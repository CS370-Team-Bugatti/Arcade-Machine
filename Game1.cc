#include "Game1.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Question::Question(){
	ans = 0;
	question = "";
}//end of constructor

void Question::rd(std::istream &in){
	std::string s;
	getline(in, s);
	question = s;
	while(getline(in, s)){
		if(s.size() == 0)
			break;
		else if(s.size() == 1)
			ans = std::stoi(s);
		else{
			choice.push_back(s);
		}//emd of else statement
	}//end of while loop
}//end of constructor

void Question::PrintQA(){
	std::cout << question << '\n';
	int size = choice.size();
	for(int i = 0; i < size; i++){
		std::cout << choice[i] << '\n';
	}//end of for loop
}//end of method
	
void Question::PrintA(){
	std::cout << choice[ans - 1] << '\n';
}//end of method

bool Question::answerCheck(int ansO){
	if(ansO == ans)
		return true;
	else
		return false;
}//end of method

Quiz::Quiz(){
	score = 0;
}//end of constructor

void Quiz::PrintScore(){
	std::cout << "Your Final score is " << score << "\n";
}//end of method

int Quiz::runGame(const std::string fileName){
	std::ifstream file(fileName);
	while(file){
		Question q;
	 	q.rd(file);
		choices.push_back(q);	
	}
	int responce;
	for(int i = 0; i < 6; i++){
		Question qq = choices[rand() % choices.size()];
		qq.PrintQA();
                cout << "choose your answer\n";
		cin >> responce;
		int s = qq.choice.size();
		if(responce > s || responce < 0)//can take this of later
			cerr << " responds not Allowed\n";
		if(qq.answerCheck(responce)){
			std::cout << "Correct!!!";
			score++;
			qq.PrintA();
		}//end of if statement
		else{
			std::cout << "Incorrect. The Corect Answer is";
			qq.PrintA();
		}//end of else statementr
	}//end of for loop
	PrintScore();
	return score;
}//end of run method