#include "SmpteOffset.h"

SmpteOffset::SmpteOffset(uint8_t* hour, uint8_t* min, uint8_t* sec, uint8_t* fr, uint8_t* subFr) {
	this->hour = new uint8_t(*hour);
	this->min = new uint8_t(*min);
	this->sec = new uint8_t(*sec);
	this->fr = new uint8_t(*fr);
	this->subFr = new uint8_t(*subFr);
}

SmpteOffset::SmpteOffset() {
	hour = new uint8_t;
	min = new uint8_t;
	sec = new uint8_t;
	fr = new uint8_t;
	subFr = new uint8_t;
}

SmpteOffset::~SmpteOffset() {
	delete(hour, min, sec, fr, subFr);
}

uint8_t* SmpteOffset::getHour() {
	return hour;
}

uint8_t* SmpteOffset::getMin() {
	return min;
}

uint8_t* SmpteOffset::getSec() {
	return sec;
}

uint8_t* SmpteOffset::getFr() {
	return fr;
}

uint8_t* SmpteOffset::getSubFr() {
	return subFr;
}

void SmpteOffset::setHour(uint8_t* newHour) {
	*hour = *newHour;
}

void SmpteOffset::setMin(uint8_t* newMin) {
	*min = *newMin;
}

void SmpteOffset::setSec(uint8_t* newSec) {
	*sec = *newSec;
}

void SmpteOffset::setFr(uint8_t* newFr) {
	*fr = *newFr;
}

void SmpteOffset::setSubFr(uint8_t* newSubFr) {
	*subFr = *newSubFr;
}
