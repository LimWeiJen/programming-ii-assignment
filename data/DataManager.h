#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "../classes/person/requester/Requester.h"
#include "../classes/person/technician/Technician.h"
#include "../classes/request/Request.h"
#include "../data structures/queue/Queue.h"
#include "../data structures/linked list/RequestLinkedList.h"
#include "../data structures/linked list/TechnicianLinkedList.h"
#include "../data structures/linked list/RequesterLinkedList.h"
#include "../data structures/linked list/ChangeLogLinkedList.h"
#include "../data structures/linked list/StringLinkedList.h"
#include "../data structures/linked list/changelog/ChangeLog.h"
#include <string>

using namespace std;

class DataManager
{
public:
	DataManager();
	~DataManager();

	bool loadAll();
	bool saveAll();

	bool loadRequesters();
	bool loadTechnicians();
	bool loadRequests();
	bool loadChangeLogs();
	bool loadCampusLocations();
	bool loadProblemCategories();

	bool saveRequesters();
	bool saveTechnicians();
	bool saveRequests();
	bool saveChangeLogs();
	bool saveCampusLocations();
	bool saveProblemCategories();

	RequesterLinkedList getRequesters();
	TechnicianLinkedList getTechnicians();
	RequestLinkedList getRequests();
	Queue* getRequestQueue();
	ChangeLogLinkedList getChangeLogs();
	StringLinkedList getCampusLocations();
	StringLinkedList getProblemCategories();

	void setRequesters(const RequesterLinkedList& requesters);
	void setTechnicians(const TechnicianLinkedList& technicians);
	void setRequests(const RequestLinkedList& requests);
	void setChangeLogs(const ChangeLogLinkedList& changeLogs);
	void addChangeLog(int requestId, string status, string repairNotes, string date = "");
	void setCampusLocations(const StringLinkedList& campusLocations);
	void setProblemCategories(const StringLinkedList& problemCategories);

	void setRequestersFilePath(string path);
	void setTechniciansFilePath(string path);
	void setRequestsFilePath(string path);
	void setChangeLogsFilePath(string path);
	void setCampusLocationsFilePath(string path);
	void setProblemCategoriesFilePath(string path);

private:
	string requestersFilePath;
	string techniciansFilePath;
	string requestsFilePath;
	string changelogsFilePath;
	string campusLocationsFilePath;
	string problemCategoriesFilePath;

	RequesterLinkedList requesters;
	TechnicianLinkedList technicians;
	RequestLinkedList requests;
	Queue* requestQueue;
	ChangeLogLinkedList changeLogs;
	StringLinkedList campusLocations;
	StringLinkedList problemCategories;

	StringLinkedList split(const string& str, char delimiter);
};

#endif
