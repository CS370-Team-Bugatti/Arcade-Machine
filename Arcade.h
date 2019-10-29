#ifndef ARCADE_H
#define ARCADE_H

#include <string>

class Arcade {
	public:
		// constructors
		Arcade(); // default constructor
		
		// methods
		void run(); // starts the Arcade Machine
		void selectGame(); // present options to user and get selection
		int executeGame(); // loads instance of selected game type
		std::string createRecord(); // creates record of gameplay in preparation to send
		bool sendRecord(); // sends record to database on another computer

		// data
		std::string game_selection;
		int score;
		std::string record;
};

#endif
