#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>

class Communicator {
  public:
	int get(); // may change integer implementation
	//You shouldn't need a test get method, just use the standard
	
	bool getMotion(int time, bool p); //Returns bool for motion capture
	
	bool testGetMotion(bool returnVal); //Returns a bool without motion capture, for testing

    
};

#endif
