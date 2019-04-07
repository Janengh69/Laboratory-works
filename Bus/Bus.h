/*******************************************
*file: Bus.h
*purpose: template class Bus declaration
*author: Dorosh Karuna
*written: 27/01/2019
*last modified: 27/01/2019
*********************************************/
#pragma warning(disable : 4996)
#include <iostream>

class Bus
{
public:
	Bus(const char*, const char*, const char*);
	Bus( char*, char*, char*);
	Bus();

	char* getNameDriver();
	char* getBusNumber();
	char* getRoutNumber();
	void setNameDriver(char*);
	void setBusNumber(char*);
	void setRoutNumber(char*);
	Bus& operator = (const Bus & orig);
	Bus& operator = (char*);
	bool operator==(const Bus &obj);
	bool operator==(char* name);
	friend std::ostream& operator<<(std::ostream& stream, Bus &obj);


private: 
	char* driver;
	char* bus_number;
	char* rout_number;
};
