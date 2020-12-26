#include "CommandEntity.h"
#include<string>

CommandEntity::CommandEntity(int commandId, std::string commandName, std::string commandDescription, CommandEntity* next) {
	this->commandId = commandId;
	this->commandName = commandName;
	this->commandDescription = commandDescription;
	this->next = next;
}

CommandEntity::CommandEntity() {
}

std::string CommandEntity::getCommandName() {
	return this->commandName;
}

std::string CommandEntity::getCommandDescription() {
	return this->commandDescription;
}

int CommandEntity::getCommandId() {
	return this->commandId;
}

CommandEntity* CommandEntity::getNext() {
	return this->next;
}

void CommandEntity::setCommandName(std::string commandName) {
	this->commandName = commandName;
}

void CommandEntity::setCommandDescription(std::string commandDescription) {
	this->commandDescription= commandDescription;
}

void CommandEntity::setCommandId(int newId) {
	this->commandId = newId;
}

void CommandEntity::setNext(CommandEntity* next) {
	this->next = next;
}
