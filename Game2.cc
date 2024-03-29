#include "Game2.h"
#include "Communicator.h"
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
	multiplier = 1;
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
			minSpeed = 4;
			vectorMax = 2;
		}else if (input == 2){
			difficultyStr = "Medium";
			speed = 7;
			minSpeed = 3;
			vectorMax = 3;
		}else{
			difficultyStr = "Hard";
			speed = 5;
			minSpeed = 2;
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
	
	//add the initial element
	changeReactors();	

	//generate the RNG line
	generateReaction();
	
	cout << "\033[6;1HScore: "<< score << endl;
bool replied = false;
		while ( currentTime < endTime){
			//update the current time
			currentTime = chrono::system_clock::now().time_since_epoch();
			
			auto nextReactorTime = currentTime + chrono::duration<double>(speed);
			
			generateReaction();
			
			
			while (currentTime < nextReactorTime && replied == false){
		//		cout << "here" << endl;
				if (comm.getMotion(speed, false)){
						if (ReflexGame::isInReactors(reaction)){
							score++;
						}else{
						//	score--;
						}
						replied = true;
						generateReaction();
				}
				currentTime = chrono::system_clock::now().time_since_epoch();
			}
			
			if (!replied && ReflexGame::isInReactors(reaction)){
			//	score--;
			}
			replied = false;
	
			//change what to react to
			if (currentTime >= nextChangeTime){
//cout << "im here" << endl;
				cout << "\033[3;1H\033[2K" << "\033[3;1H" << endl;
				nextChangeTime = currentTime + chrono::milliseconds(10000);
				changeReactors();
			}

			cout << "\033[6;1HScore: "<< score << endl;
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
	int temp = range(generator);
	while (reaction == temp){
			temp = range(generator);
	}
	reaction = temp;
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
		
	cout << "\033[2K";
	cout << "Numbers to react to: ";
	for (int i = 0; i < reactors.size(); i++){
		cout << reactors[i] << " ";
	}
	cout << "\033[5;1H" << endl;
	
	cout << reactors.size() << endl;
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

	//element already exists
	bool bad = isInReactors(newElement);
	while (bad){
		bad = isInReactors(range(generator));
	}

	if (num == 0){ //add
		reactors.push_back(newElement);
	}else {
		std::uniform_int_distribution<int> element(0, size-1);
		//get a random index
		int index = element(generator);
		if (num == 1){ //change
			int oldElement = reactors[index];
			while (newElement == oldElement){ newElement = range(generator);}
			reactors[index] = newElement;
		}else{ //erase
			reactors.erase(reactors.begin() + index);		
		}
	}
	
	//print the change
	printReactors();
}

bool ReflexGame::isInReactors(int element){
	for (int i = 0; i < reactors.size(); i++){
		if (reactors[i] == element){
			return true;
		}
	}
	return false;
}
