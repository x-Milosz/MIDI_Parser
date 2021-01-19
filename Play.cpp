#include <windows.h>
#include <mmeapi.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <thread>
#include <vector>
#include "MidiSpecificEnums.h"
#include "Play.h"
#include "MidiPiece.h"
#include "MidiTrack.h"

using namespace std;

void Play::run() {
	MidiPiece* midi = new MidiPiece(fileLocation);
	if (validator->validateFileAndOpening(*fileLocation, midi->getStream()) && 
		validator->validateMidiOutOpen(midiOutOpen(midi->getToSendInterface(), -1, NULL, NULL, CALLBACK_NULL))) {
		play(midi);
	}
}

void Play::play(MidiPiece* midi) {
	midi->read4(); // For header chunk
	midi->read4(); // For header chunk lenght
	midi->setFormat(midi->read2());
	midi->setNtrks(midi->read2());
	midi->setDivision(midi->read2());

	if (!validator->validateMidiFormat(*midi->getFormat())) {
		return;
	}

	MidiTrack** midiTracks = new MidiTrack*[*midi->getNtrks() - 1];
	uint32_t* lenghtOfChunk = new uint32_t;
	uint16_t* keySignatureOfTrack = new uint16_t;
	bool* isTrackOver = new bool(true);

	uint8_t* currentlyExaminedByte = new uint8_t;
	uint8_t* currentDeltaTime = new uint8_t[4];
	uint32_t* byteCounter = new uint32_t(22);

	uint32_t* msg = new uint32_t;
	uint32_t* tmp = new uint32_t();

	uint8_t* trackCount = new uint8_t(0);	
		while (*trackCount < 2) {
			if (*isTrackOver) {
				midi->read4();
				*lenghtOfChunk = *midi->read4();
				*isTrackOver = false;
				*byteCounter += *lenghtOfChunk;
				*trackCount += 1;
				if (*trackCount == 2) {
					*byteCounter += 8;
					break;
			}
		}

			// Calculate delta time
			currentDeltaTime[0] = *midi->read1();// lenght is fixed - 5;


			*currentlyExaminedByte = *midi->read1();

			// Meta events
			if (*currentlyExaminedByte == 0xFF) {
				*currentlyExaminedByte = *midi->read1();

				if (*currentlyExaminedByte == smpteOffset) {
					// lenght is fixed - 5;
					midi->read1(); 
					midi->setSmpteOffset(new SmpteOffset(midi->read1(), midi->read1(), midi->read1(), midi->read1(), midi->read1()));
				}
				else if (*currentlyExaminedByte == timeSignature) {
					// lenght is fixed - 4
					midi->read1(); 
					midi->setTimeSignature(new TimeSignature(midi->read1(), midi->read1(), midi->read1(), midi->read1()));
				}
				else if (*currentlyExaminedByte == setTempo) {
					// lenght is fixed - 3
					midi->read1();
					uint32_t* microsecondsPerQuarterNote = new uint32_t(0);
					uint16_t* first2Bytes = new uint16_t(*midi->read2());
					uint8_t* secondByte = new uint8_t(*midi->read1());
					*microsecondsPerQuarterNote = *first2Bytes;
					*microsecondsPerQuarterNote = (*microsecondsPerQuarterNote << 8) | *secondByte;
					midi->setMicrosecnodsPerQuaterNote(microsecondsPerQuarterNote);
					delete(first2Bytes, secondByte);
				}
				else if (*currentlyExaminedByte == keySignature) {
					midi->read1(); // lenght is fixed - 2
					keySignatureOfTrack = midi->read2();
				}
				else if (*currentlyExaminedByte == endOfTrack) {
					midi->read1();
					*isTrackOver = true;					}
				else {
					// represents other, unimplemented meta events
					*tmp = *midi->read1();
					for (int i = 0; i < *tmp; i++) {
						midi->read1();
					}
				}
			}
			// Channel events
			else {
				*msg = 0;
				if ((*currentlyExaminedByte >> 4) == noteOff || (*currentlyExaminedByte >> 4) == noteOn || (*currentlyExaminedByte >> 4) == noteAftertouch
					|| (*currentlyExaminedByte >> 4) == controller || (*currentlyExaminedByte >> 4) == pitchBend) {
					*msg = *currentlyExaminedByte | (*midi->read1() << 8);
					*msg = *msg | (*midi->read1() << 16);

					midiOutShortMsg(*midi->getToSendInterface(), *msg);
				}
				else if ((*currentlyExaminedByte >> 4) == programChange || (*currentlyExaminedByte >> 4) == channelAfterTouch) {
					*msg = *currentlyExaminedByte | (*midi->read1() << 8);

					midiOutShortMsg(*midi->getToSendInterface(), *msg);
				}
			}
		}
			
		if (*midi->getNtrks() == 2) {
			*byteCounter = *byteCounter - *lenghtOfChunk - 8;
			midiTracks[0] = new MidiTrack(fileLocation, byteCounter, midi, midi->getToSendInterface());
		}
		else {
			for (int i = 0; i < *midi->getNtrks() - 1; i++) {
				midiTracks[i] = new MidiTrack(fileLocation, byteCounter, midi, midi->getToSendInterface());
				for (int y = 0; y < *lenghtOfChunk; y++) {
					midi->read1();
				}
				if (i != *midi->getNtrks() - 2) {
					midi->read4(); // Chunk title
					*lenghtOfChunk = *midi->read4();
					*byteCounter += *lenghtOfChunk + 8;
				}
			}
		}
		
	runOtherTracks(midiTracks, midi);
	midiOutClose(*midi->getToSendInterface());
}

void Play::runOtherTracks(MidiTrack** midiTracks, MidiPiece* midiFile ) {
	// repair loop!!!
	

	vector <thread*> ts;
	for (size_t i = 0; i < *midiFile->getNtrks() - 1; i++) {
		thread* t = new thread(&MidiTrack::start, midiTracks[i], new uint8_t(i));
		ts.push_back(t);
	}
	for (int i = 0; i < ts.size(); i++) {
		ts[i]->join();
	}
}



