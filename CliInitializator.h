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
	void saveCommand(CommandEntity* newCommand);
	void printAllCommands();
	CommandEntity* commands;
};

