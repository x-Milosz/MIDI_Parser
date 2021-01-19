#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
class Validator {
public:
	Validator();
	~Validator();
	bool validateFileAndOpening(std::string fileLocation, std::ifstream* stream);
	bool validateMidiOutOpen(MMRESULT err);
	bool validateMidiFormat(int format);
};

