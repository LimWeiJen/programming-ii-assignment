#include "Technician.h"
#include "../../../data/DataManager.h"
#include "../../request/Request.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

Technician::Technician(string name, int id, string email, string password, DataManager* dataManager) 
	: Person(name, id, email, password, dataManager) {}

void Technician::displayMenu()
{
	cout << "\n========================================\n";
	cout << "          TECHNICIAN DASHBOARD          \n";
	cout << "========================================\n";
	cout << "1. View Assigned Requests\n";
	cout << "2. Update Request Status\n";
	cout << "3. Add Repair Notes\n";
	cout << "0. Logout\n";
	cout << "========================================\n";
}

void Technician::getCurrentAssignedRequests()
{
	vector<Request> requests = dataManager->getRequests();
	bool found = false;

	cout << "\n--- Your Assigned Requests ---\n";
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getAssignedTechnicianID() == this->getID())
		{
			// Do not show completed or cancelled requests
			if (requests[i].getStatus() == "COMPLETED" || requests[i].getStatus() == "CANCELLED")
			{
				continue;
			}

			if (!found)
			{
				cout << left << setw(6) << "ID" << " | "
				     << setw(16) << "Status" << " | "
				     << setw(20) << "Location" << " | "
				     << setw(16) << "Category" << " | "
				     << setw(14) << "Target Date" << " | "
				     << "Date Assigned\n";
				cout << "----------------------------------------------------------------------------------------------------\n";
				found = true;
			}
			cout << left << setw(6) << ("#" + to_string(requests[i].getID())) << " | "
			     << setw(16) << requests[i].getStatus() << " | "
			     << setw(20) << requests[i].getCampusLocation() << " | "
			     << setw(16) << requests[i].getProblemCategory() << " | "
			     << setw(14) << (requests[i].getTargetCompletionDate().empty() ? "N/A" : requests[i].getTargetCompletionDate()) << " | "
			     << (requests[i].getDateAssignedToTechnician().empty() ? "N/A" : requests[i].getDateAssignedToTechnician()) << "\n";
		}
	}

	if (!found)
	{
		cout << "[Info] No active requests currently assigned to you.\n";
	}
}

void Technician::updateRequestStatus()
{
	getCurrentAssignedRequests();

	int reqId;
	cout << "\nEnter Request ID to update status: ";
	if (!(cin >> reqId))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "[Error] Invalid input. Please enter a valid numeric Request ID.\n";
		return;
	}

	vector<Request> requests = dataManager->getRequests();
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getID() == reqId)
		{
			if (requests[i].getAssignedTechnicianID() != this->getID())
			{
				cout << "[Error] Unauthorized. This request is not assigned to you.\n";
				return;
			}

			if (requests[i].getStatus() == "COMPLETED" || requests[i].getStatus() == "CANCELLED")
			{
				cout << "[Error] Request #" << reqId << " is already " << requests[i].getStatus() << " and cannot be updated.\n";
				return;
			}

			cout << "\nCurrent Status: " << requests[i].getStatus() << "\n";
			cout << "Select New Status:\n";
			cout << "1. IN_PROGRESS\n";
			cout << "2. PENDING_PARTS\n";
			cout << "3. COMPLETED\n";
			cout << "Choose status (1-3): ";
			int choice;
			if (!(cin >> choice))
			{
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "[Error] Invalid choice.\n";
				return;
			}

			string newStatus = "";
			if (choice == 1) newStatus = "IN_PROGRESS";
			else if (choice == 2) newStatus = "PENDING_PARTS";
			else if (choice == 3) newStatus = "COMPLETED";
			else
			{
				cout << "[Error] Invalid status selection.\n";
				return;
			}

			requests[i].setStatus(newStatus);
			dataManager->setRequests(requests);
			dataManager->saveRequests();

			dataManager->addChangeLog(reqId, newStatus, "Status updated to " + newStatus + " by Technician " + this->getName());

			cout << "\n[Success] Status for Request #" << reqId << " updated to " << newStatus << ".\n";
			return;
		}
	}

	cout << "[Error] Request #" << reqId << " not found.\n";
}

void Technician::addRepairNotes()
{
	getCurrentAssignedRequests();

	int reqId;
	cout << "\nEnter Request ID to add repair notes: ";
	if (!(cin >> reqId))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "[Error] Invalid input. Please enter a valid numeric Request ID.\n";
		return;
	}

	vector<Request> requests = dataManager->getRequests();
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getID() == reqId)
		{
			if (requests[i].getAssignedTechnicianID() != this->getID())
			{
				cout << "[Error] Unauthorized. This request is not assigned to you.\n";
				return;
			}

			if (requests[i].getStatus() == "CANCELLED")
			{
				cout << "[Error] Request #" << reqId << " has been cancelled. Cannot add repair notes.\n";
				return;
			}

			string existingNotes = requests[i].getRepairNotes();
			if (!existingNotes.empty())
			{
				cout << "Current Notes: " << existingNotes << "\n";
			}

			cin.ignore(10000, '\n');
			string newNotes;
			cout << "Enter repair notes: ";
			getline(cin, newNotes);

			if (newNotes.empty())
			{
				cout << "[Error] Repair notes cannot be empty.\n";
				return;
			}

			if (!existingNotes.empty())
			{
				requests[i].setRepairNotes(existingNotes + "; " + newNotes);
			}
			else
			{
				requests[i].setRepairNotes(newNotes);
			}

			dataManager->setRequests(requests);
			dataManager->saveRequests();

			dataManager->addChangeLog(reqId, requests[i].getStatus(), newNotes);

			cout << "\n[Success] Repair notes added to Request #" << reqId << ".\n";
			return;
		}
	}

	cout << "[Error] Request #" << reqId << " not found.\n";
}
