#include "Technician.h"
#include "../../../data/DataManager.h"
#include "../../request/Request.h"
#include <iostream>
#include <iomanip>
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
	RequestLinkedList requests = dataManager->getRequests();
	bool found = false;

	cout << "\n--- Your Assigned Requests ---\n";
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		if (req->getAssignedTechnicianID() == this->getID())
		{
			// Do not show completed or cancelled requests
			if (req->getStatus() == "COMPLETED" || req->getStatus() == "CANCELLED")
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
			cout << left << setw(6) << ("#" + to_string(req->getID())) << " | "
			     << setw(16) << req->getStatus() << " | "
			     << setw(20) << req->getCampusLocation() << " | "
			     << setw(16) << req->getProblemCategory() << " | "
			     << setw(14) << (req->getTargetCompletionDate().empty() ? "N/A" : req->getTargetCompletionDate()) << " | "
			     << (req->getDateAssignedToTechnician().empty() ? "N/A" : req->getDateAssignedToTechnician()) << "\n";
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

	RequestLinkedList requests = dataManager->getRequests();
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		if (req->getID() == reqId)
		{
			if (req->getAssignedTechnicianID() != this->getID())
			{
				cout << "[Error] Unauthorized. This request is not assigned to you.\n";
				return;
			}

			if (req->getStatus() == "COMPLETED" || req->getStatus() == "CANCELLED")
			{
				cout << "[Error] Request #" << reqId << " is already " << req->getStatus() << " and cannot be updated.\n";
				return;
			}

			cout << "\nCurrent Status: " << req->getStatus() << "\n";
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

			req->setStatus(newStatus);
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

	RequestLinkedList requests = dataManager->getRequests();
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		if (req->getID() == reqId)
		{
			if (req->getAssignedTechnicianID() != this->getID())
			{
				cout << "[Error] Unauthorized. This request is not assigned to you.\n";
				return;
			}

			if (req->getStatus() == "CANCELLED")
			{
				cout << "[Error] Request #" << reqId << " has been cancelled. Cannot add repair notes.\n";
				return;
			}

			string existingNotes = req->getRepairNotes();
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
				req->setRepairNotes(existingNotes + "; " + newNotes);
			}
			else
			{
				req->setRepairNotes(newNotes);
			}

			dataManager->setRequests(requests);
			dataManager->saveRequests();

			dataManager->addChangeLog(reqId, req->getStatus(), newNotes);

			cout << "\n[Success] Repair notes added to Request #" << reqId << ".\n";
			return;
		}
	}

	cout << "[Error] Request #" << reqId << " not found.\n";
}
