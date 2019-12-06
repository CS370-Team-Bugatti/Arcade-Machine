#ifndef GAME_1_INCLUDED
#define GAME_1_INCLUDED

#include <string>
#include <vector>
#include <chrono>

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
	int run();
	void addF(std::string nfile);
	void readGF();
	int runGame(const std::string fileName);
	void PrintScore();
	std::vector<std::string> files;
	std::vector<Question> choices;
	int score;
    private:
	bool ansB(int size, int anss);
};//end of format class

#endif
