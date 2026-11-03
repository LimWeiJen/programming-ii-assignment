#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

class Request
{
public:
	Request();
	Request(int id, int requesterId, string campusLocation, string problemCategory, string targetCompletionDate = "", string dateAssignedToTechnician = "");

	void setID(int id);
	int getID();

	void setRequesterID(int requesterId);
	int getRequesterID();

	void setAssignedTechnicianID(int technicianId);
	int getAssignedTechnicianID();

	void setDateAssignedToTechnician(string dateAssignedToTechnician);
	string getDateAssignedToTechnician();
	
	void setTargetCompletionDate(string targetCompletionDate);
	string getTargetCompletionDate();

	void setStatus(string status);
	string getStatus();

	void setRepairNotes(string repairNotes);
	string getRepairNotes();

	void setCampusLocation(string campusLocation);
	string getCampusLocation();

	void setProblemCategory(string problemCategory);
	string getProblemCategory();

	void setRequestDescription(string description);
	string getRequestDescription();

private:
	int id;
	int requesterId;
	int assignedTechnicianId;
	string description;
	string dateAssignedToTechnician;
	string targetCompletionDate;
	string status;
	string repairNotes;
	string campusLocation;
	string problemCategory;
};

#endif
