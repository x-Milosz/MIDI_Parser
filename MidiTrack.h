#pragma once
#include<iostream>
#include <windows.h>
#include <mmeapi.h>
#include <thread> 
#include "MidiPiece.h"

class MidiTrack {
public:
	MidiTrack(std::string* fileName, uint32_t* trackStartByte, MidiPiece* midi, HMIDIOUT* toSendInterface);
	MidiTrack();
	void start(uint8_t* threadNumber);
private:
	uint32_t* trackStartByte = nullptr;
	std::ifstream* trackStrem;
	HMIDIOUT* toSendInterface;
	void readDeltaTime();
	void applyDelay(uint8_t* currentDeltaTime, uint8_t counter);

	MidiPiece* midi;
	uint8_t* read1();
	uint16_t* read2();
	uint32_t* read4();
};

