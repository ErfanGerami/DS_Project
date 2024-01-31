#pragma once
#include "LinkedList.cpp"
#include "Store.h"
#include "Neighborhood.h"
#include "Vector.cpp"
class Time {
	friend class Manager;
public:
	Time();
	Time(string branch_name, int time);
	void pushBackTime(LinkedList<Store>& stores, LinkedList<Neighborhood>& neighbors);
	string get_branchName();
	int get_time();
	Vector<LinkedList<Node<Store>*>> stores;
	Vector<LinkedList<Node<Neighborhood>*>> neighbors;
private:
	string branch_name;
	int time;
	


};