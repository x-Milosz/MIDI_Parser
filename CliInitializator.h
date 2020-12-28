#pragma once
#include<string>
#include "CommandEntity.h"
class CliInitializator {
public:
	void startCliModule();
private:
	void mainLoop();
	void setProgramsVariables();
	void runCommand(std::string input);
	bool analyzeInput(std::string input);
	void loadCommands();
	void saveCommand(CommandEntity* newCommand);
	void printAllCommands();
	void printSelectedCommand(std::string commandName);
	int* checkCommandId(std::string usersCommandName);
	CommandEntity* commands;
};

