#include<iostream>
#include<fstream>
#include "CliInitializator.h"
using namespace std;

enum class loadingMode {
	id = 0,
	commandName = 1,
	commandDescription = 2,
};


void CliInitializator::startCliModule() {
	setProgramsVariables();
	mainLoop();
}

void CliInitializator::setProgramsVariables() {
	setlocale(LC_ALL, "");
	loadCommands();
}

void CliInitializator::mainLoop() {
	cout << "MIDI Parser 0.1.0\nMi³osz Nowaczyk 2020\n\n" << endl;
	string input;
	bool programRunning;
	printAllCommands();
	do {
		cin >> input;
		programRunning = runCommand(input);
	} while (programRunning);
}

bool CliInitializator::runCommand(string input) {
	return true;
}

int CliInitializator::analyzeInput(string input) {
	
	return 0;
}

void CliInitializator::loadCommands() {
	ifstream* commandsLoader = new ifstream("commands.conf", ios::in);
	char singleCharacter;
	string newWord = "";
	CommandEntity* tmp = nullptr;
	int currentMode = (int) loadingMode::id;
	if (commandsLoader->is_open()) {
		
		while (commandsLoader->get(singleCharacter)) {
			if (singleCharacter != ',' && singleCharacter != '\n') {
				newWord += singleCharacter;
			}
			else {
				if (currentMode == (int) loadingMode::id) {
					tmp = new CommandEntity();
					tmp->setCommandId(stoi(newWord));
					currentMode = (int)loadingMode::commandName;
				}
				else if (currentMode == (int) loadingMode::commandName) {
					tmp->setCommandName(newWord);
					currentMode = (int)loadingMode::commandDescription;
				}
				else if (currentMode == (int)loadingMode::commandDescription) {
					tmp->setCommandDescription(newWord);
					saveCommand(tmp);
					currentMode = (int)loadingMode::id;
				}
				newWord = "";
				
			}
		}
		tmp->setCommandDescription(newWord);
		saveCommand(tmp);
		commandsLoader->close();
		delete(commandsLoader);
	}
	else {
		cout << "Fail when tried to open the commands.conf file!" << endl;
		exit(1);
	}
}

void CliInitializator::saveCommand(CommandEntity* newCommand) {
	if (commands == nullptr) {
		commands = newCommand;
	}
	else {
		CommandEntity* tmp = commands;
		while (commands->getNext() != nullptr) {
			commands = commands->getNext();
		}
		commands->setNext(newCommand);
		commands = tmp;
	}
}

void CliInitializator::printAllCommands() {
	CommandEntity* tmp = commands;
	while (commands->getNext() != nullptr) {
		cout << commands->getCommandName() << endl;
		cout << commands->getCommandDescription() << endl;
		commands = commands->getNext();
	}
	cout << commands->getCommandName() << endl;
	cout << commands->getCommandDescription() << endl;
	commands = tmp;
}
