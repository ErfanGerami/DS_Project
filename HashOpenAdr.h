#pragma once


#include <iostream>
#include "LinkedList.cpp"
#include "Store.h"
#include "Time.h"


class  HashOpenAdr {
public:
	HashOpenAdr(int capacity = 100);
	int hashFunction(int key, int i);
	Time* findTime(int time, string branch_name);
	LinkedList<Time>* findTime(int time);

	int find_empty(int key);

	int find_empty(int key, LinkedList<Time>* external_arr);
	void addTime(Time time);
	void addSubTime(int time, string branch_name, LinkedList<Store>& stores, LinkedList<Neighborhood>& neighbors);



private:
	Time* prev;
	LinkedList<Time>* arr;
	int capacity;


};