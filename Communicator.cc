#include "Communicator.h"
#include <iostream>
#include <unistd.h>

using namespace std;

bool Communicator::getMotion() {
	
	return execlp("python", "python", "Communicator.py", NULL);
	
}

bool Communicator::testGetMotion(bool returnVal) {
	return returnVal; //Designed to simulate getMotion method
}

int Communicator::get() {
	int input;
	cin >> input;
	return input;
}
