/*******************************************
*file: BusTest.cpp
*purpose: testing mathods of classes List and Bus
*author: Dorosh Karuna
*written: 27/01/2019
*last modified: 27/01/2019
*********************************************/

#include "List.h"
int main() {
	Bus buses[] = {
		Bus("Joe", "CN132453","234"),
		Bus("Joy", "NB4842DS","87"),
		Bus("Mary", "LK6583LD","103"),
		Bus("Duke", "LD9567JT","45"),
		Bus("Liza", "CB3649HF", "33"),
		Bus(),
		Bus("Winton", "LR5674ER","345")
	};
	List<Bus> bus_list;
	Bus *driver = new Bus("Sentimental", "SF123493", "42");
	int sz = sizeof(buses) / sizeof(Bus);
	for (int i = 0; i < sz; i++)
		if (buses[i].getNameDriver() == nullptr)
			continue;
		else
			bus_list.push_front(buses[i]);
	bus_list.Print();
	std::cout << "\nTesting of push_front method (Sentimental): " << std::endl;
	bus_list.push_front(*driver);
	bus_list.Print();

	bus_list.pop_front();
	std::cout << "\nTesting of pop_front method: " << std::endl;
	bus_list.Print();
	std::cout <<"\nSize of the list is "<< bus_list.size() << std::endl;

	bus_list.remove(Bus("Mary", "LK6583LD", "103"));
	std::cout << "Testing of remove(const &val) method: " << std::endl;
	bus_list.Print();

	List<Bus>::iterator it  = bus_list.find(Bus("Winton", "LR5674ER", "345"));
	bus_list.remove(it);
	std::cout << "\nTesting of remove(iterator where) method: " << std::endl;
	bus_list.Print();
	std::cout << "\nTesting splice method (Duke): " << std::endl;
	List<Bus>::iterator it2 = bus_list.find(Bus("Duke", "LD9567JT", "45"));
	bus_list.splice(it2, bus_list);
	bus_list.Print();

	List<Bus> bus_list2;

	char filename[] = "Bus.csv";
	std::cout << "\nTesting of LoadFromCSV method: "<< bus_list2.LoadFromCSV(filename, bus_list2) << std::endl;
	bus_list2.Print();
	bus_list.clear();
	char* old_name = new char[512];
	strcpy(old_name, "Elisey");
	char* new_name = new char[512];
	strcpy(new_name, "Petya");
	std::cout << "\nTesting of ChangeName method (Elisey -> Petya): " << std::endl;
	bus_list2.ChangeName(old_name, new_name);
	bus_list2.Print();
	delete new_name;
	delete old_name;
	std::cout << "\nChecking if the first list is empty: " << bus_list.empty() << std::endl;
	std::cout << "\nChecking if the second list is empty: " << bus_list2.empty() << std::endl;

	system("pause");
	return 0;
	
}