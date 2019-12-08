#include "Communicator.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>

using namespace std;

bool Communicator::getMotion(int time, bool p) {
	pid_t pid;
	pid = fork();
	int child;
	int t = 999;
	bool motion = false;
	int status = -1;
	
	if (pid < 0) {
		//error
		exit(-1);
	}
	else {
		if (pid == 0){
			child = getpid();
			if (p) {
				execlp("python", "python", "Communicator.py", NULL);
			}
			else {
				execlp("python", "python", "CommunicatorZ.py", NULL);
			}
			
		}else{ // parent
	//		cout << "Parent Thread waiting\n";
	//		waitpid(pid, &status, 0);
			wait(&status);
			int result = WEXITSTATUS(status);
			
		//	cout << "Thread returned with status" << status << " and result " << result << "\n";
			
			ifstream myfile("result.txt");
			string s;
			myfile >> s;
			
	//		cout << "s: " << s << "\n";
			
			if (s == "1"){
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

bool Communicator::testGetMotion(bool returnVal) {
	return returnVal; //Designed to simulate getMotion method
}

int Communicator::get() {
	int input;
	cin >> input;
	return input;
}
