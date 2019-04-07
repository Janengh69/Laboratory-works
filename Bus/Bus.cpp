/*******************************************
*file: Bus.cpp
*purpose: template class Bus definition
*author: Dorosh Karuna
*written: 27/01/2019
*last modified: 02/02/2019
*********************************************/

#include "Bus.h"
#define _CRT_SECURE_NO_WARNINGS
Bus::Bus(const char* _driver, const char* _bus_number, const char* _rout_number)
{
	
	driver = new char[strlen(_driver)+1];
	bus_number = new char[strlen(_bus_number)+1];
	rout_number = new char[strlen(_rout_number)+1];
	strcpy(driver,_driver);
	strcpy(bus_number, _bus_number);
	strcpy(rout_number, _rout_number);
	
}
Bus::Bus(char* driver,char* bus_number, char* rout_number)
{
	this->driver = driver;
	this->bus_number = bus_number;
	this->rout_number = rout_number;
}
Bus::Bus()
{
	this->driver = nullptr;
	this->bus_number = nullptr;
	this->rout_number = nullptr;
}

char* Bus::getNameDriver() {
	return this->driver;
}
char* Bus::getBusNumber() {
	return this->bus_number;
}
char* Bus::getRoutNumber() {
	return this->rout_number;
}
void Bus::setNameDriver(char* name) {
	strcpy(this->driver, name);
}
void Bus::setBusNumber(char* bus_number) {
	strcpy(this->bus_number, bus_number);
}
void Bus::setRoutNumber(char* rout_number) {
	strcpy(this->rout_number, rout_number);
}
Bus &Bus::operator=(const Bus & b)
{
	if (NULL != b.driver) {
		this->driver = new char[strlen(b.driver)+1];
		this->bus_number = new char[strlen(b.bus_number)+1];
		this->rout_number = new char[strlen(b.rout_number) + 1];
		strcpy(driver, b.driver);
		strcpy(bus_number, b.bus_number);
		strcpy(rout_number, b.rout_number);
		return *this;
	}
}
Bus& Bus::operator = (char* new_name) {
	if (NULL != new_name){
	strcpy(this->driver, new_name);
	return*this;
	}
}

bool Bus::operator==(const Bus &obj) {
	if (obj.driver == NULL) return false;
	return strcmp(driver, obj.driver) == 0;
}

bool Bus::operator==(char* name) {
	if (NULL == name) return false;
	return strcmp(driver, name) == 0;
}
std::ostream & operator<<(std::ostream & stream, Bus & obj)
{
		std::cout << "Driver's Name: " << obj.driver << " Bus number: " << obj.bus_number << " Route number: " << obj.rout_number;
		return stream;
}