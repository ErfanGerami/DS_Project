#pragma once
#include <iostream>
#include "Pair.cpp"
using namespace std;
class Store {
public:
	Store();
	Store(Pair<int, int> coo, string name, bool is_original);
	Store(Pair<int, int> coo, string name,  string individual_name ,bool is_original);
	
	bool get_is_original()const;
	int get_x()const ;
	int get_y()const ;
	string get_name()const ;
	string get_individualName()const;

private:
	string name;
	string individual_name;
	Pair<int, int> coo;//coordinence
	bool is_original;


};


ostream& operator<<(ostream& out, const Store& s);