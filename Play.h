#pragma once
#include<string>
#include<fstream>
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
};