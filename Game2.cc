#include "Game2.h"
//#include "Communicator.cc"
#include <iostream>
#include <thread>
#include <future>

using namespace std;

ReflexGame::ReflexGame(){	
	difficulty = -1;
	score = 0;
	difficultyStr = "";
	warning = "Game Start";
	speedDecr = true;
	multiplier = 0.6;
}//end of constructor

int ReflexGame::runGame(){
	//clear the terminal
	cout << "\033[2J\033[1;1H";
	cout << "Playing: Reflex Game\n";
	//print the selection screen
	while (difficulty == -1){
		printSelection();
	}
	cout << "\033[2;1H\033[J";
	cout << "Difficulty: " << difficultyStr << "\n";
	cout << warning << "\n";
	
	gameStart();

	return score;
}

bool ReflexGame::validate(int input){
	if (input < 1 || input > 3){
		cout << "invalid input\n";
		return false;
	}else{
		char confirm = '\0';
		if (input == 1){
			difficultyStr = "Easy";
			speed = 8;
			minSpeed = 3.5;
			vectorMax = 2;
		}else if (input == 2){
			difficultyStr = "Medium";
			speed = 7;
			minSpeed = 2.5;
			vectorMax = 3;
		}else{
			difficultyStr = "Hard";
			speed = 5;
			minSpeed = 1.5;
			vectorMax = 5;
		}
		cout << "You have selected " << difficultyStr << " Is this correct? (Y/N)\n";
		cin >> confirm;

		//if bad input, say so
		while (cin.fail() || (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N')){
			if (confirm != '\0'){
				//delete line 8 and below
				cout << "\033[8;1H\33[J";
				cout << "";
				cout << "please enter either a y or n\n";
				cin.clear();
				cin.ignore();
				confirm = '\0';
				cout << confirm;
			}
			cin >> confirm;
		}
		//if no, go back to selection
		if (confirm == 'n' || confirm == 'N'){
			cout << "\033[2;1H\33[J";
			return false;
		}
		return true;
	}
}

void ReflexGame::printSelection(){
	int input;
	bool valid = false;
	cout << "Please select your difficulty\n";
	cout << "1: Easy\n2: Medium\n3: Hard\n";
	while (!valid){
		
		cin >> input;
		//not a number
		if (cin.fail()){
			cout << "\033[6;1H\33[J";
			cout << "Invalid input. Please enter a number between 1 and 3\n";
			valid = false;
			cin.clear();
			cin.ignore();
		}else{
			valid = validate(input);
			if (!valid){
				cout << "Please select your difficulty\n";
				cout << "1: Easy\n2: Medium\n3: Hard\n";
			}
		}
	}
	difficulty = input;
}

void ReflexGame::gameStart(){

	bool cont = true;
	
	//this is used with changeTime
	bool warned = false;

	initializeTimeChange(timeChange, changeTimeMS);
	auto currentTime = chrono::system_clock::now().time_since_epoch();
	//5000 is a placeholder, change to 120000 for 2 minutes
	auto endTime = currentTime + chrono::milliseconds(120000);

	auto nextChangeTime = currentTime + chrono::milliseconds(10000);

	//set the time in milliseconds for changes
	auto staticChangeTime = chrono::milliseconds(10000);
	//set the time in milliseconds for warn time
	auto staticWarnTime = staticChangeTime - chrono::milliseconds(changeTimeMS);

	auto nextWarnTime = currentTime + staticWarnTime;

	auto nextReactorTime = currentTime + chrono::duration<double>(speed);
	
	//add the initial element
	changeReactors();	

	//generate the RNG line
	generateReaction();
	
	newThread = true;
		while ( currentTime < endTime){
			//check if warning needs to be made
			if (timeChange && (currentTime >= nextWarnTime) && !warned){
				auto seconds = changeTimeMS/1000;
				cout << "\033[3;1HWarning: Reactors change in "<< seconds <<" seconds!\033[5;1H" << endl;
				warned = true;
			}
			//update the current time
			currentTime = chrono::system_clock::now().time_since_epoch();
			
			//print reaction
			if (currentTime >= nextReactorTime){
				generateReaction();
				nextReactorTime = nextReactorTime + chrono::duration<double>(speed);
			}

			//start the input thread if needed
			//if newThread = true, make thread, set newThread to false
			if (newThread == true){
				newThread = false;
			}

			auto f = async(launch::async, [] {
				cout << " created second thread" << endl;
				bool noPause = true;
				string s = "";
				while(noPause){
					auto s = ""s;
					if (cin >> s){
						if (s.find('q') != string::npos){
							return true;
						}else{
							cin.clear();
							cin.ignore(10000, '\n');
						}
					}
				}
				return false;
			});

			if (f.get()){
				//verify that reaction is in reactors
				newThread = true;
			}
			//else if responded == true
				//increment fail
			//else, if currentTime >= expectedResponseTime
				//no response or extra response
				//update expectedResponseTime
				//set responded to false

			//every 10 seconds, change array
			if (currentTime >= nextChangeTime && warned){		
				cout << "\033[3;1H\033[2K" << "\033[3;1H" << endl;
				nextWarnTime = nextChangeTime + staticWarnTime;
				nextChangeTime = nextChangeTime + chrono::milliseconds(10000);
				warned = false;
				changeReactors();
			}
			//update the current time
			currentTime = chrono::system_clock::now().time_since_epoch();
		}
	
	cout << "Game End\n";
	//calculate score	
	//print statistics
	
}

void ReflexGame::generateReaction(){
	if (speedDecr){	
		speed = speed - multiplier;
		if (speed < minSpeed){
			speed = minSpeed;
			speedDecr = false;
		}
	}
	
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> range(0,9);
	reaction = range(generator);
	cout << "\033[5;1HReaction: " << reaction << endl;
}

void ReflexGame::initializeTimeChange(bool& timeChange, int& changeTime){
	timeChange = true;
	if (difficulty == 1){
		//4 second warning
		changeTime = 4000;
	}else if (difficulty == 2){
		//2 second warning
		changeTime = 2000;
	}else{
		timeChange = false;
		changeTime = 0;
	}
}

void ReflexGame::printReactors(){
	cout << "Numbers to react to: ";
	for (int i = 0; i < reactors.size(); i++){
		cout << reactors[i] << " ";
	}
	cout << "\033[5;1H" << endl;
}

void ReflexGame::changeReactors(){
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> range(0,9);
	int size = reactors.size();
	int num = 0;
	
	//determine what to do
	if (size == 0){
		//can add
		num = 0;
	}else if (size == 1){
		//can add or change
		std::uniform_int_distribution<int> choice(0,1);
		num = choice(generator);
	}else if (size == vectorMax){
		//can remove or change
		std::uniform_int_distribution<int> choice(1,2);
		num = choice(generator);
	}else{
		//can add, remove, or change
		std::uniform_int_distribution<int> choice(0,2);
		num = choice(generator);
	}
	
	//change the vector

	//get an element and make sure it doesnt already exist
	int newElement = range(generator);
	bool valid = true;
	while (valid){
		if (std::find(reactors.begin(), reactors.end(), newElement) != reactors.end()){
			newElement = range(generator);
		}else{
			valid = false;
		}
	}


	if (num == 0){ //add
		reactors.push_back(newElement);
	}else {
		std::uniform_int_distribution<int> element(0, size-1);
		//get a random index
		int index = element(generator);
		if (num == 1){ //change
			int oldElement = reactors.at(index);
			while (newElement == oldElement){newElement = range(generator);}
			reactors.at(index) = newElement;
		}else{ //erase
			reactors.erase(reactors.begin() + index);		
		}
	}	
	
	//print the change
	printReactors();
}


int main(){
	ReflexGame game;
	game.runGame();
	return 0;
}
