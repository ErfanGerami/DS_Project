#include "Time.h"
Time::Time() = default;

Time::Time(string branch_name, int time) {
	this->branch_name = branch_name;
	this->time = time;
}
string Time::get_branchName() { return this->branch_name; }
int Time::get_time() { return this->time; }
void Time::pushBackTime(LinkedList<Store>& stores, LinkedList<Neighborhood>& neighbors) {
	LinkedList<Node<Store>*> stores_temp;
	LinkedList<Node<Neighborhood>*> neighbors_temp;
	this->branch_name = branch_name;
	for (auto store : stores) {
		stores_temp.push(store);
	}
	for (auto neighbor : neighbors) {
		neighbors_temp.push(neighbor);
	}
	this->neighbors.push(neighbors_temp);
	this->stores.push(stores_temp);
}
