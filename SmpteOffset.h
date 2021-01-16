#pragma once
#include <iostream>
class SmpteOffset {
public:
	SmpteOffset(uint8_t* hour, uint8_t* min, uint8_t* sec, uint8_t* fr, uint8_t* subFr);
	SmpteOffset();
	~SmpteOffset();
	
	uint8_t* getHour();
	uint8_t* getMin();
	uint8_t* getSec();
	uint8_t* getFr();
	uint8_t* getSubFr();

	void setHour(uint8_t* newHour);
	void setMin(uint8_t* newMin);
	void setSec(uint8_t* newSec);
	void setFr(uint8_t* newFr);
	void setSubFr(uint8_t* newSubFr);

private:
	uint8_t* hour;
	uint8_t* min;
	uint8_t* sec;
	uint8_t* fr;
	uint8_t* subFr;
};

