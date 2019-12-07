#include "Arcade.h"
#include "Testgame.h"
#include "Game1.h"
#include "Game2.h"
#include "Memory.h" //new game
#include "Communicator.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// default constructor
Arcade::Arcade() {
//	cout << "LOG: Arcade.cc: constructor called\n";
	game_selection = "no_selection";
	score = 0;
	record = "no_record";
}

// starts the Arcade Machine
void Arcade::run() {
//	cout << "LOG: Arcade.cc: run() method called\n";

	selectGame(); // get game
	
	score = executeGame(); // run game and get score

	record = createRecord(); // create and store record

	bool worked = sendRecord(); // send record to database
	
	if (worked == false) { // send error message if it didn't work
		cout << "ERROR: Record couldn't send!\n";
	}
}

// present options to user and get selection
void Arcade::selectGame() {
//	clog << "LOG: Arcade.cc: selectGame() method called\n";
	cout << "\n\n------------------------------------------------------\n\n";
	cout << "Welcome to the Arcade Machine!\n\n";
	cout << "Options:\n\n";
	cout << "0) Test\n\n";
	cout << "1) Quiz\n\n";
	cout << "2) Motion\n\n";
	cout << "3) Memory\n\n";
	cout << "4) Exit";
	cout << "\n\n------------------------------------------------------\n\n";
	int choice;
	cout << "Choice => ";
	Communicator initialInputter;
	choice = initialInputter.get();
	if (choice == 0) {
		clog << "'" << choice << "' selected.\n";
		game_selection = "Testgame";
		
	}
	else if (choice == 1) {
		clog << "'" << choice << "' selected.\n";
		game_selection = "quiz";
	}
	else if (choice == 2) {
		clog << "'" << choice << "' selected.\n";
		game_selection = "motion";
	}//addded code here
	else if (choice == 3){
		clog << "'" << choice << "' selected.\n";
		game_selection = "memory";
	}
	else if (choice == 4) {
		cout << "'" << choice << "' selected. Exiting!\n";
		exit(1);
	}
	else {
		game_selection = "no_selection";
	}
}

// loads instance of selected game type
int Arcade::executeGame() {
//	clog << "LOG: Arcade.cc: executeGame() method called\n";

	int temp = 0;

	if (game_selection == "Testgame") { // OPTION ONE -> 'Testgame' replaceable
		Testgame Game;
		temp = Game.run();
	}
	else if (game_selection == "quiz") {
		Quiz Game;
		temp = Game.run();
	}
	else if (game_selection == "motion") {
		ReflexGame Game;
		temp = Game.runGame();
	}
	else if (game_selection == "memory") {
		Memory Game;
		temp = Game.runG();
	}
	else if (game_selection == "no_selection") { // this shouldn't run
		cout << "ERROR: No selection made! Exiting!\n";
		exit(3);
	}
	// MORE OPTIONS LATER

	return temp;
}

// creates record of gameplay in preparation to send
string Arcade::createRecord() {
	clog << "LOG: Arcade.cc: createRecord() method called\n";
	stringstream ss;
	ss << "Game selected: '" << game_selection << "'\n"
	   << "Score: '" << score << "'";
	return ss.str();
}

// sends record to database on another computer
bool Arcade::sendRecord() {
	clog << "LOG: Arcade.cc: sendRecord() method called\n";

	ofstream fss;
	fss.open("record.txt");
	fss << record;

	fss.close();	

	system("scp ./record.txt dmstephe@albany.cs.colostate.edu:/s/bach/l/under/dmstephe/CS370/group/SERVER"); // need to make this send without a password required, maybe change where it's going?

	return true; // when would there be a fail condition?
}

/* 

GOALS

[ ] replace testgame with an actual game
[ ] improve creation of record
[ ] allow sending of record without a password
[ ] edit selectGame to use the Communicator class instead of Cin to get input
[ ] create visuals for the game OR comment out log files and use console (QUESTION: Would the Communicator class still work if we used the console? I think so.)

*/
