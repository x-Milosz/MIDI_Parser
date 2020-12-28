#pragma once
#include<string>
class Play {
public:
	Play(std::string* fileLocation) {
		this->fileLocation = fileLocation;
	}
	void run();
private:
	std::string* fileLocation;
};