#include <iostream>
#pragma once

using namespace std;

inline int random(int min, int max)
{
	return rand() % (max - min) + min;
}