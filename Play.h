#pragma once
#include<string>
#include<fstream>
#include "MidiPiece.h"
#include "MidiTrack.h"
#include "Validator.h"
class Play {
public:
	Play(std::string* fileLocation) {
		this->fileLocation = fileLocation;
		this->validator = new Validator();
	}
	~Play() {
		delete fileLocation, validator;
	}
	void run();
private:
	std::string* fileLocation;
	Validator* validator;

	void play(MidiPiece* midi);
	void delay(MidiPiece* midi, uint8_t* currentDeltaTime, uint8_t* counter);
	void runOtherTracks(MidiTrack** midiTracks, MidiPiece* midiFile);
	
};