#pragma once
template<typename T>
class LinkedList;
template<typename T>
class Iterator;

template<typename T>
class Node {
	friend class LinkedList<T>;
	friend class Iterator<T>;
	
public:
	Node(T data, Node<T>* next = nullptr,Node<T>* prev=nullptr) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
	T& get_data() { return this->data; }
	T get_data() const { return this->data; }
private:
	T data;
	Node<T>* next;
	Node<T>* prev;

};

template<typename T> 
class Iterator {
	
public:
	Iterator(Node<T>* node) {
		this->node = node;
	}
	Node<T>* operator*() const  {
		return node;
	}
	
	void operator++() {
		node = node->next;
	}
	bool operator!=(const Iterator<T>& second) {
		return (second.node != this->node);
	}
	
	Node<T>* node;
private:
};
template<typename T>
class LinkedList {
public:
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		this->size = 0;
	}
	Node<T>* push(T data) {
		if(!head) {
			head = new Node<T>(data);
			tail = head;
			size++;
			return tail;
		}
		else {
			tail->next = new Node<T>(data,nullptr,tail);
			tail = tail -> next;

			
		}
		size++;
		return tail;
	}
	Iterator<T> end() {
		return nullptr;
	}
	Iterator<T> begin() {
		return head;
	}
	T front() {
		if (this->size == 0) {
			throw "list is empty";
		}
		return head->data;
	}

	T back() {
		if (this->size == 0) {
			throw "list is empty";
		}
		return tail->data;
	}
	bool empty() {
		return !size;
	}
	void popFront() {
		if (!this->head) {
			throw "list is empty";
		}
		
		Node<T>* temp = this->head;
		this->head = temp->next;
		if (head) {

		this->head->prev = nullptr;
		}
		delete temp;
		this->size--;

	}
	
	template<typename F>
	void  deleteIf(F func) {
		Node<T>* temp = head;
		while ( temp&&!func(temp->data)) {
			temp=temp->next;
		}
		if (!temp)
			throw "not found";
		deleteByAdr(temp);
		if (temp == tail) {
			if (tail->prev) {
				tail = tail->prev;
			}
			else {
				this->head = nullptr;
				this->tail = nullptr;
			}
		}
		else if (temp == head) {
			if (head->next) {
				head = head->next;

			}
			else {
				head = nullptr;
				tail = nullptr;
			}
		}
		delete temp;
		
	}
	template<typename F>
	T getIf(F func) {
		Node<T>* temp = head;
		while (!func(temp->data) && temp) {
			temp->temp->next;
		}
		if (!temp)
			throw "not found";
		return temp->data;
	}

	void deleteByAdr(Node<T>* node) {
		/*this deletes the node but not free the memory*/
		if (node->prev) {
			node->prev->next = node->next;
		}
		if (node->next) {
			node->next->prev = node->prev;
		}
		if (node == tail) {
			if (tail->prev) {
				tail = tail->prev;
			}
			else {
				this->head = nullptr;
				this->tail = nullptr;
			}
		}
		else if (node == head) {
			if (head->next) {
				head = head->next;

			}
			else {
				head = nullptr;
				tail = nullptr;
			}
		}
		this ->size--;
	}
	int get_size() { return this->size; }
	void pushByAdr(Node<T>* node) {
		size++;
		if (!head) {
			this->head = node;
			node->next = nullptr;
			node->prev = nullptr;
			this->tail = head;
			return;

		}
		tail->next = node;
		node->prev = tail;
		node->next = nullptr;
		tail = tail->next;

	}
	LinkedList<T> copy() {
		LinkedList<T> temp;
		for (auto i : this) {
			temp.push(*i);
		}
	}
	
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
};