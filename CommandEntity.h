#include<string>
class CommandEntity {
public:
	CommandEntity(int commandId, std::string commandName, std::string commandDescription, CommandEntity* next);
	CommandEntity();
	std::string getCommandName();
	std::string getCommandDescription();
	int getCommandId();
	CommandEntity* getNext();
	void setCommandName(std::string commandName);
	void setCommandDescription(std::string commandDescription);
	void setCommandId(int newId);
	void setNext(CommandEntity* next);
	std::string commandName;
	std::string commandDescription;
	int commandId;
	CommandEntity* next;
private:
	
};
