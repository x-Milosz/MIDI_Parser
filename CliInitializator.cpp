#include<iostream>
#include<fstream>
#include "CliInitializator.h"
#include "Play.h"
using namespace std;



void CliInitializator::startCliModule() {
	setProgramsVariables();
	mainLoop();
}

void CliInitializator::setProgramsVariables() {
	setlocale(LC_ALL, "");
	loadCommands();
}

void CliInitializator::mainLoop() {
	cout << "MIDI Parser 0.1.0\nMi³osz Nowaczyk 2020" << endl;
	string input;
	bool programRunning;
	do {
		cout << "\n";
		getline(cin, input);
		programRunning = analyzeInput(input);
	} while (programRunning);
}

enum class registerdCommands {
	help = 1,
	exit = 2,
	play = 3
};

bool CliInitializator::analyzeInput(string input) {
	int* commandChoosen = new int{(int) checkCommandId(input.substr(0 ,input.find(" "))) };
	string* commandArgument = new string(input.substr(input.find(" ") + 1));
	
	switch ((int) *commandChoosen) {
	case (int) registerdCommands::help:
		printAllCommands();
		break;
	case (int) registerdCommands::exit:
		return false;
		break;
	case (int) registerdCommands::play:
		{
			Play* play = new Play(commandArgument);
			play->run();
			delete(play); 
		}
		break;
	default:
		cout << "Undefined command \"" + input.substr(0, input.find(" ")) + "\", type help to list all commands." << endl;;
		break;
	}

	return true;
}

enum class loadingMode {
	id = 0,
	commandName = 1,
	commandDescription = 2,
};

// Todo: change all variables to be allocated dynamicly
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
		cout << "Failed when tried to open the commands.conf file!" << endl;
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

// Todo: chagne place of methode to CommandEntity
void CliInitializator::printAllCommands() {
	CommandEntity* tmp = commands;
	while (commands->getNext() != nullptr) {
		cout << commands->getCommandName() + " - " + commands->getCommandDescription() << endl;
		commands = commands->getNext();
	}
	cout << commands->getCommandName() + " - " + commands->getCommandDescription() << endl;
	commands = tmp;
}

// Todo: chagne place of methode to CommandEntity
void CliInitializator::printSelectedCommand(string commandName) {
	CommandEntity* tmp = commands;
	while (commands->getNext() != nullptr) {
		if (commandName == commands->getCommandName()) {
			cout << commands->getCommandName() + " - " + commands->getCommandDescription() << endl;
		}
		commands = commands->getNext();
	}
	if (commandName == commands->getCommandName()) {
		cout << commands->getCommandName() + " - " + commands->getCommandDescription() << endl;
	}
	commands = tmp;
}

// Todo: chagne place of methode to CommandEntity
int* CliInitializator::checkCommandId(string usersCommandName) {
	int* chosenCommandId = new int{0};
	CommandEntity* tmp = commands;
	while (commands->getNext() != nullptr) {
		if (usersCommandName == commands->getCommandName()) {
			chosenCommandId = (int*) commands->getCommandId();
		}
		commands = commands->getNext();
		if (usersCommandName == commands->getCommandName()) {
			chosenCommandId = (int*) commands->getCommandId();
		}
	}
	commands = tmp;
	return chosenCommandId;
}
