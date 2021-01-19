#include <iostream>
#include <fstream>
#include "MidiPiece.h"
#include "windows.h"
using namespace std;

MidiPiece::MidiPiece(string* fileName) {
	this->stream = new ifstream(*fileName, ios::in | ios::binary);
	this->format = nullptr;
	this->ntrks = nullptr;
	this->division = nullptr;
	this->microsecondsPerQuarterNote = new uint32_t(700000);
	this->timeSignaure = new TimeSignature(new uint8_t(4), new uint8_t(2), new uint8_t(0), new uint8_t(0));
	this->smpteOffset = nullptr;
	this->toSendInterface = new HMIDIOUT;
}

 MidiPiece::~MidiPiece() {
	stream->close();
	delete(stream, format, ntrks, division);
}

void MidiPiece::setStream(ifstream* newStream) {
	this->stream = newStream;
}

void MidiPiece::setFormat(uint16_t* newFormat) {
	this->format = newFormat;
}

void MidiPiece::setNtrks(uint16_t* newNtrks) {
	this->ntrks = newNtrks;
}

void MidiPiece::setDivision(uint16_t* newDivision) {
	this->division = newDivision;
}

void MidiPiece::setMicrosecnodsPerQuaterNote(uint32_t* newMicrosecondsPerQuarterNote) {
	this->microsecondsPerQuarterNote = newMicrosecondsPerQuarterNote;
}

void MidiPiece::setTimeSignature(TimeSignature* newTimeSignaure) {
	this->timeSignaure = newTimeSignaure;
}

void MidiPiece::setSmpteOffset(SmpteOffset* newSmpteOffset) {
	this->smpteOffset = newSmpteOffset;
}

void MidiPiece::setToSendInterface(HMIDIOUT* newToSendInterface) {
	this->toSendInterface = newToSendInterface;
}

ifstream* MidiPiece::getStream() {
	return stream;
}

uint16_t* MidiPiece::getFormat() {
	return format;
}

uint16_t* MidiPiece::getNtrks() {
	return ntrks;
}

uint16_t* MidiPiece::getDivision() {
	return division;
}

uint32_t* MidiPiece::getMicrosecondsPerQuaterNote() {
	return microsecondsPerQuarterNote;
}

TimeSignature* MidiPiece::getTimeSignature() {
	return timeSignaure;
}

SmpteOffset* MidiPiece::getSmpteOffset() {
	return smpteOffset;
}

HMIDIOUT* MidiPiece::getToSendInterface() {
	return toSendInterface;
}

uint8_t* MidiPiece::read1() {
	uint8_t* result = new uint8_t;
	getStream()->read((char*)result, sizeof(uint8_t));
	return result;
}

uint16_t* MidiPiece::read2() {
	uint16_t* result = new uint16_t;
	getStream()->read((char*)result, sizeof(uint16_t));
	*result =_byteswap_ushort((unsigned short)*result);
	return result;
}

uint32_t* MidiPiece::read4() {
	uint32_t* result = new uint32_t;
	getStream()->read((char*)result, sizeof(uint32_t));
	*result = _byteswap_ulong((unsigned long)*result);
	return result;
}
