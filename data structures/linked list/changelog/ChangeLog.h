#ifndef CHANGE_LOG_H
#define CHANGE_LOG_H

#include <string>

using namespace std;

class ChangeLog
{
public:
	ChangeLog(string date, int requestId, string status, string repairNotes);

	void setDate(string date);
	string getDate();

	void setRequestId(int requestId);
	int getRequestId();

	void setStatus(string status);
	string getStatus();

	void setRepairNotes(string repairNotes);
	string getRepairNotes();
private:
	string date;
	int requestId;
	string status;
	string repairNotes;
};

#endif