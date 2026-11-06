#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class DataManager;

class Person
{
public:
	Person();
	Person(string name, int id, string email, string password, DataManager* dataManager = nullptr);

	void setName(string name);
	string getName();

	void setID(int id);
	int getID();

	void setEmail(string email);
	string getEmail();

	void setPassword(string password);
	string getPassword();

	void setDataManager(DataManager* dataManager);
	DataManager* getDataManager();

	virtual void displayMenu();

protected:
	DataManager* dataManager;

private:
	string name;
	int id;
	string email;
	string password;
};

#endif
