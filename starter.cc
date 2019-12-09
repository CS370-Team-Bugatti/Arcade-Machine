#include "Arcade.h"
#include <iostream>
#include <string>

int main() {
	Arcade a;
	bool play = true;
	while (play == true) {
		a.run();
		
		std::cout << "Would you like to play another game? (yes or no)\n";
		std::string response;
		while (true) {
			
			std::cin >> response;
			if (response == "yes") {
				play = true;
				break;
			} else if (response == "no") {
				play = false;
				break;
			} else {
				// nothing
			}
		}
	}
	return 0;
}
