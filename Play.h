#pragma once
#include<string>
#include<fstream>
#include "MidiPiece.h"
#include "MidiTrack.h"
class Play {
public:
	Play(std::string* fileLocation) {
		this->fileLocation = fileLocation;
	}
	~Play() {
		delete fileLocation;
	}
	void run();
private:
	std::string* fileLocation;

	bool validateFile(MidiPiece* midi);
	void play(MidiPiece* midi);
	void delay(MidiPiece* midi, uint8_t* currentDeltaTime, uint8_t* counter);
	void runOtherTracks(MidiTrack** midiTracks, MidiPiece* midiFile);
	
};