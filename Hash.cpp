#include "LinkedList.cpp"
#include "Vector.cpp"
template<typename T>
class Hash {
public:
	Hash() = default;

	void add(T data, int key) {
		int target_index = hash_function(key);
		filled_indexes.push(target_index);
		arr[target_index].push(data);
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
	
	void clear() {
		for (int i = 0; i < filled_indexes.getSize(); i++) {
			arr[filled_indexes[i]].clear();
		}
	}
	Vector<int>& getFilledIndexes() { return filled_indexes; }
	LinkedList<T>* getArr() { return arr; }
private:
	Vector<int> filled_indexes;
	const int size = 701;
	LinkedList<T> arr[701];

};