#pragma once
#include<string>
#include "CommandEntity.h"
class CliInitializator {
public:
	void startCliModule();
private:
	void mainLoop();
	void setProgramsVariables();
	bool runCommand(std::string input);
	int analyzeInput(std::string input);
	void loadCommands();
	void saveCommand(int newId, std::string newCommandName, std::string newCommandDescription);
	void printAllCommands();
	CommandEntity* commands;
};

