#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "../classes/person/requester/Requester.h"
#include "../classes/person/technician/Technician.h"
#include "../classes/request/Request.h"
#include "../data structures/queue/Queue.h"
#include "../data structures/linked list/LinkedList.h"
#include "../data structures/linked list/changelog/ChangeLog.h"
#include <vector>
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

	vector<Requester> getRequesters();
	vector<Technician> getTechnicians();
	vector<Request> getRequests();
	Queue* getRequestQueue();
	LinkedList* getChangeLogList();
	vector<ChangeLog*> getChangeLogs();
	vector<string> getCampusLocations();
	vector<string> getProblemCategories();

	void setRequesters(vector<Requester> requesters);
	void setTechnicians(vector<Technician> technicians);
	void setRequests(vector<Request> requests);
	void setChangeLogs(vector<ChangeLog*> changeLogs);
	void addChangeLog(int requestId, string status, string repairNotes, string date = "");
	void setCampusLocations(vector<string> campusLocations);
	void setProblemCategories(vector<string> problemCategories);

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

	vector<Requester> requesters;
	vector<Technician> technicians;
	vector<Request> requests;
	Queue* requestQueue;
	LinkedList* changeLogList;
	vector<ChangeLog*> changeLogs;
	vector<string> campusLocations;
	vector<string> problemCategories;

	vector<string> split(const string& str, char delimiter);
};

#endif

