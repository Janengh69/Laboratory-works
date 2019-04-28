/*******************************************
*file: List.h
*purpose: template class List declarations and definitions
*author: Dorosh Karuna
*written: 27/02/2019
*last modified: 27/02/2019
*********************************
************/
#include "Iterator.h"
#include "Bus.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
template <class T>
class List {

	struct ListNode {
		T data;
		ListNode * next;
		ListNode() {
			next = nullptr;
		}
		ListNode(T dat) {
			data = dat;
		}
		void Print() {
			std::cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;

	List();											
	~List();		
	//methods									

	void Print();
	void clear();	
	void pop_front();
	void push_front(const node_type val);
	void splice(iterator _Where, List<T>& _Right);
	
	int size();
	bool empty();	
	bool LoadFromCSV(char* filename, List<Bus> &base);
	void ChangeName(char* old_name, char* new_name);
	iterator begin();
	iterator end();
	iterator find(const node_type & val);											
	iterator remove(const node_type val);			
	iterator remove(iterator _where);				

private:
	node_type *head;
	iterator *first, *last;

};

//constructor
template <class T>
List<T>::List() {
	first = new iterator(nullptr);
	last = new iterator(nullptr);
	head = nullptr;
}

//destructor
template <class T>
List<T>::~List() {
	clear();
}

//Returns an iterator addressing the first element
template <class T>
typename List<T>::iterator List<T>::begin() {
	if (first->empty()) {
		return iterator(nullptr);
	}
	else {
		return iterator(*first);
	}
}

//Returns an iterator that addresses the location 
//succeeding the last element
template <class T>
typename List<T>::iterator List<T>::end() {
	return iterator(*last);
}

//Erases all the elements of a list.
template <class T>
void List<T>::clear() {
	ListNode* tmp;
	while (head) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

//Tests if a list is empty.
template <class T>
bool List<T>::empty() {
	return head == nullptr;
}

//Returns an iterator to the 
//first element in a list that match a specified value.
template <class T>
typename List<T>::iterator List<T>::find(const node_type& val) {
	iterator it = begin();
	for (; it != end(); it++) {
		if ((*it).data == val.data)	return it;
	}
	return it;
}

//Deletes the element at the beginning of a list.
template <class T>
void List<T>::pop_front() {
	ListNode *temp;
	if (!head) {
		return;
	}
	temp = head->next;
	delete head;
	head = temp;
	if (nullptr == temp) {
		delete first;
		delete last;
		return;
	}
	first = new iterator(head);
}

//Adds an element to the //beginning of a list.
template <class T>
void List<T>::push_front(node_type val) {
	if (nullptr != head) {
		node_type *temp; 
		temp = new ListNode(val);
		temp->next = head;
		head = temp;
		delete first;
		first = new iterator(head);
	}
	else {
		head = new node_type(val);
		head->next = nullptr;
		first = new iterator(head);
		last = new iterator(head);
	}
}

//Erases first element in a list that 
//match a specified value and returns iterator to position next to removed 
//element.
template <class T>
typename List<T>::iterator List<T>::remove(const node_type val) {
	node_type *node = head;
	node_type *temp;

	if (nullptr == head) return iterator(head);
	
	if (node->data == val.data){
		pop_front();
		return iterator(head);
	}

	for (; node->next != nullptr; node = node->next) {
		if (node->next->data == val.data) {
			temp = node->next->next;
			delete node->next;
			node->next = temp;
			return iterator(node->next);
		}
	}
	return iterator(node->next);
}

//Erases element from specified position and 
//2returns iterator to position next to removed element.
template <class T>
typename List<T>::iterator List<T>::remove(iterator _where) {
	iterator it = begin();
	iterator temp_it = it;
	node_type *temp_node;
	if (_where == it) {
		pop_front();
		return iterator(head);
	}
	for (; !it.empty(); it++) {
		if (_where == it)
		{
			temp_node = (*temp_it).next;
			(*temp_it).next = (*it).next;
			delete temp_node;
			temp_it++;
			return temp_it;
		}
		temp_it = it;
	}
	return it;
}
//Returns the number of elements in a list.
template <class T>
int List<T>::size() {
	int count = 0;
	if (head == nullptr) return count;
	iterator it = begin();
	while(!it.empty()) {
		count++;
		it++;
	}
	return count;
}
//Removes element from //the target list and inserts it in first
//position of the argument list.
template <class T>
void List<T>::splice(iterator _Where, List<T>& _Right) {
	if (!_Where.empty() || (!find((*_Where).data).empty())) {
		_Right.push_front((*_Where).data);
		remove(_Where);
	}
	else return;
}

//Dumps list into the screen
template <class T>
void List<T>::Print() {

	if (nullptr == head) std::cout << "List is empty" << std::endl;
	iterator *it = first;
	node_type *temp = head;

	while (nullptr != temp){
		std::cout << temp->data << "\n";
		temp = temp->next;
	}
}

//loading database from file 
template <class T>
bool List<T>::LoadFromCSV(char* filename, List<Bus> &base) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Can't open the file!" << std::endl;
		return false;
	}
	std::string word;
	std::string text;
	std::vector <char*> array;

	
	while (getline(file, text)) {
		std::stringstream ss(text);
		while (getline(ss, word, ';')) {
			char *cstr = new char[word.length() + 1];
			strcpy(cstr, word.c_str());
			array.push_back(cstr);
		}
		base.push_front(Bus(array[0], array[1], array[1]));
		array.erase(array.begin(), array.end());
	}
	return true;
}
template <class T>
void List<T>::ChangeName(char* old_name, char* new_name) {
	node_type *node = head;
	while (nullptr != node) {
		if (node->data == old_name) {
			node->data = new_name;
		}
		node = node->next;
	}
	
}