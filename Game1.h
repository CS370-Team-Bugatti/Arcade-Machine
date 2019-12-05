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
	int run();
	std::vector<std::string> files;
	std::vector<Question> choices;
	int score;
    private:
	bool ansB(int size, int anss);
};//end of format class

//std::ostream &operator<<(std::ostream &out, const Format quest);

#endif
