#include "TimeSignature.h"

TimeSignature::TimeSignature(uint8_t* numer, uint8_t* denom, uint8_t* metro, uint8_t* thirtySecondsNotes) {
	this->numer = new uint8_t(*numer);
	this->denom = new uint8_t(*denom);
	this->metro = new uint8_t(*metro);
	this->thirtySecondsNotes = new uint8_t(*thirtySecondsNotes);
}

TimeSignature::TimeSignature() {
	this->numer = new uint8_t;
	this->denom = new uint8_t;
	this->metro = new uint8_t;
	this->thirtySecondsNotes = new uint8_t;
}

uint8_t* TimeSignature::getNumer() {
	return numer;
}

uint8_t* TimeSignature::getDenom() {
	return denom;
}

uint8_t* TimeSignature::getMetro() {
	return metro;
}

uint8_t* TimeSignature::getThirtySecondsNotes() {
	return thirtySecondsNotes;
}

void TimeSignature::setNumer(uint8_t* newNumer) {
	*numer = *newNumer;
}

void TimeSignature::setDenom(uint8_t* newDenom) {
	*denom = *newDenom;
}

void TimeSignature::setMetro(uint8_t* newMetro) {
	*metro = *newMetro;
}

void TimeSignature::setThirtySecondsNotes(uint8_t* newThirtySecondsNotes) {
	*thirtySecondsNotes = *newThirtySecondsNotes;
}
