#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

static string getCurrentDate()
{
	time_t t = time(nullptr);
	tm* now = localtime(&t);
	char buf[32];
	snprintf(buf, sizeof(buf), "%04d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	return string(buf);
}

DataManager::DataManager()
{
	requestersFilePath = "data/requesters.txt";
	techniciansFilePath = "data/technicians.txt";
	requestsFilePath = "data/requests.txt";
	changelogsFilePath = "data/changelogs.txt";
	campusLocationsFilePath = "data/campus_locations.text";
	problemCategoriesFilePath = "data/problem_categories.txt";

	requestQueue = nullptr;
	changeLogList = nullptr;
}

DataManager::~DataManager()
{
	if (requestQueue != nullptr)
	{
		delete requestQueue;
		requestQueue = nullptr;
	}

	while (changeLogList != nullptr)
	{
		LinkedList* tmp = changeLogList->getNext();
		delete changeLogList;
		changeLogList = tmp;
	}

	for (size_t i = 0; i < changeLogs.size(); i++)
	{
		delete changeLogs[i];
	}
	changeLogs.clear();
}

vector<string> DataManager::split(const string& str, char delimiter)
{
	vector<string> tokens;
	string token;
	stringstream ss(str);
	while (getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

bool DataManager::loadAll()
{
	bool success = true;
	if (!loadRequesters()) success = false;
	if (!loadTechnicians()) success = false;
	if (!loadRequests()) success = false;
	if (!loadChangeLogs()) success = false;
	if (!loadCampusLocations()) success = false;
	if (!loadProblemCategories()) success = false;
	return success;
}

bool DataManager::saveAll()
{
	bool success = true;
	if (!saveRequesters()) success = false;
	if (!saveTechnicians()) success = false;
	if (!saveRequests()) success = false;
	if (!saveChangeLogs()) success = false;
	if (!saveCampusLocations()) success = false;
	if (!saveProblemCategories()) success = false;
	return success;
}

bool DataManager::loadRequesters()
{
	ifstream file(requestersFilePath);
	if (!file.is_open())
	{
		cerr << "Warning: Could not open " << requestersFilePath << " for reading." << endl;
		return false;
	}

	requesters.clear();
	string line;
	while (getline(file, line))
	{
		if (line.empty()) continue;
		vector<string> tokens = split(line, '|');
		if (tokens.size() >= 4)
		{
			int id = stoi(tokens[0]);
			string name = tokens[1];
			string email = tokens[2];
			string password = tokens[3];
			requesters.push_back(Requester(name, id, email, password));
		}
	}
	file.close();
	return true;
}

bool DataManager::loadTechnicians()
{
	ifstream file(techniciansFilePath);
	if (!file.is_open())
	{
		cerr << "Warning: Could not open " << techniciansFilePath << " for reading." << endl;
		return false;
	}

	technicians.clear();
	string line;
	while (getline(file, line))
	{
		if (line.empty()) continue;
		vector<string> tokens = split(line, '|');
		if (tokens.size() >= 4)
		{
			int id = stoi(tokens[0]);
			string name = tokens[1];
			string email = tokens[2];
			string password = tokens[3];
			technicians.push_back(Technician(name, id, email, password));
		}
	}
	file.close();
	return true;
}

bool DataManager::loadRequests()
{
	ifstream file(requestsFilePath);
	if (!file.is_open())
	{
		cerr << "Warning: Could not open " << requestsFilePath << " for reading." << endl;
		return false;
	}

	requests.clear();
	if (requestQueue != nullptr)
	{
		delete requestQueue;
		requestQueue = nullptr;
	}

	string line;
	while (getline(file, line))
	{
		if (line.empty()) continue;
		vector<string> tokens = split(line, '|');
		if (tokens.size() >= 5)
		{
			int id = stoi(tokens[0]);
			int requesterId = stoi(tokens[1]);
			int assignedTechId = stoi(tokens[2]);
			string location = tokens[3];
			string category = tokens[4];
			string desc = tokens.size() > 5 ? tokens[5] : "";
			string status = tokens.size() > 6 ? tokens[6] : "PENDING";
			string dateAssigned = tokens.size() > 7 ? tokens[7] : "";
			string targetDate = tokens.size() > 8 ? tokens[8] : "";
			string notes = tokens.size() > 9 ? tokens[9] : "";

			Request req(id, requesterId, location, category, targetDate, dateAssigned);
			req.setAssignedTechnicianID(assignedTechId);
			req.setRequestDescription(desc);
			req.setStatus(status);
			req.setDateAssignedToTechnician(dateAssigned);
			req.setTargetCompletionDate(targetDate);
			req.setRepairNotes(notes);

			requests.push_back(req);
		}
	}
	file.close();

	for (size_t i = 0; i < requests.size(); i++)
	{
		if (requests[i].getStatus() == "PENDING" || requests[i].getStatus() == "SUBMITTED")
		{
			if (requestQueue == nullptr)
			{
				requestQueue = new Queue(&requests[i]);
			}
			else
			{
				requestQueue->push(&requests[i]);
			}
		}
	}

	return true;
}

bool DataManager::loadChangeLogs()
{
	ifstream file(changelogsFilePath);
	if (!file.is_open())
	{
		cerr << "Warning: Could not open " << changelogsFilePath << " for reading." << endl;
		return false;
	}

	while (changeLogList != nullptr)
	{
		LinkedList* tmp = changeLogList->getNext();
		delete changeLogList;
		changeLogList = tmp;
	}

	for (size_t i = 0; i < changeLogs.size(); i++)
	{
		delete changeLogs[i];
	}
	changeLogs.clear();

	string line;
	while (getline(file, line))
	{
		if (line.empty()) continue;
		vector<string> tokens = split(line, '|');
		if (tokens.size() >= 3)
		{
			int reqId = stoi(tokens[0]);
			string date = tokens[1];
			string status = tokens[2];
			string notes = tokens.size() > 3 ? tokens[3] : "";

			ChangeLog* log = new ChangeLog(date, reqId, status, notes);
			changeLogs.push_back(log);
		}
	}
	file.close();

	LinkedList* tail = nullptr;
	for (size_t i = 0; i < changeLogs.size(); i++)
	{
		if (changeLogList == nullptr)
		{
			changeLogList = new LinkedList(changeLogs[i]);
			tail = changeLogList;
		}
		else
		{
			tail->updateNext(new LinkedList(changeLogs[i]));
			tail = tail->getNext();
		}
	}

	return true;
}

bool DataManager::loadCampusLocations()
{
	ifstream file(campusLocationsFilePath);
	if (!file.is_open())
	{
		file.open("data/campus_locations.txt");
		if (!file.is_open())
		{
			cerr << "Warning: Could not open campus locations file for reading." << endl;
			return false;
		}
	}

	campusLocations.clear();
	string line;
	while (getline(file, line))
	{
		if (!line.empty())
		{
			campusLocations.push_back(line);
		}
	}
	file.close();
	return true;
}

bool DataManager::loadProblemCategories()
{
	ifstream file(problemCategoriesFilePath);
	if (!file.is_open())
	{
		cerr << "Warning: Could not open " << problemCategoriesFilePath << " for reading." << endl;
		return false;
	}

	problemCategories.clear();
	string line;
	while (getline(file, line))
	{
		if (!line.empty())
		{
			problemCategories.push_back(line);
		}
	}
	file.close();
	return true;
}

bool DataManager::saveRequesters()
{
	ofstream file(requestersFilePath);
	if (!file.is_open())
	{
		cerr << "Error: Could not open " << requestersFilePath << " for writing." << endl;
		return false;
	}

	for (size_t i = 0; i < requesters.size(); i++)
	{
		file << requesters[i].getID() << "|"
		     << requesters[i].getName() << "|"
		     << requesters[i].getEmail() << "|"
		     << requesters[i].getPassword() << "\n";
	}
	file.close();
	return true;
}

bool DataManager::saveTechnicians()
{
	ofstream file(techniciansFilePath);
	if (!file.is_open())
	{
		cerr << "Error: Could not open " << techniciansFilePath << " for writing." << endl;
		return false;
	}

	for (size_t i = 0; i < technicians.size(); i++)
	{
		file << technicians[i].getID() << "|"
		     << technicians[i].getName() << "|"
		     << technicians[i].getEmail() << "|"
		     << technicians[i].getPassword() << "\n";
	}
	file.close();
	return true;
}

bool DataManager::saveRequests()
{
	ofstream file(requestsFilePath);
	if (!file.is_open())
	{
		cerr << "Error: Could not open " << requestsFilePath << " for writing." << endl;
		return false;
	}

	for (size_t i = 0; i < requests.size(); i++)
	{
		file << requests[i].getID() << "|"
		     << requests[i].getRequesterID() << "|"
		     << requests[i].getAssignedTechnicianID() << "|"
		     << requests[i].getCampusLocation() << "|"
		     << requests[i].getProblemCategory() << "|"
		     << requests[i].getRequestDescription() << "|"
		     << requests[i].getStatus() << "|"
		     << requests[i].getDateAssignedToTechnician() << "|"
		     << requests[i].getTargetCompletionDate() << "|"
		     << requests[i].getRepairNotes() << "\n";
	}
	file.close();
	return true;
}

bool DataManager::saveChangeLogs()
{
	ofstream file(changelogsFilePath);
	if (!file.is_open())
	{
		cerr << "Error: Could not open " << changelogsFilePath << " for writing." << endl;
		return false;
	}

	for (size_t i = 0; i < changeLogs.size(); i++)
	{
		file << changeLogs[i]->getRequestId() << "|"
		     << changeLogs[i]->getDate() << "|"
		     << changeLogs[i]->getStatus() << "|"
		     << changeLogs[i]->getRepairNotes() << "\n";
	}
	file.close();
	return true;
}

bool DataManager::saveCampusLocations()
{
	ofstream file(campusLocationsFilePath);
	if (!file.is_open())
	{
		cerr << "Error: Could not open " << campusLocationsFilePath << " for writing." << endl;
		return false;
	}

	for (size_t i = 0; i < campusLocations.size(); i++)
	{
		file << campusLocations[i] << "\n";
	}
	file.close();
	return true;
}

bool DataManager::saveProblemCategories()
{
	ofstream file(problemCategoriesFilePath);
	if (!file.is_open())
	{
		cerr << "Error: Could not open " << problemCategoriesFilePath << " for writing." << endl;
		return false;
	}

	for (size_t i = 0; i < problemCategories.size(); i++)
	{
		file << problemCategories[i] << "\n";
	}
	file.close();
	return true;
}

vector<Requester> DataManager::getRequesters()
{
	return requesters;
}

vector<Technician> DataManager::getTechnicians()
{
	return technicians;
}

vector<Request> DataManager::getRequests()
{
	return requests;
}

Queue* DataManager::getRequestQueue()
{
	return requestQueue;
}

LinkedList* DataManager::getChangeLogList()
{
	return changeLogList;
}

vector<ChangeLog*> DataManager::getChangeLogs()
{
	return changeLogs;
}

vector<string> DataManager::getCampusLocations()
{
	return campusLocations;
}

vector<string> DataManager::getProblemCategories()
{
	return problemCategories;
}

void DataManager::setRequesters(vector<Requester> requesters)
{
	this->requesters = requesters;
}

void DataManager::setTechnicians(vector<Technician> technicians)
{
	this->technicians = technicians;
}

void DataManager::setRequests(vector<Request> requests)
{
	this->requests = requests;
}

void DataManager::setChangeLogs(vector<ChangeLog*> changeLogs)
{
	this->changeLogs = changeLogs;

	while (changeLogList != nullptr)
	{
		LinkedList* tmp = changeLogList->getNext();
		delete changeLogList;
		changeLogList = tmp;
	}

	LinkedList* tail = nullptr;
	for (size_t i = 0; i < this->changeLogs.size(); i++)
	{
		if (changeLogList == nullptr)
		{
			changeLogList = new LinkedList(this->changeLogs[i]);
			tail = changeLogList;
		}
		else
		{
			tail->updateNext(new LinkedList(this->changeLogs[i]));
			tail = tail->getNext();
		}
	}
}

void DataManager::addChangeLog(int requestId, string status, string repairNotes, string date)
{
	if (date.empty())
	{
		date = getCurrentDate();
	}

	ChangeLog* log = new ChangeLog(date, requestId, status, repairNotes);
	changeLogs.push_back(log);

	if (changeLogList == nullptr)
	{
		changeLogList = new LinkedList(log);
	}
	else
	{
		LinkedList* tail = changeLogList;
		while (tail->getNext() != nullptr)
		{
			tail = tail->getNext();
		}
		tail->updateNext(new LinkedList(log));
	}

	saveChangeLogs();
}

void DataManager::setCampusLocations(vector<string> campusLocations)
{
	this->campusLocations = campusLocations;
}

void DataManager::setProblemCategories(vector<string> problemCategories)
{
	this->problemCategories = problemCategories;
}

void DataManager::setRequestersFilePath(string path)
{
	requestersFilePath = path;
}

void DataManager::setTechniciansFilePath(string path)
{
	techniciansFilePath = path;
}

void DataManager::setRequestsFilePath(string path)
{
	requestsFilePath = path;
}

void DataManager::setChangeLogsFilePath(string path)
{
	changelogsFilePath = path;
}

void DataManager::setCampusLocationsFilePath(string path)
{
	campusLocationsFilePath = path;
}

void DataManager::setProblemCategoriesFilePath(string path)
{
	problemCategoriesFilePath = path;
}

