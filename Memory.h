#ifndef MEMORY_H_
#define MEMORY_H_

#include <string>
#include <array>
#include <chrono>//dont know if i need time related
#include <cstdlib>

class Memory {
public:
	Memory();
	int runG();
	int number();
	int pattern();
	bool difficultyL(int level);
	bool check(int ck);
	int score;
	int level;
};

#endif /* MEMORY_H_ */
