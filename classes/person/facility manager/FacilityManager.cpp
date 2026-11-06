#include "FacilityManager.h"
#include "../../../data/DataManager.h"
#include "../../request/Request.h"
#include "../requester/Requester.h"
#include "../technician/Technician.h"
#include "../../../data structures/queue/Queue.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

FacilityManager::FacilityManager(string name, int id, string email, string password, DataManager* dataManager) 
	: Person(name, id, email, password, dataManager) {}

void FacilityManager::displayMenu()
{
	cout << "\n========================================\n";
	cout << "       FACILITY MANAGER DASHBOARD       \n";
	cout << "========================================\n";
	cout << "1.  View All Technicians\n";
	cout << "2.  Add New Technician\n";
	cout << "3.  Remove Technician\n";
	cout << "4.  Review Latest Pending Request (Queue)\n";
	cout << "5.  Review / Filter All Requests\n";
	cout << "6.  Assign Technician to Current Request\n";
	cout << "7.  View All Users\n";
	cout << "8.  Remove User\n";
	cout << "9.  View All Campus Locations\n";
	cout << "10. Add Campus Location\n";
	cout << "11. Remove Campus Location\n";
	cout << "12. View All Problem Categories\n";
	cout << "13. Add Problem Category\n";
	cout << "14. Remove Problem Category\n";
	cout << "15. View Service History (Change Logs)\n";
	cout << "0.  Logout\n";
	cout << "========================================\n";
}

void FacilityManager::viewTechnicians()
{
	TechnicianLinkedList allTechnicians = getAllTechnicians();

	if (allTechnicians.empty())
	{
		cout << "\n[Info] No technicians registered in the system.\n";
		return;
	}

	cout << "\n--- Registered Technicians ---\n";
	for (TechnicianNode* curr = allTechnicians.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Technician* tech = curr->getData();
		cout << "ID: " << tech->getID()
		     << " | Name: " << tech->getName()
		     << " | Email: " << tech->getEmail() << "\n";
	}
}

void FacilityManager::addTechnician()
{
	TechnicianLinkedList allTechnicians = getAllTechnicians();

	int newId = 1;
	for (TechnicianNode* curr = allTechnicians.getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() >= newId)
		{
			newId = curr->getData()->getID() + 1;
		}
	}

	string name, email, password;
	cout << "\n--- Add New Technician ---\n";
	cout << "Auto-generated Technician ID: " << newId << "\n";
	cout << "Enter Technician Name: ";
	cin >> name;
	cout << "Enter Technician Email: ";
	cin >> email;
	cout << "Enter Technician Password: ";
	cin >> password;

	Technician newTech(name, newId, email, password, dataManager);
	allTechnicians.append(newTech);

	dataManager->setTechnicians(allTechnicians);
	dataManager->saveTechnicians();

	cout << "\n[Success] Technician \"" << name << "\" (ID: " << newId << ") added successfully!\n";
}

void FacilityManager::removeTechnician(int technicianId)	
{
	TechnicianLinkedList allTechnicians = getAllTechnicians();
	string techName = "";
	for (TechnicianNode* curr = allTechnicians.getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() == technicianId)
		{
			techName = curr->getData()->getName();
			break;
		}
	}

	bool removed = allTechnicians.removeById(technicianId);

	if (removed)
	{
		cout << "[Success] Technician \"" << techName 
		     << "\" (ID: " << technicianId << ") has been removed.\n";
		dataManager->setTechnicians(allTechnicians);
		dataManager->saveTechnicians();
	}
	else
	{
		cout << "[Error] Technician with ID " << technicianId << " not found.\n";
	}
}

void FacilityManager::reviewLatestRequest()
{
	Queue* currentQueue = getCurrentRequestQueue();
	if (currentQueue == nullptr || currentQueue->size() == 0)
	{
		cout << "\n[Info] No pending requests in the queue to review.\n";
		return;
	}

	Request* currentRequest = currentQueue->front();
	cout << "\n--- Latest Pending Request (1 of " << currentQueue->size() << ") ---\n";
	cout << "Request ID:       " << currentRequest->getID() << "\n";
	cout << "Requester ID:     " << currentRequest->getRequesterID() << "\n";
	cout << "Location:         " << currentRequest->getCampusLocation() << "\n";
	cout << "Category:         " << currentRequest->getProblemCategory() << "\n";
	cout << "Description:      " << currentRequest->getRequestDescription() << "\n";
	cout << "Status:           " << currentRequest->getStatus() << "\n";
	cout << "Target Date:      " << currentRequest->getTargetCompletionDate() << "\n";
	cout << "Date Assigned:    " << currentRequest->getDateAssignedToTechnician() << "\n";
}

void FacilityManager::reviewRequests()
{
	RequestLinkedList allRequests = getAllRequests();
	if (allRequests.empty())
	{
		cout << "\n[Info] No requests found in the system.\n";
		return;
	}

	cout << "\n================ Filter Requests ================\n";
	cout << "1. View All Requests\n";
	cout << "2. Filter by Problem Category\n";
	cout << "3. Filter by Campus Location\n";
	cout << "4. Filter by Assigned Technician\n";
	cout << "5. Filter by Overdue Requests\n";
	cout << "Choose option (1-5): ";
	int filterChoice;
	cin >> filterChoice;

	RequestLinkedList filtered;

	if (filterChoice == 1)
	{
		filtered = allRequests;
	}
	else if (filterChoice == 2)
	{
		StringLinkedList categories = dataManager->getProblemCategories();
		if (categories.empty())
		{
			cout << "[Info] No problem categories available.\n";
			return;
		}

		cout << "\nSelect Category:\n";
		int catIndex = 1;
		for (StringNode* curr = categories.getHead(); curr != nullptr; curr = curr->getNext(), catIndex++)
		{
			cout << catIndex << ". " << curr->getData() << "\n";
		}
		cout << "Choose category (1-" << categories.size() << "): ";
		int catChoice;
		cin >> catChoice;
		string selectedCategory = categories.getAt(catChoice - 1);

		for (RequestNode* curr = allRequests.getHead(); curr != nullptr; curr = curr->getNext())
		{
			if (curr->getData()->getProblemCategory() == selectedCategory)
			{
				filtered.append(*(curr->getData()));
			}
		}
	}
	else if (filterChoice == 3)
	{
		StringLinkedList locations = dataManager->getCampusLocations();
		if (locations.empty())
		{
			cout << "[Info] No campus locations available.\n";
			return;
		}

		cout << "\nSelect Campus Location:\n";
		int locIndex = 1;
		for (StringNode* curr = locations.getHead(); curr != nullptr; curr = curr->getNext(), locIndex++)
		{
			cout << locIndex << ". " << curr->getData() << "\n";
		}
		cout << "Choose location (1-" << locations.size() << "): ";
		int locChoice;
		cin >> locChoice;
		string selectedLocation = locations.getAt(locChoice - 1);

		for (RequestNode* curr = allRequests.getHead(); curr != nullptr; curr = curr->getNext())
		{
			if (curr->getData()->getCampusLocation() == selectedLocation)
			{
				filtered.append(*(curr->getData()));
			}
		}
	}
	else if (filterChoice == 4)
	{
		viewTechnicians();
		int techId;
		cout << "Enter Technician ID to filter by: ";
		cin >> techId;

		for (RequestNode* curr = allRequests.getHead(); curr != nullptr; curr = curr->getNext())
		{
			if (curr->getData()->getAssignedTechnicianID() == techId)
			{
				filtered.append(*(curr->getData()));
			}
		}
	}
	else if (filterChoice == 5)
	{
		string currentDate;
		cout << "Enter current date to check overdue status (YYYY-MM-DD): ";
		cin >> currentDate;

		for (RequestNode* curr = allRequests.getHead(); curr != nullptr; curr = curr->getNext())
		{
			Request* req = curr->getData();
			if (req->getStatus() != "COMPLETED" && req->getStatus() != "CANCELLED")
			{
				string target = req->getTargetCompletionDate();
				if (!target.empty() && target < currentDate)
				{
					filtered.append(*req);
				}
			}
		}
	}
	else
	{
		cout << "[Error] Invalid filter option.\n";
		return;
	}

	if (filtered.empty())
	{
		cout << "\n[Info] No requests found matching the selected criteria.\n";
		return;
	}

	cout << "\n--- Matching Requests (" << filtered.size() << " found) ---\n";
	cout << "ID   | Status          | Location             | Category         | Tech ID    | Target Date\n";
	cout << "----------------------------------------------------------------------------------------------------\n";
	for (RequestNode* curr = filtered.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Request* req = curr->getData();
		cout << "#" << req->getID() << "\t | "
		     << req->getStatus() << "\t | "
		     << req->getCampusLocation() << "\t | "
		     << req->getProblemCategory() << "\t | "
		     << (req->getAssignedTechnicianID() == 0 ? "Unassigned" : to_string(req->getAssignedTechnicianID())) << "\t | "
		     << (req->getTargetCompletionDate().empty() ? "None" : req->getTargetCompletionDate()) << "\n";
	}

	cout << "\nEnter Request ID to view full details (or 0 to return): ";
	int detailId;
	if (cin >> detailId && detailId != 0)
	{
		bool found = false;
		for (RequestNode* curr = filtered.getHead(); curr != nullptr; curr = curr->getNext())
		{
			Request* req = curr->getData();
			if (req->getID() == detailId)
			{
				cout << "\n================ Request #" << req->getID() << " Details ================\n";
				cout << "Requester ID:             " << req->getRequesterID() << "\n";
				cout << "Campus Location:          " << req->getCampusLocation() << "\n";
				cout << "Problem Category:         " << req->getProblemCategory() << "\n";
				cout << "Status:                   " << req->getStatus() << "\n";
				cout << "Target Completion Date:   " << (req->getTargetCompletionDate().empty() ? "None" : req->getTargetCompletionDate()) << "\n";
				cout << "Date Assigned:            " << (req->getDateAssignedToTechnician().empty() ? "Not assigned" : req->getDateAssignedToTechnician()) << "\n";
				cout << "Assigned Technician ID:   " << (req->getAssignedTechnicianID() == 0 ? "None" : to_string(req->getAssignedTechnicianID())) << "\n";
				cout << "Description:              " << (req->getRequestDescription().empty() ? "None" : req->getRequestDescription()) << "\n";
				cout << "Repair Notes:             " << (req->getRepairNotes().empty() ? "None" : req->getRepairNotes()) << "\n";
				cout << "========================================================\n";
				found = true;
				break;
			}
		}
		if (!found)
		{
			cout << "[Error] Request #" << detailId << " not found in matching list.\n";
		}
	}
}

void FacilityManager::assignTechnician(int technicianId)
{
	Queue* currentQueue = getCurrentRequestQueue();
	if (currentQueue == nullptr || currentQueue->size() == 0)
	{
		cout << "\n[Error] No pending requests in the queue to assign.\n";
		return;
	}

	// Verify that the technician exists
	TechnicianLinkedList allTechnicians = getAllTechnicians();
	bool techExists = false;
	string techName = "";
	for (TechnicianNode* curr = allTechnicians.getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() == technicianId)
		{
			techExists = true;
			techName = curr->getData()->getName();
			break;
		}
	}

	if (!techExists)
	{
		cout << "\n[Error] Technician with ID " << technicianId << " does not exist.\n";
		return;
	}

	Request* currentRequest = currentQueue->front();
	int reqId = currentRequest->getID();

	string assignDate;
	cout << "Enter date assigned to technician (YYYY-MM-DD): ";
	cin >> assignDate;

	// Update the full requests list in DataManager
	RequestLinkedList requests = getAllRequests();
	for (RequestNode* curr = requests.getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() == reqId)
		{
			curr->getData()->setAssignedTechnicianID(technicianId);
			curr->getData()->setDateAssignedToTechnician(assignDate);
			curr->getData()->setStatus("IN_PROGRESS");
			break;
		}
	}

	dataManager->setRequests(requests);
	dataManager->saveRequests();

	dataManager->addChangeLog(reqId, "IN_PROGRESS", "Assigned to Technician " + techName + " (ID: " + to_string(technicianId) + ")", assignDate);

	// Pop the assigned request from the pending queue so next pending request moves to front
	currentQueue->pop();

	cout << "\n[Success] Assigned Technician \"" << techName 
	     << "\" (ID: " << technicianId << ") to Request #" << reqId << ".\n";
}

void FacilityManager::viewUsers()
{
	RequesterLinkedList allRequesters = getAllRequester();

	if (allRequesters.empty())
	{
		cout << "\n[Info] No registered users (requesters) found.\n";
		return;
	}

	cout << "\n--- Registered Users (Requesters) ---\n";
	for (RequesterNode* curr = allRequesters.getHead(); curr != nullptr; curr = curr->getNext())
	{
		Requester* req = curr->getData();
		cout << "ID: " << req->getID()
		     << " | Name: " << req->getName()
		     << " | Email: " << req->getEmail() << "\n";
	}
}

void FacilityManager::removeUser()
{
	RequesterLinkedList allRequesters = getAllRequester();
	if (allRequesters.empty())
	{
		cout << "\n[Info] No users available to remove.\n";
		return;
	}

	viewUsers();

	int userId;
	cout << "\nEnter User ID to remove: ";
	cin >> userId;

	string userName = "";
	for (RequesterNode* curr = allRequesters.getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() == userId)
		{
			userName = curr->getData()->getName();
			break;
		}
	}

	bool removed = allRequesters.removeById(userId);

	if (removed)
	{
		cout << "[Success] User \"" << userName 
		     << "\" (ID: " << userId << ") has been removed.\n";
		dataManager->setRequesters(allRequesters);
		dataManager->saveRequesters();
	}
	else
	{
		cout << "[Error] User with ID " << userId << " not found.\n";
	}
}

void FacilityManager::viewAllCampusLocations()
{
	StringLinkedList locations = dataManager->getCampusLocations();
	if (locations.empty())
	{
		cout << "\n[Info] No campus locations recorded.\n";
		return;
	}

	cout << "\n--- Campus Locations ---\n";
	int idx = 1;
	for (StringNode* curr = locations.getHead(); curr != nullptr; curr = curr->getNext(), idx++)
	{
		cout << idx << ". " << curr->getData() << "\n";
	}
}

void FacilityManager::addCampusLocation()
{
	string newLocation;
	cout << "\nEnter new campus location: ";
	cin >> newLocation;

	if (newLocation.empty())
	{
		cout << "[Error] Location name cannot be empty.\n";
		return;
	}

	StringLinkedList locations = dataManager->getCampusLocations();
	if (locations.contains(newLocation))
	{
		cout << "[Error] Location \"" << newLocation << "\" already exists.\n";
		return;
	}

	locations.append(newLocation);
	dataManager->setCampusLocations(locations);
	dataManager->saveCampusLocations();

	cout << "[Success] Campus location \"" << newLocation << "\" added successfully.\n";
}

void FacilityManager::removeCampusLocation()
{
	StringLinkedList locations = dataManager->getCampusLocations();
	if (locations.empty())
	{
		cout << "\n[Info] No campus locations available to remove.\n";
		return;
	}

	viewAllCampusLocations();

	int choice;
	cout << "\nEnter the number of the location to remove (1-" << locations.size() << "): ";
	cin >> choice;

	string removed = locations.getAt(choice - 1);
	bool success = locations.removeAt(choice - 1);

	if (success)
	{
		dataManager->setCampusLocations(locations);
		dataManager->saveCampusLocations();
		cout << "[Success] Removed location \"" << removed << "\".\n";
	}
	else
	{
		cout << "[Error] Invalid selection.\n";
	}
}

void FacilityManager::viewAllProblemCategories()
{
	StringLinkedList categories = dataManager->getProblemCategories();
	if (categories.empty())
	{
		cout << "\n[Info] No problem categories recorded.\n";
		return;
	}

	cout << "\n--- Problem Categories ---\n";
	int idx = 1;
	for (StringNode* curr = categories.getHead(); curr != nullptr; curr = curr->getNext(), idx++)
	{
		cout << idx << ". " << curr->getData() << "\n";
	}
}

void FacilityManager::addProblemCategory()
{
	string newCategory;
	cout << "\nEnter new problem category: ";
	cin >> newCategory;

	if (newCategory.empty())
	{
		cout << "[Error] Category name cannot be empty.\n";
		return;
	}

	StringLinkedList categories = dataManager->getProblemCategories();
	if (categories.contains(newCategory))
	{
		cout << "[Error] Category \"" << newCategory << "\" already exists.\n";
		return;
	}

	categories.append(newCategory);
	dataManager->setProblemCategories(categories);
	dataManager->saveProblemCategories();

	cout << "[Success] Problem category \"" << newCategory << "\" added successfully.\n";
}

void FacilityManager::removeProblemCategory()
{
	StringLinkedList categories = dataManager->getProblemCategories();
	if (categories.empty())
	{
		cout << "\n[Info] No problem categories available to remove.\n";
		return;
	}

	viewAllProblemCategories();

	int choice;
	cout << "\nEnter the number of the category to remove (1-" << categories.size() << "): ";
	cin >> choice;

	string removed = categories.getAt(choice - 1);
	bool success = categories.removeAt(choice - 1);

	if (success)
	{
		dataManager->setProblemCategories(categories);
		dataManager->saveProblemCategories();
		cout << "[Success] Removed category \"" << removed << "\".\n";
	}
	else
	{
		cout << "[Error] Invalid selection.\n";
	}
}

TechnicianLinkedList FacilityManager::getAllTechnicians()
{
	return dataManager->getTechnicians();
}

RequestLinkedList FacilityManager::getAllRequests()
{
	return dataManager->getRequests();
}

RequesterLinkedList FacilityManager::getAllRequester()
{
	return dataManager->getRequesters();
}

Queue* FacilityManager::getCurrentRequestQueue()
{
	return dataManager->getRequestQueue();
}

void FacilityManager::viewServiceHistory()
{
	ChangeLogLinkedList history = getServiceHistory();

	if (history.empty())
	{
		cout << "\n[Info] No service history (change logs) found.\n";
		return;
	}

	cout << "\n--- Service History (Change Logs) ---\n";
	cout << left << setw(8) << "Req ID" << " | "
	     << setw(12) << "Date" << " | "
	     << setw(16) << "Status" << " | "
	     << "Repair Notes / Action\n";
	cout << "------------------------------------------------------------------------------------\n";
	for (ChangeLogNode* curr = history.getHead(); curr != nullptr; curr = curr->getNext())
	{
		ChangeLog* log = curr->getData();
		cout << left << setw(8) << ("#" + to_string(log->getRequestId())) << " | "
		     << setw(12) << log->getDate() << " | "
		     << setw(16) << log->getStatus() << " | "
		     << log->getRepairNotes() << "\n";
	}
}

ChangeLogLinkedList FacilityManager::getServiceHistory()
{
	return dataManager->getChangeLogs();
}
