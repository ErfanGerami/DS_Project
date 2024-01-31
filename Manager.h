#pragma once

#include "Vector.cpp"
#include "LinkedList.cpp"
#include "Hash.cpp"
#include "Store.h"
#include "Vector.cpp"
#include "Neighborhood.h"
#include "Merge.cpp"
#include "Pair.cpp"
#include <string>
#include <sstream>

#pragma warning(disable:4996)

#include "KDTree.h"

#include "HashOpenAdr.h"
#include <fstream>
#include <stdio.h>
class Manager {
public:

	Manager() ;
	void readFromFile(string path);
	void writeInFile(string path);
	void addStore(Store store,bool new_time);
	void addNeighborhood(Neighborhood neighborhood,  bool new_time);
	int convertToInt(const Store& store) const;
	int convertToInt(string name) const;
	void printLargest();
	void printCooByName(string name);
	void printKDTree_DEBUG();
	void printNearest(int x, int y) {
		Node<Store>* node = kdtree.findTheClosestPoint(x, y);
		cout << node->get_data();
	}
	void DEBUG(){//just for DEBUG purposes;
		
	}
	void changeTimeOrBranch(int time,int subtime,string branch);
	void deleteByCoo(int x, int y, bool new_time);
	void printNearestBranch(string name, int x, int y);
	void printInNeighbor(string name);
	void printAllBranches(string name);
	void printAllInRange(int x, int y, float R);
private:
	LinkedList<Store> stores;
	LinkedList<Store> deleted_stores;
	Hash<Node<Store>*> stores_hash;
	LinkedList<Neighborhood> neighbors;
	Hash<Node<Neighborhood>*> neighborhoods_hash;

	KDTree kdtree;
	Hash < Pair<string, KDTree>>  kdrees;
	HashOpenAdr timeline;
	string branch_name="master";
	int current_time=-1;
	

};