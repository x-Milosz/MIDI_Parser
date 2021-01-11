#pragma once
#include<string>
#include<fstream>
#include "MidiPiece.h"
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

	bool validateFile(std::ifstream* stream);
	void play(MidiPiece* midi);
};