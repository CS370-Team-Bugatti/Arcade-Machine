#include "Game2.h"
//#include "Communicator.cc"
#include <iostream>

using namespace std;

ReflexGame::ReflexGame(){	
	reaction = false;
	difficulty = -1;
	score = 0;
	difficultyStr = "";
	warning = "Game Start";
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
	//print reactors
	
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
		}else if (input == 2){
			difficultyStr = "Medium";
		}else{
			difficultyStr = "Hard";
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

int main(){
	ReflexGame game;
	game.runGame();
	return 0;
}
