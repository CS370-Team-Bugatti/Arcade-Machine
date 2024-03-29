#include "Memory.h"
#include "Communicator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
/*
#include <thread>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
*/
using namespace std;

Memory::Memory() {
	score = 0;
	level = 0;
}//end of cons

int Memory::runG(){
	cout << "\033[1J\033[1;1H" << endl;
	cout << "Can You Remember?\n"
			<< "Lets see ;) :)\n";
	int dif;
	cout << "Select a Level\n";
	cout << "1. Easy		2. Medium	   3.Hard\n";
	cin >> dif;
	while(!difficultyL(dif)){
		cin >> dif;
	}//end of while loop
	cout << "\033[1J\033[1;1H" << endl;//clear screen
	level = dif;
	//option between number or patters
	cout << "1: Patterns	2: Numbers\n";
	cin >> dif;
	int sco = 0;
	if(dif == 1)
		sco = pattern();
	if(dif == 2)
		sco = number();
	return sco;
}//end of run method

bool Memory::check(int ck){
	if(ck > 2 || ck <= 0){
		cout << "Choice is invalid try again\n";
		return false;
	}//end of if statement
	return true;
}//end of check method

int Memory::number(){
	int ch;
	int num;
	cout << "\033[2J\033[1;1H" << endl;//clear screen
	cout << "1: PI        2: Random Number\n";
	cin >> ch;
	while(!check(ch)){
		cin >> ch;
	}//end of while loop statement
	if(level == 1){
			num = 10;
	}
	else if(level == 2){
		num = 30;
	}
	else {
		num = 50;
	}
	cout << "\033[2J\033[1;1H" << endl;//clear screen
	if(ch == 1){
		cout << "Note: we will only take up to the difficulty level\n";
		ifstream inn("Pi.txt");
		vector<char> pi;
		char f;
		while(inn >> f){
			pi.push_back(f);
		}//end of while loop
		cout << "Okay lets start!!!!\nGive us your number\n3.";
		inn.close();
		string s;
		cin >> s;
		for(int i = 0; i < num; i++){
			if(s[i] == pi[i])
				score++;
		}//end of for loop
		cout << "Your score is " << score << " out of " << num << '\n';
	}//end of if statement
	else{
		int size;
		vector<int> ran;
		if(level == 1){
			size = 10;
		}else if(level == 2){
			size = 15;
		}else{
			size = 30;
		}
		for(int i = 0; i < size; i++){
			int temp = rand()%9;
			ran.push_back(temp);
		}
		cout << "The Number is: ";
		for(auto i: ran)
			cout << i;
//		_sleep(num);
		cout << "\nYou will get " << num << " seconds look at the numbers displayed on the screen\n";
		cout << "\nTime starts Now!!\n";
		sleep(num);
//		_sleep(1);
		cout << "Time has end\n";
		sleep(1);
		cout << "\033[2J\033[1;1H" << endl;//clear screen
		cout << "Now what do you remember?\n";
		string s;
		cin >> s;
		for(int i = 0; i < num; i++){
			if(s[i] == ran[i])
				score++;
		}//end of for loop
		cout << "At the end you remember " << score << " out of " << num << '\n';
	}//end of else statement
	return score;
}//end of method

int Memory::pattern(){
	int time;
	int num;
	if(level == 1){
		time = 60;
		num = 10;
	}
	else if(level == 2){
		time = 45;
		num = 15;
	}
	else {
		time = 30;
		num = 30;
	}
	Communicator input;
	cout << "You will get " << time << " seconds look at the pattern displayed on the screen, After that you will have to react if the X is in that position\n";
	cout << "We will see what you remember\n";
	vector<char> pp;
	for(int i = 1; i <= num; i++){
		int temp = rand()%2;
		if(temp == 0)
			pp.push_back('x');
		else{
			pp.push_back('+');
		}//end of else statement
	}//end of for loop
	sleep(2);
	for(auto c: pp)
		cout << c;
	cout << "\nTime starts now\n";
//	_sleep(num);
	sleep(time);
	cout << "Time has ended\n";
//	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sleep(1);
	cout << "\033[2J\033[1;1H" << endl;//clear screen
	cout << "Now what did you remember\n";
	char p;
	for(int i = 1; i <= num; i++){
		cout << "\n\n" << i << ". Was there an x here?\n\n";
		bool t = input.getMotion(1, true);//should always be 10000 akay 10s
	//	cout << input.getMotion(1) << "\n";
	//	bool t = true;
	//	cout << boolalpha << "bool: " << t << "\n";
		if(t)
			p = 'x';
		else
			p = '+';
		if(p == pp[i])
			score++;
		cout << '\n';
	}//end of for loop
	cout << "This is the score " << score << '\n';

	return score;
}//end of pattern method

bool Memory::difficultyL(int level){
	if(level <= 0 || level > 3){
		cout << "The level you choice does not exit try again\n";
		return false;
	}//end of if statement
	return true;
}//end of dificultyL method
