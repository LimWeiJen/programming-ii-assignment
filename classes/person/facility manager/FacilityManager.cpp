#include "FacilityManager.h"
#include "../../../data/DataManager.h"
#include "../../request/Request.h"
#include "../requester/Requester.h"
#include "../technician/Technician.h"
#include "../../../data structures/queue/Queue.h"
#include <iostream>
#include <iomanip>
#include <vector>
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
	vector<Technician> allTechnicians = getAllTechnicians();

	if (allTechnicians.empty())
	{
		cout << "\n[Info] No technicians registered in the system.\n";
		return;
	}

	cout << "\n--- Registered Technicians ---\n";
	for (int i = 0; i < allTechnicians.size(); i++)
	{
		cout << "ID: " << allTechnicians[i].getID()
		     << " | Name: " << allTechnicians[i].getName()
		     << " | Email: " << allTechnicians[i].getEmail() << "\n";
	}
}

void FacilityManager::addTechnician()
{
	vector<Technician> allTechnicians = getAllTechnicians();

	int newId = 1;
	for (int i = 0; i < allTechnicians.size(); i++)
	{
		if (allTechnicians[i].getID() >= newId)
		{
			newId = allTechnicians[i].getID() + 1;
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
	allTechnicians.push_back(newTech);

	dataManager->setTechnicians(allTechnicians);
	dataManager->saveTechnicians();

	cout << "\n[Success] Technician \"" << name << "\" (ID: " << newId << ") added successfully!\n";
}

void FacilityManager::removeTechnician(int technicianId)	
{
	vector<Technician> allTechnicians = getAllTechnicians();
	bool found = false;

	for (int i = 0; i < allTechnicians.size(); i++)
	{
		if (allTechnicians[i].getID() == technicianId)
		{
			cout << "[Success] Technician \"" << allTechnicians[i].getName() 
			     << "\" (ID: " << technicianId << ") has been removed.\n";
			allTechnicians.erase(allTechnicians.begin() + i);
			found = true;
			break;
		}
	}

	if (found)
	{
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
	vector<Request> allRequests = getAllRequests();
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

	vector<Request> filtered;

	if (filterChoice == 1)
	{
		filtered = allRequests;
	}
	else if (filterChoice == 2)
	{
		vector<string> categories = dataManager->getProblemCategories();
		if (categories.empty())
		{
			cout << "[Info] No problem categories available.\n";
			return;
		}

		cout << "\nSelect Category:\n";
		for (int i = 0; i < categories.size(); i++)
		{
			cout << (i + 1) << ". " << categories[i] << "\n";
		}
		cout << "Choose category (1-" << categories.size() << "): ";
		int catChoice;
		cin >> catChoice;
		string selectedCategory = categories[catChoice - 1];

		for (int i = 0; i < allRequests.size(); i++)
		{
			if (allRequests[i].getProblemCategory() == selectedCategory)
			{
				filtered.push_back(allRequests[i]);
			}
		}
	}
	else if (filterChoice == 3)
	{
		vector<string> locations = dataManager->getCampusLocations();
		if (locations.empty())
		{
			cout << "[Info] No campus locations available.\n";
			return;
		}

		cout << "\nSelect Campus Location:\n";
		for (int i = 0; i < locations.size(); i++)
		{
			cout << (i + 1) << ". " << locations[i] << "\n";
		}
		cout << "Choose location (1-" << locations.size() << "): ";
		int locChoice;
		cin >> locChoice;
		string selectedLocation = locations[locChoice - 1];

		for (int i = 0; i < allRequests.size(); i++)
		{
			if (allRequests[i].getCampusLocation() == selectedLocation)
			{
				filtered.push_back(allRequests[i]);
			}
		}
	}
	else if (filterChoice == 4)
	{
		viewTechnicians();
		int techId;
		cout << "Enter Technician ID to filter by: ";
		cin >> techId;

		for (int i = 0; i < allRequests.size(); i++)
		{
			if (allRequests[i].getAssignedTechnicianID() == techId)
			{
				filtered.push_back(allRequests[i]);
			}
		}
	}
	else if (filterChoice == 5)
	{
		string currentDate;
		cout << "Enter current date to check overdue status (YYYY-MM-DD): ";
		cin >> currentDate;

		for (int i = 0; i < allRequests.size(); i++)
		{
			if (allRequests[i].getStatus() != "COMPLETED" && allRequests[i].getStatus() != "CANCELLED")
			{
				string target = allRequests[i].getTargetCompletionDate();
				if (!target.empty() && target < currentDate)
				{
					filtered.push_back(allRequests[i]);
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
	for (int i = 0; i < filtered.size(); i++)
	{
		cout << "#" << filtered[i].getID() << "\t | "
		     << filtered[i].getStatus() << "\t | "
		     << filtered[i].getCampusLocation() << "\t | "
		     << filtered[i].getProblemCategory() << "\t | "
		     << (filtered[i].getAssignedTechnicianID() == 0 ? "Unassigned" : to_string(filtered[i].getAssignedTechnicianID())) << "\t | "
		     << (filtered[i].getTargetCompletionDate().empty() ? "None" : filtered[i].getTargetCompletionDate()) << "\n";
	}

	cout << "\nEnter Request ID to view full details (or 0 to return): ";
	int detailId;
	if (cin >> detailId && detailId != 0)
	{
		bool found = false;
		for (int i = 0; i < filtered.size(); i++)
		{
			if (filtered[i].getID() == detailId)
			{
				cout << "\n================ Request #" << filtered[i].getID() << " Details ================\n";
				cout << "Requester ID:             " << filtered[i].getRequesterID() << "\n";
				cout << "Campus Location:          " << filtered[i].getCampusLocation() << "\n";
				cout << "Problem Category:         " << filtered[i].getProblemCategory() << "\n";
				cout << "Status:                   " << filtered[i].getStatus() << "\n";
				cout << "Target Completion Date:   " << (filtered[i].getTargetCompletionDate().empty() ? "None" : filtered[i].getTargetCompletionDate()) << "\n";
				cout << "Date Assigned:            " << (filtered[i].getDateAssignedToTechnician().empty() ? "Not assigned" : filtered[i].getDateAssignedToTechnician()) << "\n";
				cout << "Assigned Technician ID:   " << (filtered[i].getAssignedTechnicianID() == 0 ? "None" : to_string(filtered[i].getAssignedTechnicianID())) << "\n";
				cout << "Description:              " << (filtered[i].getRequestDescription().empty() ? "None" : filtered[i].getRequestDescription()) << "\n";
				cout << "Repair Notes:             " << (filtered[i].getRepairNotes().empty() ? "None" : filtered[i].getRepairNotes()) << "\n";
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
	vector<Technician> allTechnicians = getAllTechnicians();
	bool techExists = false;
	string techName = "";
	for (int i = 0; i < allTechnicians.size(); i++)
	{
		if (allTechnicians[i].getID() == technicianId)
		{
			techExists = true;
			techName = allTechnicians[i].getName();
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
	vector<Request> requests = getAllRequests();
	for (int i = 0; i < requests.size(); i++)
	{
		if (requests[i].getID() == reqId)
		{
			requests[i].setAssignedTechnicianID(technicianId);
			requests[i].setDateAssignedToTechnician(assignDate);
			requests[i].setStatus("IN_PROGRESS");
			break;
		}
	}

	dataManager->setRequests(requests);
	dataManager->saveRequests();

	dataManager->addChangeLog(reqId, "IN_PROGRESS", "Assigned to Technician " + techName + " (ID: " + to_string(technicianId) + ")", assignDate);

	cout << "\n[Success] Assigned Technician \"" << techName 
	     << "\" (ID: " << technicianId << ") to Request #" << reqId << ".\n";
}

void FacilityManager::viewUsers()
{
	vector<Requester> allRequesters = getAllRequester();

	if (allRequesters.empty())
	{
		cout << "\n[Info] No registered users (requesters) found.\n";
		return;
	}

	cout << "\n--- Registered Users (Requesters) ---\n";
	for (int i = 0; i < allRequesters.size(); i++)
	{
		cout << "ID: " << allRequesters[i].getID()
		     << " | Name: " << allRequesters[i].getName()
		     << " | Email: " << allRequesters[i].getEmail() << "\n";
	}
}

void FacilityManager::removeUser()
{
	vector<Requester> allRequesters = getAllRequester();
	if (allRequesters.empty())
	{
		cout << "\n[Info] No users available to remove.\n";
		return;
	}

	viewUsers();

	int userId;
	cout << "\nEnter User ID to remove: ";
	cin >> userId;

	bool found = false;
	for (int i = 0; i < allRequesters.size(); i++)
	{
		if (allRequesters[i].getID() == userId)
		{
			cout << "[Success] User \"" << allRequesters[i].getName() 
			     << "\" (ID: " << userId << ") has been removed.\n";
			allRequesters.erase(allRequesters.begin() + i);
			found = true;
			break;
		}
	}

	if (found)
	{
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
	vector<string> locations = dataManager->getCampusLocations();
	if (locations.empty())
	{
		cout << "\n[Info] No campus locations recorded.\n";
		return;
	}

	cout << "\n--- Campus Locations ---\n";
	for (int i = 0; i < locations.size(); i++)
	{
		cout << (i + 1) << ". " << locations[i] << "\n";
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

	vector<string> locations = dataManager->getCampusLocations();
	for (int i = 0; i < locations.size(); i++)
	{
		if (locations[i] == newLocation)
		{
			cout << "[Error] Location \"" << newLocation << "\" already exists.\n";
			return;
		}
	}

	locations.push_back(newLocation);
	dataManager->setCampusLocations(locations);
	dataManager->saveCampusLocations();

	cout << "[Success] Campus location \"" << newLocation << "\" added successfully.\n";
}

void FacilityManager::removeCampusLocation()
{
	vector<string> locations = dataManager->getCampusLocations();
	if (locations.empty())
	{
		cout << "\n[Info] No campus locations available to remove.\n";
		return;
	}

	viewAllCampusLocations();

	int choice;
	cout << "\nEnter the number of the location to remove (1-" << locations.size() << "): ";
	cin >> choice;

	string removed = locations[choice - 1];
	locations.erase(locations.begin() + (choice - 1));
	dataManager->setCampusLocations(locations);
	dataManager->saveCampusLocations();

	cout << "[Success] Removed location \"" << removed << "\".\n";
}

void FacilityManager::viewAllProblemCategories()
{
	vector<string> categories = dataManager->getProblemCategories();
	if (categories.empty())
	{
		cout << "\n[Info] No problem categories recorded.\n";
		return;
	}

	cout << "\n--- Problem Categories ---\n";
	for (int i = 0; i < categories.size(); i++)
	{
		cout << (i + 1) << ". " << categories[i] << "\n";
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

	vector<string> categories = dataManager->getProblemCategories();
	for (int i = 0; i < categories.size(); i++)
	{
		if (categories[i] == newCategory)
		{
			cout << "[Error] Category \"" << newCategory << "\" already exists.\n";
			return;
		}
	}

	categories.push_back(newCategory);
	dataManager->setProblemCategories(categories);
	dataManager->saveProblemCategories();

	cout << "[Success] Problem category \"" << newCategory << "\" added successfully.\n";
}

void FacilityManager::removeProblemCategory()
{
	vector<string> categories = dataManager->getProblemCategories();
	if (categories.empty())
	{
		cout << "\n[Info] No problem categories available to remove.\n";
		return;
	}

	viewAllProblemCategories();

	int choice;
	cout << "\nEnter the number of the category to remove (1-" << categories.size() << "): ";
	cin >> choice;
	string removed = categories[choice - 1];
	categories.erase(categories.begin() + (choice - 1));
	dataManager->setProblemCategories(categories);
	dataManager->saveProblemCategories();

	cout << "[Success] Removed category \"" << removed << "\".\n";
}

vector<Technician> FacilityManager::getAllTechnicians()
{
	return dataManager->getTechnicians();
}

vector<Request> FacilityManager::getAllRequests()
{
	return dataManager->getRequests();
}

vector<Requester> FacilityManager::getAllRequester()
{
	return dataManager->getRequesters();
}

Queue* FacilityManager::getCurrentRequestQueue()
{
	return dataManager->getRequestQueue();
}

void FacilityManager::viewServiceHistory()
{
	vector<ChangeLog*> history = getServiceHistory();

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
	for (int i = 0; i < history.size(); i++)
	{
		cout << left << setw(8) << ("#" + to_string(history[i]->getRequestId())) << " | "
		     << setw(12) << history[i]->getDate() << " | "
		     << setw(16) << history[i]->getStatus() << " | "
		     << history[i]->getRepairNotes() << "\n";
	}
}

vector<ChangeLog*> FacilityManager::getServiceHistory()
{
	return dataManager->getChangeLogs();
}
