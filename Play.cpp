#include<iostream>
#include<fstream>
#include "Play.h"
#include "MidiPiece.h"
using namespace std;

void Play::run() {
	MidiPiece* midi = new MidiPiece(fileLocation);
	
	if (validateFile(midi->getStream())) {
		play(midi);
	}
}

bool Play::validateFile(ifstream* stream) {
	if (fileLocation->size() <= 4) {
		cout << "Wrong input!" << endl;
		return false;
	}
	else if (fileLocation->substr(fileLocation->size() - 4, fileLocation->size()) != ".mid") {
		cout << "Your file has extension of wrong type!" << endl;
		return false;
	}
	else if (!stream->is_open()) {
		cout << "Failed to open your file!" << endl;
		return false;
	}
	return true;
}

void Play::play(MidiPiece* midi) {
	
}