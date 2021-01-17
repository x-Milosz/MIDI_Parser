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
	
	if (validateFile(midi)) {
		play(midi);
	}
}

bool Play::validateFile(MidiPiece* midi) {
	if (fileLocation->size() <= 4) {
		cout << "Wrong input!" << endl;
		return false;
	}
	else if (fileLocation->substr(fileLocation->size() - 4, fileLocation->size()) != ".mid") {
		cout << "Your file has extension of wrong type!" << endl;
		return false;
	}
	else if (!midi->getStream()->is_open()) {
		cout << "Failed to open your file!" << endl;
		return false;
	} 
	return true;
}

void Play::play(MidiPiece* midiFile) {
	HMIDIOUT* toSendInterface = new HMIDIOUT;
	
	MMRESULT* returnMidiError = new MMRESULT(midiOutOpen(toSendInterface, -1, NULL, NULL, CALLBACK_NULL));
	if (MMSYSERR_NOERROR != *returnMidiError) {

		cout << "Error " + to_string(*returnMidiError) + " while opening MIDI output!" << endl;
		return;
	}
	delete(returnMidiError);

	midiFile->read4(); // For header chunk
	midiFile->read4(); // For header chunk lenght
	midiFile->setFormat(midiFile->read2());
	midiFile->setNtrks(midiFile->read2());
	midiFile->setDivision(midiFile->read2());

	MidiTrack** midiTracks = new MidiTrack*[*midiFile->getNtrks() - 1];


	if (*midiFile->getFormat() == 1 || *midiFile->getFormat() == 0) {


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
					midiFile->read4();
					*lenghtOfChunk = *midiFile->read4();
					*isTrackOver = false;
					*byteCounter += *lenghtOfChunk;
					*trackCount += 1;
					if (*trackCount == 2) {
						*byteCounter += 8;
						break;
					}
				}

				// Calculate delta time
				currentDeltaTime[0] = *midiFile->read1();a// lenght is fixed - 5;


				*currentlyExaminedByte = *midiFile->read1();

				// Meta events
				if (*currentlyExaminedByte == 0xFF) {
					*currentlyExaminedByte = *midiFile->read1();

					if (*currentlyExaminedByte == smpteOffset) {
						// lenght is fixed - 5;
						midiFile->read1(); 
						midiFile->setSmpteOffset(new SmpteOffset(midiFile->read1(), midiFile->read1(), midiFile->read1(), midiFile->read1(), midiFile->read1()));
					}
					else if (*currentlyExaminedByte == timeSignature) {
						// lenght is fixed - 4
						midiFile->read1(); 
						midiFile->setTimeSignature(new TimeSignature(midiFile->read1(), midiFile->read1(), midiFile->read1(), midiFile->read1()));
					}
					else if (*currentlyExaminedByte == setTempo) {
						// lenght is fixed - 3
						midiFile->read1();
						uint32_t* microsecondsPerQuarterNote = new uint32_t(0);
						uint16_t* first2Bytes = new uint16_t(*midiFile->read2());
						uint8_t* secondByte = new uint8_t(*midiFile->read1());
						*microsecondsPerQuarterNote = *first2Bytes;
						*microsecondsPerQuarterNote = (*microsecondsPerQuarterNote << 8) | *secondByte;
						midiFile->setMicrosecnodsPerQuaterNote(microsecondsPerQuarterNote);
						delete(first2Bytes, secondByte);
					}
					else if (*currentlyExaminedByte == keySignature) {
						midiFile->read1(); // lenght is fixed - 2
						keySignatureOfTrack = midiFile->read2();
					}
					else if (*currentlyExaminedByte == endOfTrack) {
						midiFile->read1();
						*isTrackOver = true;
					}
					else {
						// represents other, unimplemented meta events
						*tmp = *midiFile->read1();
						for (int i = 0; i < *tmp; i++) {
							midiFile->read1();
						}
					}
				}
				// Channel events
				else {
					*msg = 0;
					if ((*currentlyExaminedByte >> 4) == noteOff || (*currentlyExaminedByte >> 4) == noteOn || (*currentlyExaminedByte >> 4) == noteAftertouch
						|| (*currentlyExaminedByte >> 4) == controller || (*currentlyExaminedByte >> 4) == pitchBend) {
						*msg = *currentlyExaminedByte | (*midiFile->read1() << 8);
						*msg = *msg | (*midiFile->read1() << 16);

						midiOutShortMsg(*toSendInterface, *msg);
					}
					else if ((*currentlyExaminedByte >> 4) == programChange || (*currentlyExaminedByte >> 4) == channelAfterTouch) {
						*msg = *currentlyExaminedByte | (*midiFile->read1() << 8);

						midiOutShortMsg(*toSendInterface, *msg);
					}
				}
			}
			
			for(int i = 0; i < *midiFile->getNtrks() - 1; i++){
				midiTracks[i] = new MidiTrack(fileLocation, byteCounter, midiFile->getDivision(), midiFile->getMicrosecondsPerQuaterNote(), toSendInterface);
				for (int y = 0; y < *lenghtOfChunk; y++) {
					midiFile->read1();
				}
				if (i != *midiFile->getNtrks() - 2) {
					midiFile->read4(); // Chunk title
					*lenghtOfChunk = *midiFile->read4();
					*byteCounter += *lenghtOfChunk + 8;
				}
			}
		
		runOtherTracks(midiTracks, midiFile);
		midiOutClose(*toSendInterface);
}


}

void Play::runOtherTracks(MidiTrack** midiTracks, MidiPiece* midiFile ) {
	vector <thread*> ts;
	for (size_t i = 0; i < *midiFile->getNtrks() - 1; i++) {
		thread* t = new thread(&MidiTrack::start, midiTracks[i], new uint8_t(i));
		ts.push_back(t);
	}
	for (int i = 0; i < ts.size(); i++) {
		ts[i]->join();
	}
}



