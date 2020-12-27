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
	int newId;
	string commandName, commandDescription;
	int currentMode = (int) loadingMode::id;
	if (commandsLoader->is_open()) {
		
		while (commandsLoader->get(singleCharacter)) {
			if (singleCharacter != ',' && singleCharacter != '\n') {
				newWord += singleCharacter;
			}
			else {
				if (currentMode == (int) loadingMode::id) {
					newId = (stoi(newWord));
					currentMode = (int)loadingMode::commandName;
				}
				else if (currentMode == (int) loadingMode::commandName) {
					commandName = newWord;
					currentMode = (int)loadingMode::commandDescription;
				}
				else if (currentMode == (int)loadingMode::commandDescription) {
					commandDescription = newWord;
					saveCommand(newId, commandName, commandDescription);
					currentMode = (int)loadingMode::id;
				}
				newWord = "";
				
			}
		}
		saveCommand(newId, commandName, commandDescription);
		commandsLoader->close();
		delete(commandsLoader);
	}
	else {
		cout << "Fail when tried to open the commands.conf file!" << endl;
		exit(1);
	}
}

void CliInitializator::saveCommand(int newId, string newCommandName, string newCommandDescription) {
	if (commands == NULL) {
		commands = new CommandEntity(newId, newCommandName, newCommandDescription, NULL);
	}
	else {
		CommandEntity* tmp = commands;
		while (commands->next != NULL) {
			commands = commands->next;
		}
		commands->next = new CommandEntity(newId, newCommandName, newCommandDescription, NULL);
		commands = tmp;
	}
}

void CliInitializator::printAllCommands() {
	CommandEntity* tmp = commands;
	while (commands->next != NULL) {
		cout << commands->commandName << endl;
		cout << commands->getCommandDescription() << endl;
		commands = commands->next;
	}
	cout << commands->commandName << endl;
	cout << commands->getCommandDescription() << endl;
	commands = tmp;
}
