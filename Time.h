#pragma once
#include "LinkedList.cpp"
#include "Store.h"
#include "Neighborhood.h"
#include "Vector.cpp"
class Time {
public:
	Time();
	Time(string branch_name, int time);
	void pushBackTime(LinkedList<Store>& stores, LinkedList<Neighborhood>& neighbors);
	string get_branchName();
	int get_time();
private:
	Vector<LinkedList<Node<Store>*>> stores;
	Vector<LinkedList<Node<Neighborhood>*>> neighbors;
	string branch_name;
	int time;
	


};