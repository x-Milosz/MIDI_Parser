#include "Validator.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

Validator::Validator() {
}

Validator::~Validator() {
}

bool Validator::validateFileAndOpening(std::string fileLocation, std::ifstream* stream) {
	if (fileLocation.size() <= 4) {
		cout << "Wrong input!" << endl;
		return false;
	}
	else if (fileLocation.substr(fileLocation.size() - 4, fileLocation.size()) != ".mid") {
		cout << "Your file has extension of the wrong type!" << endl;
		return false;
	}
	else if (!stream->is_open()) {
		cout << "Failed to open your file!" << endl;
		return false;
	}
	return true;
}

bool Validator::validateMidiOutOpen(MMRESULT err) {
	if (err != MMSYSERR_NOERROR) {
		cout << "Error ";
		switch (err) {
		case MMSYSERR_BADDEVICEID:
			cout << "device ID out of range";
			break;
		case MMSYSERR_NOTENABLED:
			cout << "driver failed enable";
			break;
		case MMSYSERR_ALLOCATED:
			cout << "device already allocated";
			break;
		case MMSYSERR_INVALHANDLE:
			cout << "device handle is invalid";
			break;
		default:
			cout << "with code " + to_string(err);
			break;
		}
		cout << " while opening MIDI output!" << endl;
		return false;
	}
	else {
		return true;
	}
}

bool Validator::validateMidiFormat(int format) {
	if (format == 0 || format == 1) {
		return true;
	}
	else {
		cout << "SMPTE time format isn't supported yet." << endl;
		return false;
	}
}
