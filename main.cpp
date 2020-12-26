#include <iostream>
#include "CliInitializator.h"
using namespace std;

int main() {
	CliInitializator* cliModule = new CliInitializator();
	cliModule->startCliModule();
}

