#pragma once
#include<iostream>
#include<fstream>
#include "TimeSignature.h"
#include "SmpteOffset.h"
#include "windows.h"

class MidiPiece {
public:
	MidiPiece(std::string* fileName);
	~MidiPiece();
	
	void setStream(std::ifstream* newStream);
	void setFormat(uint16_t* newFormat);
	void setNtrks(uint16_t* newNtrks);
	void setDivision(uint16_t* newDivision);
	void setMicrosecnodsPerQuaterNote(uint32_t* newMicrosecondsPerQuarterNote);
	void setTimeSignature(TimeSignature* newTimeSignaure);
	void setSmpteOffset(SmpteOffset* newSmpteOffset);
	void setToSendInterface(HMIDIOUT* newToSendInterface);

	std::ifstream* getStream();
	uint16_t* getFormat();
	uint16_t* getNtrks();
	uint16_t* getDivision();
	uint32_t* getMicrosecondsPerQuaterNote();
	TimeSignature* getTimeSignature();
	SmpteOffset* getSmpteOffset();
	HMIDIOUT* getToSendInterface();

	uint8_t* read1();
	uint16_t* read2();
	uint32_t* read4();
private:
	std::ifstream* stream;
	uint16_t* format;
	uint16_t* ntrks;
	uint16_t* division;
	uint32_t* microsecondsPerQuarterNote;
	TimeSignature* timeSignaure;
	SmpteOffset* smpteOffset;
	HMIDIOUT* toSendInterface;
};

