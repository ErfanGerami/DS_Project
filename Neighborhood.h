#pragma once
#include "Pair.cpp"
#include <iostream>
using namespace std;
class Neighborhood {
public:
	Neighborhood();
	Neighborhood(string name, int left, int right, int bottom, int top);
	Pair<Pair<int, int>, Pair<int, int>> getCoo()const ;
	string getName()const;
private:
	int left, right;
	int top, bottom;
	string name;
};