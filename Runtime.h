#include "Bot.h"
#include <string>
#include <map>
#include <iostream>
#include "Const.h"
#include "util.cpp"
#include <vector>

using namespace std;

#pragma once
class Runtime
{
public:
	Runtime();
	~Runtime();

	void step();

	bool grid[WORLD_WIDTH][WORLD_HEIGHT];
	//int updated[WORLD_WIDTH][WORLD_HEIGHT];

private:
	//map<string, Bot> bots;
	std::vector<Bot> bots;

	bool isLive(int x, int y);
	bool isNeedDelete(unsigned int x, unsigned int y, map<std::string, Dead>& empty);
	bool isNeedCreate(unsigned int x, unsigned int y);
	bool outOfGrid(int x, int y);
	void pushToMap(unsigned int x, unsigned int y, map<std::string, Dead>& empty);
	std::string genKey(unsigned int x, unsigned int y);
};

