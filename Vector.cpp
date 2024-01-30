#pragma once
template<typename T>
class Vector {
public:
	
	Vector(int capacity=1){
		this->capacity = capacity;
		arr = new T[this->capacity];
		this->size = 0;
	}


	void push(T data) {
		if (!this->capacity) {
			arr = new T[1];
			arr[0] = data;
			this->size = 1;
			this -> capacity = 1;
			return;
		}
		if (size == capacity) {
			this->capacity *= 2;
			T* temp = new T[this->capacity];
			for (int i = 0; i < this->size; i++) {
				temp[i] = arr[i];
			}
			delete arr;
			arr = temp;
		}
		arr[size] = data;
		this->size++;
	}
	T& operator[](int index) {
		return arr[index];
	}
	int getSize() { return size; }
	void clear() {
		this->capacity = 0;
		this->size = 0;
		delete arr;
	}

private:
	T* arr;
	int capacity;
	int size;
	

};