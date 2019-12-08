#ifndef GAME_2_INCLUDED
#define GAME_2_INCLUDED

#include "Communicator.h"
#include <string>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>

class ReflexGame{
	public:
		//returns average reflex in seconds
		int runGame();
		//ctor
		ReflexGame();
	private:
		/*** methods ***/
		
		void PrintScore();
		void printSelection();
		bool validate(int);
		void gameStart();
		void printReactors();
		void initializeTimeChange(bool&, int&);
		void changeReactors();
		void generateReaction();
		bool isInReactors(int num);
	
		/*** variables ***/
		//score is average reflex in seconds
		int score;
		//difficulty level (0=easy, 1=medium, 2=hard)
		int difficulty;
		std::string difficultyStr;
		std::string warning;
		int changeTimeMS;
		bool timeChange;
		std::vector<int> reactors;
		int vectorMax;
		std::random_device rd;
		int reaction;
		double speed;
		double minSpeed;	
		bool speedDecr;
		double multiplier;
		Communicator comm;
};//end of format class

#endif
