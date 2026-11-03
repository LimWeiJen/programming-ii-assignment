#include "ChangeLog.h"
#include <string>

ChangeLog::ChangeLog(string date, int requestId, string status, string repairNotes) : date(date), requestId(requestId), status(status), repairNotes(repairNotes) {}

void ChangeLog::setDate(string date) {
	this->date = date;
}
string ChangeLog::getDate() {
	return date;
}

void ChangeLog::setRequestId(int requestId) {
	this->requestId = requestId;
}
int ChangeLog::getRequestId() {
	return requestId;
}

void ChangeLog::setStatus(string status) {
	this->status = status;
}
string ChangeLog::getStatus() {
	return status;
}

void ChangeLog::setRepairNotes(string repairNotes) {
	this->repairNotes = repairNotes;
}
string ChangeLog::getRepairNotes() {
	return repairNotes;
}