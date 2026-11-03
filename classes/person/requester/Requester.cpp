#include "Requester.h"
#include "../../../data/DataManager.h"
#include "../../request/Request.h"
#include <iostream>
#include <vector>
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
	vector<string> locations = dataManager->getCampusLocations();
	string selectedLocation = "";

	cout << "\nAvailable Campus Locations:\n";
	for (int i = 0; i < locations.size(); i++)
	{
		cout << (i + 1) << ". " << locations[i] << "\n";
	}
	cout << "Choose location (1-" << locations.size() << "): ";
	int locChoice;
	cin >> locChoice;
	selectedLocation = locations[locChoice - 1];

	// 2. Select Problem Category
	vector<string> categories = dataManager->getProblemCategories();
	string selectedCategory = "";

	cout << "\nAvailable Problem Categories:\n";
	for (int i = 0; i < categories.size(); i++)
	{
		cout << (i + 1) << ". " << categories[i] << "\n";
	}
	cout << "Choose category (1-" << categories.size() << "): ";
	int catChoice;
	cin >> catChoice;
	selectedCategory = categories[catChoice - 1];

	// 3. Enter Problem Description
	string description;
	cout << "\nEnter detailed description of the problem: ";
	getline(cin >> ws, description);

	// 4. Enter Target Completion Date
	string targetDate;
	cout << "Enter target completion date (YYYY-MM-DD): ";
	getline(cin >> ws, targetDate);

	// 5. Generate New Request ID (max ID + 1)
	vector<Request> requests = dataManager->getRequests();
	int newId = 1;
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getID() >= newId)
		{
			newId = requests[i].getID() + 1;
		}
	}

	// 6. Create and save new Request
	Request newReq(newId, this->getID(), selectedLocation, selectedCategory, targetDate, "");
	newReq.setRequestDescription(description);
	newReq.setStatus("PENDING");
	newReq.setAssignedTechnicianID(0);

	requests.push_back(newReq);
	dataManager->setRequests(requests);
	dataManager->saveRequests();

	string note = description.empty() ? "Request submitted" : "Request submitted: " + description;
	dataManager->addChangeLog(newId, "PENDING", note);

	cout << "\n[Success] Maintenance Request #" << newId << " submitted successfully!\n";
}

void Requester::viewSubmittedRequests()
{
	vector<Request> requests = dataManager->getRequests();
	bool found = false;

	cout << "\n--- Your Submitted Requests ---\n";
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getRequesterID() == this->getID())
		{
			if (!found)
			{
				cout << "ID   | Status       | Location             | Category         | Target Date\n";
				cout << "----------------------------------------------------------------------------------------\n";
				found = true;
			}
			cout << "#" << requests[i].getID() << "\t | "
			     << requests[i].getStatus() << "\t | "
			     << requests[i].getCampusLocation() << "\t | "
			     << requests[i].getProblemCategory() << "\t | "
			     << requests[i].getTargetCompletionDate() << "\n";
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

	vector<Request> requests = dataManager->getRequests();
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getID() == reqId)
		{
			if (requests[i].getRequesterID() != this->getID())
			{
				cout << "[Error] Unauthorized. You can only view requests you submitted.\n";
				return;
			}

			cout << "\n================ Request Details ================\n";
			cout << "Request ID:               #" << requests[i].getID() << "\n";
			cout << "Campus Location:          " << requests[i].getCampusLocation() << "\n";
			cout << "Problem Category:         " << requests[i].getProblemCategory() << "\n";
			cout << "Description:              " << requests[i].getRequestDescription() << "\n";
			cout << "Status:                   " << requests[i].getStatus() << "\n";

			if (requests[i].getAssignedTechnicianID() > 0)
			{
				cout << "Assigned Technician ID:   " << requests[i].getAssignedTechnicianID() << "\n";
				cout << "Date Assigned:            " << requests[i].getDateAssignedToTechnician() << "\n";
				cout << "Target Completion Date:   " << requests[i].getTargetCompletionDate() << "\n";
			}
			else
			{
				cout << "Assigned Technician:      Not yet assigned\n";
			}

			if (!requests[i].getRepairNotes().empty())
			{
				cout << "Repair Notes:             " << requests[i].getRepairNotes() << "\n";
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

	vector<Request> requests = dataManager->getRequests();
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getID() == reqId)
		{
			if (requests[i].getRequesterID() != this->getID())
			{
				cout << "[Error] Unauthorized. You can only cancel your own requests.\n";
				return;
			}

			if (requests[i].getStatus() == "COMPLETED")
			{
				cout << "[Error] Cannot cancel Request #" << reqId << " because it is already marked as COMPLETED.\n";
				return;
			}

			if (requests[i].getStatus() == "CANCELLED")
			{
				cout << "[Info] Request #" << reqId << " is already CANCELLED.\n";
				return;
			}

			requests[i].setStatus("CANCELLED");
			dataManager->setRequests(requests);
			dataManager->saveRequests();

			dataManager->addChangeLog(reqId, "CANCELLED", "Request cancelled by requester");

			cout << "\n[Success] Request #" << reqId << " has been cancelled.\n";
			return;
		}
	}

	cout << "[Error] Request #" << reqId << " not found.\n";
}
