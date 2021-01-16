#pragma once
#include <iostream>
class TimeSignature {
public:
	TimeSignature(uint8_t* numer, uint8_t* denom, uint8_t* metro, uint8_t* thirtySecondsNotes);
	TimeSignature();

	uint8_t* getNumer();
	uint8_t* getDenom();
	uint8_t* getMetro();
	uint8_t* getThirtySecondsNotes();

	void setNumer(uint8_t* newNumer);
	void setDenom(uint8_t* newDenom);
	void setMetro(uint8_t* newMetro);
	void setThirtySecondsNotes(uint8_t* newThirtySecondsNotes);
private:
	uint8_t* numer;
	uint8_t* denom;
	uint8_t* metro;
	uint8_t* thirtySecondsNotes;
};

