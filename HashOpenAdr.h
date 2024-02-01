#pragma once


#include <iostream>
#include "LinkedList.cpp"
#include "Store.h"
#include "Time.h"


class  HashOpenAdr {
public:
	HashOpenAdr(int capacity = 100) {
		this->capacity = capacity;
		this->arr = new LinkedList<Time>[capacity];
	}
	int hashFunction(int key, int i) {
		return (key + i * (key % (this->capacity - 1))) % this->capacity;
	}
	Time* findTime(int time, string branch_name) {
		for (int i = 0; i < this->capacity; i++) {
			int candidate = hashFunction(time, i);
			if (arr[candidate].get_size() != 0
				&& arr[candidate].front().get_time() == time) {
				for (auto target_time : arr[candidate]) {
					if (target_time->get_data().get_branchName() == branch_name) {
						return &target_time->get_data();
					}
				}
			}
		}
		return nullptr;

	}
	int find_empty(int key) {
		for (int i = 0; i < this->capacity; i++) {
			int candidate = hashFunction(key, i);
			if (arr[candidate].get_size() == 0 
				|| arr[candidate].front().get_time() == key) {
				return candidate;
			}
		}
		return -1;
	}

	int find_empty(int key, LinkedList<Time>* external_arr) {
		for (int i = 0; i < this->capacity; i++) {
			int candidate = hashFunction(key, i);
			if (external_arr[candidate].get_size() == 0 || external_arr[candidate].front().get_time() == key) {
				return candidate;
			}
		}
		return -1;
	}
	void addTime(Time time) {
		
		int index = find_empty(time.get_time());
		if (index == -1) {

			LinkedList<Time>* temp = new LinkedList<Time>[this->capacity * 2];
			for (int i = 0; i < this->capacity; i++) {
				temp[find_empty(arr[i].front().get_time(), temp)] = arr[i];

			}
			delete this->arr;
			this->arr = temp;

		}
		for (auto i : arr[index]) {
			if (i->get_data().get_branchName() == time.get_branchName()) {
				throw "there is a time with that specifics";
			}
		}
		this->arr[find_empty(time.get_time())].push(time);

	}
	void addSubTime(int time,string branch_name,LinkedList<Store>& stores, LinkedList<Neighborhood>& neighbors) {
		if (prev && prev->get_branchName() == branch_name && prev->get_time() == time) {
			prev->pushBackTime(stores, neighbors);
			return;
		}
		Time* target_time = findTime(time, branch_name);
		target_time->pushBackTime(stores, neighbors);
		prev = target_time;


	}



private:
	Time* prev;
	LinkedList<Time>* arr;
	int capacity;


};