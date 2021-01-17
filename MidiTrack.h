#pragma once
#include<iostream>
#include <windows.h>
#include <mmeapi.h>
#include <thread> 

class MidiTrack {
public:
	MidiTrack(std::string* fileName, uint32_t* trackStartByte, uint16_t* division, uint32_t* microsecondsPerQuarterNote, HMIDIOUT* toSendInterface);
	MidiTrack();
	void start(uint8_t* threadNumber);
private:
	uint32_t* trackStartByte = nullptr;
	std::ifstream* trackStrem;
	uint16_t* division;
	uint32_t* microsecondsPerQuarterNote;
	HMIDIOUT* toSendInterface;
	void delay(uint8_t* currentDeltaTime, uint8_t* counter);

	uint8_t* read1();
	uint16_t* read2();
	uint32_t* read4();
};

