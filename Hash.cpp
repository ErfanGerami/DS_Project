#include "LinkedList.cpp"
template<typename T>
class Hash {
public:
	Hash() = default;

	void add(T data, int key) {
		arr[hash_function(key)].push(data);
	}

	LinkedList<T> get(int key) {
		return arr[hash_function(key)];
	}
	int hash_function(int key) {
		return key % size;
	}
	template<typename F>
	void deleteIf(int key, F func) {
		arr[hash_function(key)].deleteIf(func);
	}
	template<typename F>
	T& getIf(int key,F func){
		LinkedList<T> list=arr[hash_function(key)];
		for ( auto item : list) {
			if (func(item->get_data())) {
				return item->get_data();
			}

		}

		throw "there is nothing by that name";
	}
	
	
private:
	
	const int size = 701;
	LinkedList<T> arr[701];

};