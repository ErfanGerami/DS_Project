#include "Neighborhood.h"
Neighborhood::Neighborhood() = default;
Neighborhood::Neighborhood(string name,int left, int right, int bottom, int top) {
	this->right = right;
	this->left = left;
	this->bottom = bottom;
	this->top = top;
	this->name = name;
}

Pair<Pair<int, int>, Pair<int, int>> Neighborhood::getCoo()const  { return { {left,right},{bottom,top } }; }
string Neighborhood::getName()const { return this->name; }