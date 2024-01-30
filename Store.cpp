#include "Store.h"

Store::Store() = default;
Store::Store(Pair<int, int> coo, string name, bool is_original) {
	this->coo = coo;
	this->name = name;
	this->is_original = is_original;
	this->individual_name = name;
}
Store::Store(Pair<int, int> coo, string name, string individual_name, bool is_original) {
	this->coo = coo;
	this->name = name;
	this->is_original = is_original;
	this->individual_name = individual_name;
}

bool Store::get_is_original()const { return is_original; }
int Store::get_x()const { return coo.first; }
int Store::get_y()const { return coo.second; }
string Store::get_name()const { return name; }
string Store::get_individualName() const{ return this->individual_name; }

ostream& operator<<(ostream& out, const Store& store) {
	out << store.get_individualName() << (store.get_is_original() ? "*" : "("+store.get_name() + ")") << " located in ( " << store.get_x() << " , " << store.get_y() << " )";
	return out;
}