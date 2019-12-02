#ifndef GAME_2_INCLUDED
#define GAME_2_INCLUDED

#include <vector>
#include <string>

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
	
		/*** variables ***/
		//score is average reflex in seconds
		int score;
		//what needs to be reacted to
		//std::vector<int> reactors;
		//difficulty level (0=easy, 1=medium, 2=hard)
		int difficulty;
		//boolean for whether or not a reaction is expected
		bool reaction;
		std::string difficultyStr;
		std::string warning;
};//end of format class

#endif
