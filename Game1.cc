#include "Game1.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

Question::Question(){
	ans = 0;
	question = "";
}//end of constructor

void Question::rd(std::istream &in){
	std::string s;
	getline(in, s);
	question = s;
	vector<string> temp;
	while(getline(in, s)){
		if(s.size() == 0)
			break;
		else{
			temp.push_back(s);
		}//end of else statement
	}//end of while loop
	for(auto s: temp){
		string ss = "";
		if(s[0] == ' ' || s[0] == '	'){//second one is a tab
			int ind = s.find_first_not_of(" 	");
			ss = s.substr(ind);
		}//end of if statement
		if(ss == "")
			ss = s;
		if(ss.size() == 1)
			ans = std::stoi(s);
		else if(ss.size() > 1){
			choice.push_back(s);
		}//end of else statement
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
	string a = choice[ans - 1];
	int ind = a.find_first_of('.');
	string sub = a.substr(ind+1);
	cout << sub << '\n';
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
	cout << "\033[2J\033[1;1H\n";
	cout << "Lets begin the Quiz!!!\n";
	while(file){
		Question q;
	 	q.rd(file);
		choices.push_back(q);	
	}
	int responce;
	for(int i = 0; i < 3; i++){
		cout << "\033[2J\033[1;1H\n";
		Question qq = choices[rand() % choices.size()];
		qq.PrintQA();
                cout << "Choose your answer: ";
		cin >> responce;
		int s = qq.choice.size();
		while(ansB(s,responce)){
			cout << "Choice out of range Try again\n";
			cout << "\033[2J\033[1;1H\n";
			qq.PrintQA();
			cin >> responce;
		}//end of while loop
		if(qq.answerCheck(responce)){
			std::cout << "Correct!!!";
			score++;
			qq.PrintA();
		}//end of if statement
		else{
			std::cout << "Incorrect. The Correct Answer is";
			qq.PrintA();
		}//end of else statement
	}//end of for loop
	PrintScore();
	return score;
}//end of run method

bool Quiz::ansB(int size, int anss){
	if(anss > size || anss < 0)
		return true;
	return false;
}//end of method

int Quiz::run(){
	string file;
	readGF();
	cout << "Choice a subject\n";
	for(auto s: files)
		cout << s << "	";
	cout << "Other\n";
	cin >> file;
	if(!(file.find("ther") > 1)){
		cout << "Upload file to pi\n"
			<< "What is the name of the file?\n";
		cin >> file;
		addF(file);
	}//end of if statement
return runGame(file);
}//end of run method

void Quiz::addF(std::string nfile){
	ofstream of("ff.txt", std::ofstream::out);
	for(auto s: files){
		of << s << "\n";
	}//end of for loop
	of << nfile;
	of.close();
}//end of addF

void Quiz::readGF(){
	ifstream in("ff.txt");
	string s;
	while(getline(in,s))
		files.push_back(s);
	in.close();
}//end of method
