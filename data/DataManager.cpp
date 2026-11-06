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
}

DataManager::~DataManager()
{
	if (requestQueue != nullptr)
	{
		delete requestQueue;
		requestQueue = nullptr;
	}
}

StringLinkedList DataManager::split(const string& str, char delimiter)
{
	StringLinkedList tokens;
	string token;
	stringstream ss(str);
	while (getline(ss, token, delimiter))
	{
		tokens.append(token);
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
		StringLinkedList tokens = split(line, '|');
		if (tokens.size() >= 4)
		{
			int id = stoi(tokens.getAt(0));
			string name = tokens.getAt(1);
			string email = tokens.getAt(2);
			string password = tokens.getAt(3);
			requesters.append(Requester(name, id, email, password));
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
		StringLinkedList tokens = split(line, '|');
		if (tokens.size() >= 4)
		{
			int id = stoi(tokens.getAt(0));
			string name = tokens.getAt(1);
			string email = tokens.getAt(2);
			string password = tokens.getAt(3);
			technicians.append(Technician(name, id, email, password));
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
		StringLinkedList tokens = split(line, '|');
		if (tokens.size() >= 5)
		{
			int id = stoi(tokens.getAt(0));
			int requesterId = stoi(tokens.getAt(1));
			int assignedTechId = stoi(tokens.getAt(2));
			string location = tokens.getAt(3);
			string category = tokens.getAt(4);
			string desc = tokens.size() > 5 ? tokens.getAt(5) : "";
			string status = tokens.size() > 6 ? tokens.getAt(6) : "PENDING";
			string dateAssigned = tokens.size() > 7 ? tokens.getAt(7) : "";
			string targetDate = tokens.size() > 8 ? tokens.getAt(8) : "";
			string notes = tokens.size() > 9 ? tokens.getAt(9) : "";

			Request req(id, requesterId, location, category, targetDate, dateAssigned);
			req.setAssignedTechnicianID(assignedTechId);
			req.setRequestDescription(desc);
			req.setStatus(status);
			req.setDateAssignedToTechnician(dateAssigned);
			req.setTargetCompletionDate(targetDate);
			req.setRepairNotes(notes);

			requests.append(req);
		}
	}
	file.close();

	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		if (req->getStatus() == "PENDING" || req->getStatus() == "SUBMITTED")
		{
			if (requestQueue == nullptr)
			{
				requestQueue = new Queue(req);
			}
			else
			{
				requestQueue->push(req);
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

	changeLogs.clear();

	string line;
	while (getline(file, line))
	{
		if (line.empty()) continue;
		StringLinkedList tokens = split(line, '|');
		if (tokens.size() >= 3)
		{
			int reqId = stoi(tokens.getAt(0));
			string date = tokens.getAt(1);
			string status = tokens.getAt(2);
			string notes = tokens.size() > 3 ? tokens.getAt(3) : "";

			ChangeLog* log = new ChangeLog(date, reqId, status, notes);
			changeLogs.append(log);
		}
	}
	file.close();

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
			campusLocations.append(line);
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
			problemCategories.append(line);
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

	for (RequesterNode* curr = requesters.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Requester* req = curr->getData();
		file << req->getID() << "|"
		     << req->getName() << "|"
		     << req->getEmail() << "|"
		     << req->getPassword() << "\n";
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

	for (TechnicianNode* curr = technicians.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Technician* tech = curr->getData();
		file << tech->getID() << "|"
		     << tech->getName() << "|"
		     << tech->getEmail() << "|"
		     << tech->getPassword() << "\n";
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

	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		file << req->getID() << "|"
		     << req->getRequesterID() << "|"
		     << req->getAssignedTechnicianID() << "|"
		     << req->getCampusLocation() << "|"
		     << req->getProblemCategory() << "|"
		     << req->getRequestDescription() << "|"
		     << req->getStatus() << "|"
		     << req->getDateAssignedToTechnician() << "|"
		     << req->getTargetCompletionDate() << "|"
		     << req->getRepairNotes() << "\n";
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

	for (ChangeLogNode* curr = changeLogs.getHead(); curr != nullptr; curr = curr->getNext())
	{
		ChangeLog* log = curr->getData();
		file << log->getRequestId() << "|"
		     << log->getDate() << "|"
		     << log->getStatus() << "|"
		     << log->getRepairNotes() << "\n";
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

	for (StringNode* curr = campusLocations.getHead(); curr != nullptr; curr = curr->getNext())
	{
		file << curr->getData() << "\n";
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

	for (StringNode* curr = problemCategories.getHead(); curr != nullptr; curr = curr->getNext())
	{
		file << curr->getData() << "\n";
	}
	file.close();
	return true;
}

RequesterLinkedList DataManager::getRequesters()
{
	return requesters;
}

TechnicianLinkedList DataManager::getTechnicians()
{
	return technicians;
}

RequestLinkedList DataManager::getRequests()
{
	return requests;
}

Queue* DataManager::getRequestQueue()
{
	return requestQueue;
}

ChangeLogLinkedList DataManager::getChangeLogs()
{
	return changeLogs;
}

StringLinkedList DataManager::getCampusLocations()
{
	return campusLocations;
}

StringLinkedList DataManager::getProblemCategories()
{
	return problemCategories;
}

void DataManager::setRequesters(const RequesterLinkedList& requesters)
{
	this->requesters = requesters;
}

void DataManager::setTechnicians(const TechnicianLinkedList& technicians)
{
	this->technicians = technicians;
}

void DataManager::setRequests(const RequestLinkedList& requests)
{
	this->requests = requests;
}

void DataManager::setChangeLogs(const ChangeLogLinkedList& changeLogs)
{
	this->changeLogs = changeLogs;
}

void DataManager::addChangeLog(int requestId, string status, string repairNotes, string date)
{
	if (date.empty())
	{
		date = getCurrentDate();
	}

	ChangeLog* log = new ChangeLog(date, requestId, status, repairNotes);
	changeLogs.append(log);

	saveChangeLogs();
}

void DataManager::setCampusLocations(const StringLinkedList& campusLocations)
{
	this->campusLocations = campusLocations;
}

void DataManager::setProblemCategories(const StringLinkedList& problemCategories)
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
