#include "MidiTrack.h"
#include <iostream>
#include <windows.h>
#include <mmeapi.h>
#include <string>
#include <fstream>
#include "MidiSpecificEnums.h"
using namespace std;

MidiTrack::MidiTrack(string* fileName, uint32_t* trackStartByte, MidiPiece* midi, HMIDIOUT* toSendInterface) {
	this->trackStartByte = new uint32_t(*trackStartByte);
	this->trackStrem = new ifstream(*fileName, ios::in | ios::binary);
	this->midi = midi;
	this->toSendInterface = toSendInterface;
}

MidiTrack::MidiTrack() {
}

void MidiTrack::start(uint8_t* threadNumber) {
	printf("Thread number %d is on.\n", *threadNumber);
	
	trackStrem->seekg(*trackStartByte); 

	bool* isTrackOver = new bool(false);

	uint8_t* currentlyExaminedByte = new uint8_t;

	uint32_t* msg = new uint32_t(0);
	uint32_t* tmp = new uint32_t();
	read4();
	read4();
	while (!*isTrackOver) {

		readDeltaTime();

		*currentlyExaminedByte = *read1();

		// Meta events
		if (*currentlyExaminedByte == 0xFF) {
			*currentlyExaminedByte = *read1();
			if (*currentlyExaminedByte == endOfTrack) {
				read1();
				*isTrackOver = true;
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
			else {
				// represents other, unimplemented meta events
				*tmp = *read1();
				for (int i = 0; i < *tmp; i++) {
					read1();
				}
			}
		}
		// Channel events
		else {
			*msg = 0;
			if ((*currentlyExaminedByte >> 4) == noteOff || (*currentlyExaminedByte >> 4) == noteOn || (*currentlyExaminedByte >> 4) == noteAftertouch
				|| (*currentlyExaminedByte >> 4) == controller || (*currentlyExaminedByte >> 4) == pitchBend) {
				*msg = *currentlyExaminedByte | (*read1() << 8);
				*msg = *msg | (*read1() << 16);

				midiOutShortMsg(*toSendInterface, *msg);
			}
			else if ((*currentlyExaminedByte >> 4) == programChange || (*currentlyExaminedByte >> 4) == channelAfterTouch) {
				*msg = *currentlyExaminedByte | (*read1() << 8);

				midiOutShortMsg(*toSendInterface, *msg);
			}
		}
	}
}

uint8_t* MidiTrack::read1() {
	uint8_t* result = new uint8_t;
	trackStrem->read((char*)result, sizeof(uint8_t));
	return result;
}

uint16_t* MidiTrack::read2() {
	uint16_t* result = new uint16_t;
	trackStrem->read((char*)result, sizeof(uint16_t));
	*result = _byteswap_ushort((unsigned short)*result);
	return result;
}

uint32_t* MidiTrack::read4() {
	uint32_t* result = new uint32_t;
	trackStrem->read((char*)result, sizeof(uint32_t));
	*result = _byteswap_ulong((unsigned long)*result);
	return result;
}

void MidiTrack::readDeltaTime() {
	uint8_t* currentDeltaTime = new uint8_t[4];
	currentDeltaTime[0] = *read1();
	uint8_t counter = 0;
	while (currentDeltaTime[counter] >= 128) {
		currentDeltaTime[counter] = currentDeltaTime[counter] - 128;
		if (counter < 4) {
			counter += 1;
			currentDeltaTime[counter] = *read1();
		}
	}
	applyDelay(currentDeltaTime, counter);
}

void MidiTrack::applyDelay(uint8_t* currentDeltaTime, uint8_t counter) {
	// For metrical timing
	if (currentDeltaTime[0] == 0) {
		return;
	}
	else  {
		uint32_t* deltaTime = new uint32_t(currentDeltaTime[0]);
		for (int i = 0; i <= counter; i++) {
			*deltaTime = (*deltaTime << i * 7) | currentDeltaTime[i];
		}
		double* t1 = new double(*deltaTime / (double)*midi->getDivision());
		*t1 = *t1 * *midi->getMicrosecondsPerQuaterNote();
		*t1 = *t1 / 1000;
		uint32_t* properInt = new uint32_t(*t1);
		Sleep(*properInt);
	}
}