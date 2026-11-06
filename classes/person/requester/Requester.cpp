#include "Requester.h"
#include "../../../data/DataManager.h"
#include "../../request/Request.h"
#include <iostream>
#include <string>

using namespace std;

Requester::Requester(string name, int id, string email, string password, DataManager* dataManager) 
	: Person(name, id, email, password, dataManager) {}

void Requester::displayMenu()
{
	cout << "\n========================================\n";
	cout << "           REQUESTER DASHBOARD          \n";
	cout << "========================================\n";
	cout << "1. Submit New Request\n";
	cout << "2. View Submitted Requests\n";
	cout << "3. View Request Details\n";
	cout << "4. Cancel Request\n";
	cout << "0. Logout\n";
	cout << "========================================\n";
}

void Requester::submitRequest()
{
	cout << "\n--- Submit New Maintenance Request ---\n";

	// 1. Select Campus Location
	StringLinkedList locations = dataManager->getCampusLocations();
	string selectedLocation = "";

	cout << "\nAvailable Campus Locations:\n";
	int locIndex = 1;
	for (StringNode* curr = locations.getHead(); curr != nullptr; curr = curr->getNext(), locIndex++)
	{
		cout << locIndex << ". " << curr->getData() << "\n";
	}
	cout << "Choose location (1-" << locations.size() << "): ";
	int locChoice;
	cin >> locChoice;
	selectedLocation = locations.getAt(locChoice - 1);

	// 2. Select Problem Category
	StringLinkedList categories = dataManager->getProblemCategories();
	string selectedCategory = "";

	cout << "\nAvailable Problem Categories:\n";
	int catIndex = 1;
	for (StringNode* curr = categories.getHead(); curr != nullptr; curr = curr->getNext(), catIndex++)
	{
		cout << catIndex << ". " << curr->getData() << "\n";
	}
	cout << "Choose category (1-" << categories.size() << "): ";
	int catChoice;
	cin >> catChoice;
	selectedCategory = categories.getAt(catChoice - 1);

	// 3. Enter Problem Description
	string description;
	cout << "\nEnter detailed description of the problem: ";
	getline(cin >> ws, description);

	// 4. Enter Target Completion Date
	string targetDate;
	cout << "Enter target completion date (YYYY-MM-DD): ";
	getline(cin >> ws, targetDate);

	// 5. Generate New Request ID (max ID + 1)
	RequestLinkedList requests = dataManager->getRequests();
	int newId = 1;
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() >= newId)
		{
			newId = curr->getData()->getID() + 1;
		}
	}

	// 6. Create and save new Request
	Request newReq(newId, this->getID(), selectedLocation, selectedCategory, targetDate, "");
	newReq.setRequestDescription(description);
	newReq.setStatus("PENDING");
	newReq.setAssignedTechnicianID(0);

	requests.append(newReq);
	dataManager->setRequests(requests);
	dataManager->saveRequests();

	string note = description.empty() ? "Request submitted" : "Request submitted: " + description;
	dataManager->addChangeLog(newId, "PENDING", note);

	cout << "\n[Success] Maintenance Request #" << newId << " submitted successfully!\n";
}

void Requester::viewSubmittedRequests()
{
	RequestLinkedList requests = dataManager->getRequests();
	bool found = false;

	cout << "\n--- Your Submitted Requests ---\n";
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		if (req->getRequesterID() == this->getID())
		{
			if (!found)
			{
				cout << "ID   | Status       | Location             | Category         | Target Date\n";
				cout << "----------------------------------------------------------------------------------------\n";
				found = true;
			}
			cout << "#" << req->getID() << "\t | "
			     << req->getStatus() << "\t | "
			     << req->getCampusLocation() << "\t | "
			     << req->getProblemCategory() << "\t | "
			     << req->getTargetCompletionDate() << "\n";
		}
	}

	if (!found)
	{
		cout << "[Info] You have not submitted any maintenance requests yet.\n";
	}
}

void Requester::viewRequestDetails()
{
	viewSubmittedRequests();

	int reqId;
	cout << "\nEnter Request ID to view full details: ";
	cin >> reqId;

	RequestLinkedList requests = dataManager->getRequests();
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		if (req->getID() == reqId)
		{
			if (req->getRequesterID() != this->getID())
			{
				cout << "[Error] Unauthorized. You can only view requests you submitted.\n";
				return;
			}

			cout << "\n================ Request Details ================\n";
			cout << "Request ID:               #" << req->getID() << "\n";
			cout << "Campus Location:          " << req->getCampusLocation() << "\n";
			cout << "Problem Category:         " << req->getProblemCategory() << "\n";
			cout << "Description:              " << req->getRequestDescription() << "\n";
			cout << "Status:                   " << req->getStatus() << "\n";

			if (req->getAssignedTechnicianID() > 0)
			{
				cout << "Assigned Technician ID:   " << req->getAssignedTechnicianID() << "\n";
				cout << "Date Assigned:            " << req->getDateAssignedToTechnician() << "\n";
				cout << "Target Completion Date:   " << req->getTargetCompletionDate() << "\n";
			}
			else
			{
				cout << "Assigned Technician:      Not yet assigned\n";
			}

			if (!req->getRepairNotes().empty())
			{
				cout << "Repair Notes:             " << req->getRepairNotes() << "\n";
			}
			cout << "=================================================\n";
			return;
		}
	}

	cout << "[Error] Request #" << reqId << " not found.\n";
}

void Requester::cancelRequest()
{
	viewSubmittedRequests();

	int reqId;
	cout << "\nEnter Request ID to cancel: ";
	cin >> reqId;

	RequestLinkedList requests = dataManager->getRequests();
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		if (req->getID() == reqId)
		{
			if (req->getRequesterID() != this->getID())
			{
				cout << "[Error] Unauthorized. You can only cancel your own requests.\n";
				return;
			}

			if (req->getStatus() == "COMPLETED")
			{
				cout << "[Error] Cannot cancel Request #" << reqId << " because it is already marked as COMPLETED.\n";
				return;
			}

			if (req->getStatus() == "CANCELLED")
			{
				cout << "[Info] Request #" << reqId << " is already CANCELLED.\n";
				return;
			}

			req->setStatus("CANCELLED");
			dataManager->setRequests(requests);
			dataManager->saveRequests();

			dataManager->addChangeLog(reqId, "CANCELLED", "Request cancelled by requester");

			cout << "\n[Success] Request #" << reqId << " has been cancelled.\n";
			return;
		}
	}

	cout << "[Error] Request #" << reqId << " not found.\n";
}
