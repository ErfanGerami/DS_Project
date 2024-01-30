#pragma once
#include "LinkedList.cpp"
template<typename T>
class Queue:public LinkedList<T> {
public:
	Queue() = default;
	
	
	void pop(){
		LinkedList<T>::popFront();
	}

	
private:
	using LinkedList<T>::get_size;
	using LinkedList<T>::deleteByAdr;
	using LinkedList<T>::getIf;
	using LinkedList<T>::deleteIf;



};