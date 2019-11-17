#ifndef GAME_1_INCLUDED
#define GAME_1_INCLUDED

#include <string>
#include <vector>

class Question{
    public:
	Question();
	void PrintQA();
	void PrintA();
	std::vector<std::string> choice;
	int ans;
	std::string question;
	bool answerCheck(int ansO);
	void rd(std::istream &in);
};//end of question 

class Quiz{
    public:
	Quiz();
	int runGame(const std::string fileName);
	void PrintScore();
	std::vector<Question> choices;
	int score;
};//end of format class

//std::ostream &operator<<(std::ostream &out, const Format quest);

#endif