/**********************************************************************************
* file: DoublyLinkedList.cpp
* synopsis: Realisation of class DoublyLinkedList and his methods to work with Node with help of related class ListNode. All the athods
* are declare in the include file "DoublyLikedList.h"
* author: Karyna Dorosh
* written : 22.11.2018
* last modified: 4.12.2018
**********************************************************************************/
#include "DoublyLinkedList.h"
#include <utility>
#include <list>
using namespace std;

ListNode::ListNode() {
	prev = next = nullptr;
	data = nullptr;
}
ListNode::ListNode(char *_data) {
	if (NULL == _data) {
		return;
	}
	else{
		prev = this;
		next = NULL;
		data = new char[strlen(_data) + 1];
		strcpy(data, _data);
	}
}

ListNode::~ListNode() {
	if (NULL != data) {
		data = NULL;
		delete[]data;
		if (prev != NULL)
			prev->~ListNode();
		if (next != NULL)
			next->~ListNode();
	}
}
DoublyLinkedList::DoublyLinkedList()
{	
	head = nullptr;
}

DoublyLinkedList::~DoublyLinkedList()
{
	clear();
}
//Returns the number of element	s in the list.
int DoublyLinkedList::size() {
	int size = 0;
	ListNode *temp_ptr = this->head;
	while (temp_ptr != NULL) {
		size++;
		temp_ptr = temp_ptr->next;
	}
	return size;
} 

//Returns true if empty, false otherwise.
bool DoublyLinkedList::empty() {
	if (head == nullptr)
		return true;
	else return false;
}

//Removes all elements from the list.
void DoublyLinkedList::clear() {
	this->unique();
	ListNode* q = this->head;
	while (q != NULL)
	{
		ListNode* del = new ListNode;
		del = q;
		q = q->next;
		delete del;
	}
	head = NULL;
}

// Adds node to the end of the list
void DoublyLinkedList::push_back(const ListNode &ls) {
	if (NULL == ls.data) { 
		cout << "Can't push NULL into list" << endl;
		return;
	}
	ListNode *new_node = new ListNode;
	ListNode* last = this->head;
	new_node->data = ls.data;//put the data
	new_node->next = NULL;//thi sew node is going to be the last node, so make next of it null
	if (this->head == NULL) { //if the linked list is empty make the new node as a head
		new_node->prev = NULL;
		this->head = new_node;
		return;
	}
	//else transverse till the last node
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = new_node;
	new_node->prev = last;
}

// Adds node to the front of the list.
void DoublyLinkedList::push_front(const ListNode &ls) {
	if (NULL == (ls.data)) {
		cout << "Can't push NULL into list" << endl;
		return;
	}
	ListNode *NewNode = new ListNode;    // allocate node
	NewNode->data = ls.data;    //put in the data 
	NewNode->next = this->head;    //Make next of NewNode as head and previous as NULL
	NewNode->prev = NULL;
	if (this->head != NULL)    //change prev of head node to new node
		this->head->prev = NewNode;
	// move the head to point to the new node
	this->head = NewNode;
}

// Removes the first element of the list.
void DoublyLinkedList::pop_front() {
	if (head == NULL) {
		printf("This list is already empty");
		return;
	}
	else {
		head = head->next;
		head->prev = NULL;
		if (head->next != NULL)
			head->next->prev = NULL;
	}
}

// Removes the last element of the list.
void DoublyLinkedList::pop_back() {
	if (head == NULL) {
		printf("This list is already empty");
		return;
	}
	ListNode *last = new ListNode;
	last = head;
	while (last->next != NULL) {
		last = last->next;
	}
	last->prev->next = NULL;
	free(last);
}

//Inserts node preserving list ordering
void DoublyLinkedList::insert_ord(const ListNode &ls) {
	if (NULL == ls.data) return;;
	ListNode *NewNode = new ListNode;
	ListNode *current = new ListNode;
	current = head;
	NewNode->data = ls.data;
	if (this == NULL) {    // check if the given previous node is NULL
		head = NewNode;
	}
	else if (strcmp(head->data, NewNode->data) >= 0) {
		NewNode->next = head;
		NewNode->next->prev = NewNode;
		head = NewNode;
	}
	else {
		current = head;
		while (current->next != NULL &&
			-1 == strcmp(current->next->data, NewNode->data))
			current = current->next;

		NewNode->next = current->next;

		// if the new node is not inserted 
		// at the end of the list 
		if (current->next != NULL)
			NewNode->next->prev = NewNode;

		current->next = NewNode;
		NewNode->prev = current;
	}
}
void DoublyLinkedList::sort(){
int swapped;
ListNode *current;
ListNode *pointer = NULL;

if (head->data == NULL) {
	return;
}

do
{
	swapped = 0;
	current = this->head;
	while (current->next != pointer){
			if (strcmp(current->data, current->next->data) > 0) {
				swap(current->next->data, current->data);
				swapped = 1;
			}
		
			current = current->next;
	}
	pointer = current;
} while (swapped);
}

// Inserts nd after the node with dat. Returns true on success 
bool DoublyLinkedList::insert_after(char *dat, const ListNode &nd) {
	if (this->head->data == NULL) {    // check if the given prev_node is NULL
		printf("The given node can't be NULL");
		return false;
	}
	ListNode *NewNode = new ListNode;
	ListNode *current = new ListNode;
	current = head;
	NewNode->data = nd.data;
	while ((NULL != current)&&(0 != strcmp(current->data, dat))) {
		current = current->next;
	}
	while ((NULL != current->next) && (current != current->next)) {
		current = current->next;
	}
	if (NULL == current) {
		return false;
	}
	else {
		if(current->next != NULL)
		current->next->prev = NewNode;
		NewNode->next = current->next;
		current->next = NewNode;
	}
	return true;
}
// Overloaded of the assignment
//operator
void DoublyLinkedList::operator=(const DoublyLinkedList &dll) {
	if (NULL != dll.head) {
		if (this != &dll) {
			this->head = dll.head;
		}
	}
}

//Removes the elements from the argument
/*видаляє елементи lst, втавляє їх у список й упорядковує отриманий список у порядку неубування*/
void DoublyLinkedList::merge(DoublyLinkedList &lst) {
	if (NULL == this->head) {
	}

	DoublyLinkedList * temp = new DoublyLinkedList;
	ListNode *current = new ListNode;
	current = lst.head;
	while (NULL != current) {
		temp->push_back(*current);
		current = current->next;
	}
	temp->sort();
	*this = *temp;	
	lst.clear();
}
//list, inserts them into the target list,  //and orders the new, combined set of //elements in nondescending order

// Removes all nodes with data
void DoublyLinkedList::erase(char *dat) {
	if (this == NULL) {    // check if the given prev_node is NULL
		printf("The given node can't be NULL");
	}
	ListNode *current = new ListNode;
	current = head;
	while (NULL != current) {
		if ((0 == strcmp(current->data, dat)) && (current->next != NULL)) {
			if (this->head == current)
				this->head = current->next;	
			if (current->next != NULL)
				current->next->prev = current->prev;
			if (current->prev != NULL)
				current->prev->next = current->next;
		}
		current = current->next;
	}
}

//Removes adjacent duplicate elements or adjacent elements
void DoublyLinkedList::unique() {
	if (NULL == head) return;
	ListNode *current_list= new ListNode;
	ListNode *current_this = new ListNode;
	current_this = head;
	current_list = head;
	int flag = 0;

	while (NULL != current_this) {
		while (NULL != current_list) {
			if (0 == strcmp(current_this->data, current_list->data)) 
				flag++;
			
			if (flag == 2) 
				deleteNode(this, current_this);
			current_list = current_list->next;

		}
		flag = 0;
		current_this = current_this->next;
		current_list = current_this;// there is no need to check previous
	}
}
//deletes elements
//from argument list between first and last positions and adds them to the end of target list

void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last) {
	ListNode *current = new ListNode;
	DoublyLinkedList * temp = new DoublyLinkedList;
	if (NULL == head) return;
	temp = &dl;
	current = dl.head;
	int i = 0;
	while ((i < first) &&( current != NULL)) {
		current = current->next;
		i++;
	}
	if (NULL == current) return;
	while((i <= last) && (current != NULL)) {
		temp->push_back(*current);
		temp->deleteNode(temp, current);
		i++;
		current = current->next;
	}
	
}
//inserts elements of argument list in target list starting from where position	
//if "where" is negative - inserts in the beginning and if where is bigger than size of list - inderts in the end of the list
void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl) {
	if (NULL == this->head) {
		*this = dl;
		return;
	}
	DoublyLinkedList *temp = new DoublyLinkedList;
	ListNode *current = new ListNode;
	ListNode *curr_dl = new ListNode;
	int i = 0;
	current = this->head;
	while (NULL != current && i < where) {
		i++;
		temp->push_back(*current);
		current = current->next;
	}
	curr_dl = dl.head;
	while (curr_dl != NULL) {
		
		temp->push_back(*curr_dl);
		curr_dl = curr_dl->next;
	}
	while (NULL != current) {
		temp->push_back(*current);
		current = current->next;
	}
	*this = *temp;
}

// inserts elements of argument list from first to last positions in target list starting from where position
/*вставляє елементи списку dl з позицій від first до last в поточний, починаючи з позиції where.*/
void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl, int first, int last) {
	DoublyLinkedList *temp = new DoublyLinkedList;
	ListNode *current = new ListNode;
	ListNode *curr_dl = new ListNode;
	int i = 0;
	current = this->head;
	while (NULL != current && i < where) {
		i++;
		temp->push_back(*current);
		current = current->next;
	}
	curr_dl = dl.head;
	i = 0;
	while (NULL != curr_dl && i < first) {
		curr_dl = curr_dl->next;
		i++;
	}
	while (curr_dl != NULL && i <= last) {
		temp->push_back(*curr_dl);
		curr_dl = curr_dl->next;
		i++;
	}
	while (NULL != current) {
		temp->push_back(*current);
		current = current->next;
	}
	*this = *temp;
}
//prints list
void DoublyLinkedList::print() {
	ListNode* last = new ListNode;
	last = this->head;
	//printf("List in a right direction: \n");
	while (last != NULL) {
		printf(" %s ", last->data);
		last = last->next;
	}
	printf("\n");
}
//prints list backward
void DoublyLinkedList::print_bkw() {
	ListNode* last = new ListNode;
	last = this->head;
	while (last->next != NULL) {
		last = last->next;
	}

	//printf("List in reverse order: \n");
	while (last != NULL) {
		cout << " " << last->data;
		last = last->prev;
	}
}