
#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
	DoublyLinkedList *ls = new DoublyLinkedList;
	char str[] = "sda";
	char str1[] = "programming";
	char str2[] = "algebra";
	char str3[] = "biology";
	ListNode nd1(str); 
	ListNode nd2(str1);
	ListNode nd3(str2);
	ListNode nd4(str3);

	DoublyLinkedList *empty = new DoublyLinkedList;
	
	cout <<"Function push_front: " << endl;
	ls->push_front(nd1);
	ls->push_front(nd3);	
	ls->push_front(nd2);
	ls->push_front(nd3);
	ls->push_front(nd2);
	ls->push_front(nd1);
	ls->push_front(nd1);
	ls->push_back(nd2);
	ls->push_back(nd1);
	ls->push_back(nd3);
	ls->push_back(nd3);
	ls->push_front(nd1);
	ls->print();

	cout << "\nTest of pop_front function (sda):" << endl;
	ls->pop_front();
	ls->print();

	cout << "\nTest of push_back (programming): " << endl;
	ls->push_back(nd2);
	ls->print();
	
	cout << "\nTest of pop_back function (programming): \n";
	ls->pop_back();
	ls->print();

	cout <<"\nTest of sort function: \n List before sorting:" << endl;
	ls->print();
	ls->sort();
	cout << "\nList after sorting:" << endl;
	ls->print();
	
	char str4[] = "computer science";
	ListNode nd5(str4);

	cout <<"\nTest of insert_ord function (computer science): \n";
	ls->insert_ord(nd5);
	ls->print();

	cout <<"\nTest of insert_after function (computer science after algebra ): ";
	cout << "\nThe return of insert_after " << ls->insert_after(str2, nd5) << "\n List after the call: \n";
	ls->print();
	
	cout <<"\nTest of operator= method:\n";
	DoublyLinkedList dll;
	DoublyLinkedList meh;
	dll = meh;
	dll.print();
	dll = (*ls);
	dll.print();
	
	cout <<"\nTest of erase method (algebra): \n";
	ls->erase(str2);
	ls->print();


	cout << "\n Test of print_bkw method: " << endl;
	ls->print_bkw();


	ls->push_front(nd4);
	ls->push_front(nd4);
	ls->push_back(nd2);

	cout << "\nList before the assign function: " << endl;
	ls->print();
	cout <<"\nTest of function assign from 0 index to 4: \n";
	ls->assign(*ls, 0, 4);
	ls->print();

	cout << "\n\nThe list before unique function: \n";
	ls->print();
	cout << "\nTest of unique method: \n";
	ls->unique();
	ls->print();

	DoublyLinkedList test;
	test.push_back(nd4);
	test.push_back(nd2);
	test.push_back(nd3);
	test.push_back(nd1);
	test.push_back(nd3);
	test.push_back(nd4);

	cout << "List that we insert: " << endl;
	test.print();
	cout << "\n Test of splice method: " << endl;
	ls->splice(2, test);
	ls->print();

	cout << "Test list:" << endl;
	test.print();
	cout << "\nTest of splice 2.0 method on the 2nd place the 2nd and the 3rd elements: " << endl;
	ls->splice(2, test, 2, 3);
	ls->print();

	empty->push_back(nd1);
	empty->push_back(nd2);
	cout << "\nTest of the method empty()  " << empty->empty() << endl;
	empty->clear();
	cout << "\nTest of the method empty() after cleaning the list " << empty->empty() << endl;

	cout << "\nTest of merge method: " << endl;
	DoublyLinkedList merge_test;
	merge_test.push_back(nd4);
	merge_test.push_back(nd2);
	merge_test.push_back(nd3);
	merge_test.push_back(nd1);
	merge_test.push_back(nd1);
	merge_test.push_back(nd3);
	cout << "List that we want to insert: " << endl;
	merge_test.print();
	cout << "List after the merge method: " << endl;
	empty->merge(merge_test);
	empty->print();
	system("pause");
	return 0;
}