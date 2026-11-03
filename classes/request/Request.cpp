#include "Request.h"

using namespace std;

Request::Request() 
	: id(0), requesterId(0), assignedTechnicianId(0), description(""), 
	  dateAssignedToTechnician(""), targetCompletionDate(""), 
	  status("PENDING"), repairNotes(""), campusLocation(""), problemCategory("") {}

Request::Request(int id, int requesterId, string campusLocation, string problemCategory, string targetCompletionDate, string dateAssignedToTechnician) 
	: id(id), requesterId(requesterId), assignedTechnicianId(0), description(""), 
	  dateAssignedToTechnician(dateAssignedToTechnician), targetCompletionDate(targetCompletionDate), 
	  status("PENDING"), repairNotes(""), campusLocation(campusLocation), problemCategory(problemCategory) {}

void Request::setID(int id) {
	this->id = id;
}

int Request::getID() {
	return id;
}

void Request::setRequesterID(int requesterId) {
	this->requesterId = requesterId;
}

int Request::getRequesterID() {
	return requesterId;
}

void Request::setAssignedTechnicianID(int technicianId) {
	this->assignedTechnicianId = technicianId;
}

int Request::getAssignedTechnicianID() {
	return assignedTechnicianId;
}

void Request::setDateAssignedToTechnician(string dateAssignedToTechnician) {
	this->dateAssignedToTechnician = dateAssignedToTechnician;
}

string Request::getDateAssignedToTechnician() {
	return dateAssignedToTechnician;
}

void Request::setTargetCompletionDate(string targetCompletionDate) {
	this->targetCompletionDate = targetCompletionDate;
}

string Request::getTargetCompletionDate() {
	return targetCompletionDate;
}

void Request::setStatus(string status) {
	this->status = status;
}

string Request::getStatus() {
	return status;
}

void Request::setRepairNotes(string repairNotes) {
	this->repairNotes = repairNotes;
}

string Request::getRepairNotes() {
	return repairNotes;
}

void Request::setCampusLocation(string campusLocation) {
	this->campusLocation = campusLocation;
}

string Request::getCampusLocation() {
	return campusLocation;
}

void Request::setProblemCategory(string problemCategory) {
	this->problemCategory = problemCategory;
}

string Request::getProblemCategory() {
	return problemCategory;
}

void Request::setRequestDescription(string requestDescription) {
	this->description = requestDescription;
}

string Request::getRequestDescription() {
	return description;
}
