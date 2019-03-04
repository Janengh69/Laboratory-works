
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class ListNode {
public:
	char *data;
	ListNode *prev;
	ListNode *next;
public:
	ListNode();
	ListNode(char *_data);
	~ListNode();
};

class DoublyLinkedList {
	ListNode *head;
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	int size(); 

	bool empty();
	void clear(); 
	void push_back(const ListNode &);
	void push_front(const ListNode &);
	void pop_front();
	void pop_back();
	void insert_ord(const ListNode &);
	void sort();
	bool insert_after(char *dat, const ListNode &nd);
	void operator=(const DoublyLinkedList &);
	void merge(DoublyLinkedList &);
	void erase(char *dat);
	void unique();
	void assign(DoublyLinkedList &dl, int first, int last);
	void splice(int where, const DoublyLinkedList &dl);
	void splice(int where, const DoublyLinkedList &dl, int first, int
		last);

	void print();
	void print_bkw();

private:
	//службові функції
	void deleteNode(DoublyLinkedList* head_ref , ListNode* del)
	{
		if (head_ref == NULL || del == NULL)
			return;
		if (head_ref->head == del)
			head_ref->head = del->next;

		if (del->next != NULL ) {
			del->next->prev = del->prev;
			if(del->prev != NULL)
			del->prev->next = del->next;
		}

		if (del->prev != NULL)
			del->prev->next = del->next;
	}
};
