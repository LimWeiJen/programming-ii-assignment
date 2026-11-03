#include "data/DataManager.h"
#include "classes/person/facility manager/FacilityManager.h"
#include "classes/person/technician/Technician.h"
#include "classes/person/requester/Requester.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void handleFacilityManager(DataManager& dataManager);
void handleTechnician(DataManager& dataManager);
void handleRequester(DataManager& dataManager);

int main()
{
	DataManager dataManager;
	dataManager.loadAll();

	int roleChoice = -1;

	while (roleChoice != 0)
	{
		cout << "\n========================================\n";
		cout << "   CAMPUS FACILITY MANAGEMENT SYSTEM    \n";
		cout << "========================================\n";
		cout << "Select your role:\n";
		cout << "1. Facility Manager\n";
		cout << "2. Technician\n";
		cout << "3. User (Requester)\n";
		cout << "0. Exit Program\n";
		cout << "========================================\n";
		cout << "Choose role (0-3): ";
		if (!(cin >> roleChoice))
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n[Error] Invalid input. Please enter a number.\n";
			continue;
		}

		switch (roleChoice)
		{
			case 1:
				handleFacilityManager(dataManager);
				break;
			case 2:
				handleTechnician(dataManager);
				break;
			case 3:
				handleRequester(dataManager);
				break;
			case 0:
				dataManager.saveAll();
				cout << "\nAll data saved. Thank you for using the system. Goodbye!\n";
				break;
			default:
				cout << "\n[Error] Invalid role selection. Please choose 0 to 3.\n";
				break;
		}
	}

	return 0;
}

void handleFacilityManager(DataManager& dataManager)
{
	cout << "\n--- Facility Manager Sign In ---\n";
	cout << "(Default login: admin@campus.edu / admin123)\n";
	string email, password;
	cout << "Enter Email: ";
	cin >> email;
	cout << "Enter Password: ";
	cin >> password;

	if ((email == "admin@campus.edu" || email == "admin") && (password == "admin123" || password == "admin"))
	{
		FacilityManager manager("Administrator", 1, "admin@campus.edu", "admin123", &dataManager);
		cout << "\n[Success] Welcome, Facility Manager!\n";

		int choice = -1;
		while (choice != 0)
		{
			manager.displayMenu();
			cout << "Enter choice: ";
			if (!(cin >> choice))
			{
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\n[Error] Invalid input. Please enter a number.\n";
				continue;
			}

			switch (choice)
			{
				case 1:
					manager.viewTechnicians();
					break;
				case 2:
					manager.addTechnician();
					break;
				case 3:
				{
					manager.viewTechnicians();
					int techId;
					cout << "Enter Technician ID to remove: ";
					cin >> techId;
					manager.removeTechnician(techId);
					break;
				}
				case 4:
					manager.reviewLatestRequest();
					break;
				case 5:
					manager.reviewRequests();
					break;
				case 6:
				{
					manager.viewTechnicians();
					int techId;
					cout << "Enter Technician ID to assign: ";
					cin >> techId;
					manager.assignTechnician(techId);
					break;
				}
				case 7:
					manager.viewUsers();
					break;
				case 8:
					manager.removeUser();
					break;
				case 9:
					manager.viewAllCampusLocations();
					break;
				case 10:
					manager.addCampusLocation();
					break;
				case 11:
					manager.removeCampusLocation();
					break;
				case 12:
					manager.viewAllProblemCategories();
					break;
				case 13:
					manager.addProblemCategory();
					break;
				case 14:
					manager.removeProblemCategory();
					break;
				case 15:
					manager.viewServiceHistory();
					break;
				case 0:
					cout << "\nLogging out of Facility Manager dashboard...\n";
					break;
				default:
					cout << "\n[Error] Invalid choice. Please try again.\n";
					break;
			}
		}
	}
	else
	{
		cout << "\n[Error] Invalid Facility Manager credentials.\n";
	}
}

void handleTechnician(DataManager& dataManager)
{
	vector<Technician> technicians = dataManager.getTechnicians();
	if (technicians.empty())
	{
		cout << "\n[Info] No technicians registered in the system.\n";
		cout << "Please contact the Facility Manager to register a technician first.\n";
		return;
	}

	cout << "\n--- Technician Sign In ---\n";
	string input, password;
	cout << "Enter Email or Technician ID: ";
	cin >> input;
	cout << "Enter Password: ";
	cin >> password;

	bool authenticated = false;
	Technician* currentTech = nullptr;

	for (int i = 0; i < technicians.size(); i++)
	{
		if ((technicians[i].getEmail() == input || to_string(technicians[i].getID()) == input) && technicians[i].getPassword() == password)
		{
			currentTech = new Technician(technicians[i].getName(), technicians[i].getID(), technicians[i].getEmail(), technicians[i].getPassword(), &dataManager);
			authenticated = true;
			break;
		}
	}

	if (authenticated && currentTech != nullptr)
	{
		cout << "\n[Success] Welcome back, " << currentTech->getName() << "!\n";

		int choice = -1;
		while (choice != 0)
		{
			currentTech->displayMenu();
			cout << "Enter choice: ";
			if (!(cin >> choice))
			{
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\n[Error] Invalid input. Please enter a number.\n";
				continue;
			}

			switch (choice)
			{
				case 1:
					currentTech->getCurrentAssignedRequests();
					break;
				case 2:
					currentTech->updateRequestStatus();
					break;
				case 3:
					currentTech->addRepairNotes();
					break;
				case 0:
					cout << "\nLogging out of Technician dashboard...\n";
					break;
				default:
					cout << "\n[Error] Invalid choice. Please try again.\n";
					break;
			}
		}
		delete currentTech;
	}
	else
	{
		cout << "\n[Error] Invalid email/ID or password.\n";
	}
}

void handleRequester(DataManager& dataManager)
{
	cout << "\n--- User (Requester) Access ---\n";
	cout << "1. Sign In\n";
	cout << "2. Sign Up\n";
	cout << "0. Back to Role Selection\n";
	cout << "Choose option (0-2): ";
	int authChoice;
	if (!(cin >> authChoice))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n[Error] Invalid input. Please enter a number.\n";
		return;
	}

	if (authChoice == 1)
	{
		vector<Requester> requesters = dataManager.getRequesters();
		if (requesters.empty())
		{
			cout << "\n[Info] No users registered yet. Please Sign Up first!\n";
			return;
		}

		cout << "\n--- User Sign In ---\n";
		string input, password;
		cout << "Enter Email or User ID: ";
		cin >> input;
		cout << "Enter Password: ";
		cin >> password;

		bool authenticated = false;
		Requester* currentRequester = nullptr;

		for (int i = 0; i < requesters.size(); i++)
		{
			if ((requesters[i].getEmail() == input || to_string(requesters[i].getID()) == input) && requesters[i].getPassword() == password)
			{
				currentRequester = new Requester(requesters[i].getName(), requesters[i].getID(), requesters[i].getEmail(), requesters[i].getPassword(), &dataManager);
				authenticated = true;
				break;
			}
		}

		if (authenticated && currentRequester != nullptr)
		{
			cout << "\n[Success] Welcome back, " << currentRequester->getName() << "!\n";

			int choice = -1;
			while (choice != 0)
			{
				currentRequester->displayMenu();
				cout << "Enter choice: ";
				cin >> choice;

				switch (choice)
				{
					case 1:
						currentRequester->submitRequest();
						break;
					case 2:
						currentRequester->viewSubmittedRequests();
						break;
					case 3:
						currentRequester->viewRequestDetails();
						break;
					case 4:
						currentRequester->cancelRequest();
						break;
					case 0:
						cout << "\nLogging out of Requester dashboard...\n";
						break;
					default:
						cout << "\n[Error] Invalid choice. Please try again.\n";
						break;
				}
			}
			delete currentRequester;
		}
		else
		{
			cout << "\n[Error] Invalid email/ID or password.\n";
		}
	}
	else if (authChoice == 2)
	{
		cout << "\n--- User Sign Up ---\n";
		string name, email, password;
		cout << "Enter Name: ";
		getline(cin >> ws, name);
		cout << "Enter Email: ";
		cin >> email;
		cout << "Enter Password: ";
		cin >> password;

		vector<Requester> requesters = dataManager.getRequesters();
		for (int i = 0; i < requesters.size(); i++)
		{
			if (requesters[i].getEmail() == email)
			{
				cout << "\n[Error] Email is already registered. Please Sign In instead.\n";
				return;
			}
		}

		int newId = 1;
		for (int i = 0; i < requesters.size(); i++)
		{
			if (requesters[i].getID() >= newId)
			{
				newId = requesters[i].getID() + 1;
			}
		}

		Requester newRequester(name, newId, email, password, &dataManager);
		requesters.push_back(newRequester);
		dataManager.setRequesters(requesters);
		dataManager.saveRequesters();

		cout << "\n[Success] Account created successfully! Your User ID is " << newId << ".\n";
		cout << "You are now logged in as " << name << ".\n";

		int choice = -1;
		while (choice != 0)
		{
			newRequester.displayMenu();
			cout << "Enter choice: ";
			if (!(cin >> choice))
			{
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\n[Error] Invalid input. Please enter a number.\n";
				continue;
			}

			switch (choice)
			{
				case 1:
					newRequester.submitRequest();
					break;
				case 2:
					newRequester.viewSubmittedRequests();
					break;
				case 3:
					newRequester.viewRequestDetails();
					break;
				case 4:
					newRequester.cancelRequest();
					break;
				case 0:
					cout << "\nLogging out of Requester dashboard...\n";
					break;
				default:
					cout << "\n[Error] Invalid choice. Please try again.\n";
					break;
			}
		}
	}
}

