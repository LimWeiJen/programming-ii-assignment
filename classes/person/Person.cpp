#include "Person.h"
#include <string>

using namespace std;

Person::Person() : name(""), id(0), email(""), password(""), dataManager(nullptr) {}

Person::Person(string name, int id, string email, string password, DataManager* dataManager) 
	: name(name), id(id), email(email), password(password), dataManager(dataManager) {}

void Person::setName(string name) {
	this->name = name;
}

string Person::getName() {
    return name;
}

void Person::setID(int id) {
	this->id = id;
}

int Person::getID() {
    return id;
}

void Person::setEmail(string email) {
	this->email = email;
}

string Person::getEmail() {
    return email;
}

void Person::setPassword(string password) {
	this->password = password;
}

string Person::getPassword() {
	return password;
}

void Person::setDataManager(DataManager* dataManager) {
	this->dataManager = dataManager;
}

DataManager* Person::getDataManager() {
	return dataManager;
}

void Person::displaymenu() {
	// Virtual base method
}