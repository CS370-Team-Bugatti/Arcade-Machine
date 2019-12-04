#ifndef GAME_2_INCLUDED
#define GAME_2_INCLUDED

#include <string>
#include <curses.h>
#include <chrono>

class ReflexGame{
	public:
		/*** methods ***/
		//ctor
		ReflexGame();
		//returns average reflex in seconds
		int runGame();
		void PrintScore();
		void printSelection();
		bool validate(int);
		void gameStart();
		void printReactors();
		void initializeTimeChange(bool&, int&);
	
		/*** variables ***/
		//score is average reflex in seconds
		int score;
		//difficulty level (0=easy, 1=medium, 2=hard)
		int difficulty;
		//boolean for whether or not a reaction is expected
		bool reaction;
		std::string difficultyStr;
		std::string warning;
		int changeTimeMS;
		bool timeChange;
		//what nseeds to be reacted to
		int reactors[];
};//end of format class

#endif
