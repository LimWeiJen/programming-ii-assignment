# Demonstration Video Slides Outline & Script
## Smart Campus Facility Maintenance System (SCFMS)
**Course:** KIE1008 Programming II — Semester I 2026/2027  
**Assignment:** Group Project (OOP Architecture & Advanced Data Structures)  
**Target Video Duration:** 10 – 12 Minutes  
**Target Audience:** Course Evaluator / Lecturer / Tutor

---

## 📋 Comprehensive Requirements Traceability Matrix (README.md Alignment)

Every single requirement from the assignment specification and your `README.md` checklist is mapped to its exact slide, code module, and demonstration step:

| Category | Requirement from `README.md` Checklist | Implemented Class / Method | Addressed in Slide |
| :--- | :--- | :--- | :--- |
| **Domain Scope** | Manage campus requests (lights, air-conditioning, furniture) | `Request` entity, `problem_categories.txt` | Slide 2, 7 |
| | Target completion dates & campus locations | `Request::getTargetCompletionDate()`, `campus_locations.text` | Slide 2, 7, 10 |
| **OOP Base Class** | `Person` (Name, ID, Email, Password, DataManager pointer) | `classes/person/Person.h` | Slide 3 |
| | Virtual method `displayMenu()` overridden in derived classes | `virtual void displaymenu()` in `Person.h` | Slide 3 |
| **Derived Classes** | `FacilityManager` (overrides `displayMenu()`, admin functions) | `classes/person/facility manager/FacilityManager.h` | Slide 3, 9, 10 |
| | `Technician` (overrides `displayMenu()`, job processing) | `classes/person/technician/Technician.h` | Slide 3, 11 |
| | `Requester` (overrides `displayMenu()`, ticket submission) | `classes/person/requester/Requester.h` | Slide 3, 7, 8 |
| **Data Structures** | Custom pointer-based FIFO `Queue` (holds pending requests) | `data structures/queue/Queue.h` & `QueueNode.h` | Slide 5, 9 |
| | Custom pointer-based `LinkedList` (service history changelogs) | `data structures/linked list/LinkedList.h` & `ChangeLog.h` | Slide 6, 10, 11 |
| | Service History attributes: Date, Status Change, Repair Notes | `ChangeLog::getDate()`, `getStatus()`, `getRepairNotes()` | Slide 6, 10, 11 |
| **Requester Interface** | Register requester (Sign Up) | `handleRequester()` in `main.cpp` | Slide 7 |
| | Submit maintenance request (location, category, date, notes) | `Requester::submitRequest()` | Slide 7 |
| | View maintenance status (view submitted requests, view details) | `Requester::viewSubmittedRequests()`, `viewRequestDetails()` | Slide 8 |
| | Cancel maintenance request | `Requester::cancelRequest()` | Slide 8 |
| **Manager Interface** | Review latest pending request using FIFO queue (`Queue::front()`) | `FacilityManager::reviewLatestRequest()` | Slide 9 |
| | Assign next pending request to technician | `FacilityManager::assignTechnician(int technicianId)` | Slide 9 |
| | View and remove registered technicians | `FacilityManager::viewTechnicians()`, `removeTechnician()` | Slide 9 |
| | Register new technician | `FacilityManager::addTechnician()` | Slide 9 |
| | View and remove requesters / users | `FacilityManager::viewUsers()`, `removeUser()` | Slide 10 |
| | Manage campus locations & problem categories | `add/removeCampusLocation()`, `add/removeProblemCategory()` | Slide 10 |
| | Filter/Review requests: active, completed, category, location, tech | `FacilityManager::reviewRequests()` | Slide 10 |
| | Detect and list overdue requests | `FacilityManager::reviewRequests()` (Option 5) | Slide 10 |
| | View complete service history audit trail | `FacilityManager::viewServiceHistory()` | Slide 10 |
| **Technician Interface**| View assigned requests only (filters active jobs for tech ID) | `Technician::getCurrentAssignedRequests()` | Slide 11 |
| | Process assigned jobs (Update status: IN_PROGRESS, PENDING_PARTS, COMPLETED) | `Technician::updateRequestStatus()` | Slide 11 |
| | Record maintenance progress (add repair notes to ticket & history) | `Technician::addRepairNotes()` | Slide 11 |
| **Data Persistence** | Save & Load users (requesters & technicians) | `DataManager::load/saveRequesters()`, `load/saveTechnicians()` | Slide 4, 14 |
| | Save & Load maintenance requests & technician assignments | `DataManager::load/saveRequests()` | Slide 4, 14 |
| | Save & Load pending queue order & service history | `DataManager::load/saveChangeLogs()`, queue rebuild | Slide 4, 14 |
| **Error Handling** | Creating requests with duplicate IDs (auto-generated ID check) | `Requester::submitRequest()` (max ID + 1) | Slide 12 |
| | Creating requests for non-existent users (session binding) | `handleRequester()` auth gating | Slide 12 |
| | Invalid Request ID check before proceeding | Validated in Requester, Manager & Technician | Slide 12 |
| | Invalid Technician ID check before assignment / login | `FacilityManager::assignTechnician()` validation | Slide 12 |
| | Unauthorized actions (cross-user access prevention) | Ownership check in Technician & Requester | Slide 12 |
| | Invalid status change protection (completed/cancelled guards) | Guard conditions in `Technician.cpp` & `Requester.cpp` | Slide 12 |
| | Assigning completed request / processing empty queue | `currentQueue->size() == 0` validation | Slide 12 |
| **Report Insight** | Engineering discussion: Why FIFO queue + Vector hybrid design | `README.md` note on data structure suitability | Slide 13 |

---

## Group Roles & Presentation Workload Distribution

| Team Member | Presentation Section | Role / Perspective Covered |
| :--- | :--- | :--- |
| **Member 1** | Slides 1 – 4 | Title, Scope, OOP Hierarchy, File Persistence Layer |
| **Member 2** | Slides 5 – 6 | Custom Data Structures (Pointer-Based Queue & Linked List) |
| **Member 3** | Slides 7 – 8 | Perspective 1: Requester (Sign-Up, Submission, Tracking, Cancel) |
| **Member 4** | Slides 9 – 10 | Perspective 2: Facility Manager (FIFO Assign, Users, Filters, History) |
| **Member 5** | Slides 11 – 14 | Perspective 3: Technician, Error Handling, Trade-offs, Conclusion |

*(Note: If presenting in a smaller group of 3 or 4, merge sections naturally).*

---

## Detailed Slide-by-Slide Outline & Script

```
================================================================================
SLIDE 1: Title Slide & Introduction
================================================================================
```
- **Estimated Duration:** 0:45 min
- **Speaker:** Member 1
- **Visual Content:**
  - **Project Title:** Smart Campus Facility Maintenance System (SCFMS)
  - **Subtitle:** *An Object-Oriented C++ Architecture with Custom Pointer Data Structures*
  - **Course:** KIE1008 Programming II (Semester I 2026/2027)
  - **Team Roster:** Names, Student IDs, and assigned presentation modules
  - **System Overview Badge:** Demonstrating compliance with all assignment & README.md task specifications.
- **On-Screen Graphic:**
  - High-level workflow diagram:
    `Student / Requester ➔ Pending FIFO Queue ➔ Facility Manager ➔ Assigned Technician ➔ Audit Linked List`
- **Voiceover Script / Speaking Points:**
  > "Good day to our respected lecturer and evaluators. Welcome to our presentation and live demonstration of the Smart Campus Facility Maintenance System, or SCFMS, developed for KIE1008 Programming II.
  >
  > In a modern university campus, managing daily facility faults—from flickering laboratory lights to faulty lecture hall air conditioning and broken classroom furniture—requires a dependable, structured workflow. Without proper software coordination, requests are delayed, technician workloads become unbalanced, and there is no transparent maintenance history.
  >
  > Our team has designed and implemented a complete object-oriented C++ solution. Every requirement specified in the assignment and tracked in our project roadmap has been fully realized: from class inheritance and polymorphism, to custom pointer-based FIFO queues and service history linked lists, to multi-role interfaces and persistent file storage.
  >
  > Today, we will guide you through our system architecture, demonstrate every task requirement, and show live operations from the perspectives of the Requester, the Facility Manager, and the Technician."

---

```
================================================================================
SLIDE 2: Problem Scope, Domain & System Objectives
================================================================================
```
- **Estimated Duration:** 0:45 min
- **Speaker:** Member 1
- **Visual Content:**
  - **Target Campus Domain:**
    - Campus Locations: Lecture Halls, Laboratories, Sports Complex, Library, Residential Colleges.
    - Problem Categories: Electrical / Lighting, Air Conditioning (HVAC), Furniture / Structural, Hygiene / Plumbing.
  - **Core System Objectives:**
    1. **Role-Appropriate Interfaces:** Requester, Facility Manager, and Technician dashboards.
    2. **Fair FIFO Triage:** Explicit queue scheduling ensuring requests are handled in first-come, first-served order.
    3. **Immutable Service History:** Explicit linked list capturing dates, status transitions, and technician repair notes.
    4. **Target Dates & Overdue Tracking:** Proactive tracking of deadlines to prevent maintenance backlogs.
    5. **Data Persistence:** Complete data survival across sessions using structured file I/O.
  - **✅ README.md Task Fulfilled:**
    - `[x] manage campus requests (faulty lights, air-conditioning, furniture)`
    - `[x] target completion dates & campus locations`
- **Voiceover Script / Speaking Points:**
  > "Let us look at the scope of our system.
  >
  > As outlined in our project checklist, SCFMS is configured to manage campus repair requests across real-world campus locations and problem categories—specifically faulty lighting, air-conditioning, plumbing, and furniture.
  >
  > The system coordinates four fundamental pillars:
  > First, role-appropriate maintenance management interfaces tailored to requesters, managers, and technicians.
  > Second, an explicit FIFO queue that guarantees fairness in dispatching pending tickets.
  > Third, an explicit singly linked list recording the chronological service history of every intervention.
  > And fourth, target completion date tracking to identify overdue tickets alongside permanent file persistence.
  >
  > Let us now inspect how these requirements are architected using Object-Oriented Programming principles."

---

```
================================================================================
SLIDE 3: OOP Architecture — Class Hierarchy & Polymorphism
================================================================================
```
- **Estimated Duration:** 1:00 min
- **Speaker:** Member 1
- **Visual Content:**
  - **UML Class Diagram:**
    - **Base Class: `Person`**
      - Common Attributes: `name: string`, `id: int`, `email: string`, `password: string`, `dataManager: DataManager*`
      - Public Getters / Setters: Encapsulation of private fields
      - Virtual Method: `virtual void displaymenu()`
    - **Derived Classes (Inheritance `is-a`):**
      - `FacilityManager` ➔ Overrides `displayMenu()`, adds administrative dispatch, user management, and filtering.
      - `Technician` ➔ Overrides `displayMenu()`, adds assigned ticket processing and repair note logging.
      - `Requester` ➔ Overrides `displayMenu()`, adds request submission, tracking, and cancellation.
  - **Code Callout:** Showing the virtual function declaration in `Person.h` and its polymorphic override in derived classes.
  - **✅ README.md Task Fulfilled:**
    - `[x] Person (Name, ID, Email, Password, Display Menu virtual method)`
    - `[x] Derived Classes: Facility Manager, Technician, Requester`
- **Voiceover Script / Speaking Points:**
  > "The foundation of our software architecture is Object-Oriented design, specifically Inheritance, Encapsulation, and Polymorphism.
  >
  > We created an abstract base class named `Person`. It encapsulates common identity attributes required by all campus users: Name, numeric ID, email address, password for secure authentication, and a pointer to the shared `DataManager`.
  >
  > To satisfy the polymorphism requirement, `Person` defines a virtual method: `displayMenu()`.
  >
  > Each of our three derived classes—`FacilityManager`, `Technician`, and `Requester`—inherits from `Person` and overrides `displayMenu()` with role-specific menu options.
  >
  > When a user signs in, the main controller interacts with the user object through this polymorphic interface. This enforces strict separation of concerns and guarantees that users can only execute authorized operations."

---

```
================================================================================
SLIDE 4: Entity Models & File I/O Persistence Layer
================================================================================
```
- **Estimated Duration:** 1:00 min
- **Speaker:** Member 1
- **Visual Content:**
  - **Entity Domain Models:**
    - `Request`: Tracks Request ID, Requester ID, Assigned Technician ID, Campus Location, Problem Category, Description, Status, Date Assigned, Target Completion Date, Repair Notes.
    - `ChangeLog`: Represents a single audit node with Date, Request ID, Status Change, and Repair Notes.
  - **Persistence Layer (`DataManager`):**
    - Single point of truth coordinating file storage and dynamic memory.
    - **6 Text Databases (Pipe-Delimited `|`):**
      - `requesters.txt` — Requester accounts (ID, Name, Email, Password).
      - `technicians.txt` — Technician accounts (ID, Name, Email, Password).
      - `requests.txt` — Complete ticket records.
      - `changelogs.txt` — Historical audit trail events.
      - `campus_locations.text` & `problem_categories.txt` — Dynamic campus configurations.
  - **Lifecycle Execution:**
    - Startup: `dataManager.loadAll()` parses files, creates objects, and builds runtime Queue and Linked List in memory.
    - Exit: `dataManager.saveAll()` writes state back to files.
  - **✅ README.md Task Fulfilled:**
    - `[x] I/O for Data Persistence (Save & Load users, requests, technician assignments, pending queue order, service history)`
- **Voiceover Script / Speaking Points:**
  > "Next is our Data Persistence Layer, encapsulated within `DataManager`.
  >
  > We designed two core domain entities: `Request`, which represents the current state of a maintenance ticket, and `ChangeLog`, which represents an immutable point-in-time record of a maintenance event.
  >
  > To ensure data persists between application runs without requiring external database engines, `DataManager` implements bidirectional serialization using clean, pipe-delimited text files across six separate databases.
  >
  > On startup, `loadAll()` parses these files, instantiates user objects, and rebuilds both the pending FIFO queue and the service history linked list in dynamic memory. Whenever a ticket status changes, an assignment is made, or the program exits, `saveAll()` writes everything safely back to disk."

---

```
================================================================================
SLIDE 5: Custom Data Structure I — Pointer-Based FIFO Queue
================================================================================
```
- **Estimated Duration:** 1:15 min
- **Speaker:** Member 2
- **Visual Content:**
  - **Explicit Implementation Highlight:**
    - Explicitly implemented using pointers and nodes (no `std::queue` used).
  - **Queue Node Architecture:**
    - `QueueNode`: Contains `Request* val` and `QueueNode* next`.
    - `Queue`: Maintains `QueueNode* head`, `QueueNode* tail`, and `int queueSize`.
  - **Operations Complexity:**
    - `push(Request* val)`: $O(1)$ constant-time enqueue at `tail`.
    - `pop()`: $O(1)$ constant-time dequeue at `head` with memory cleanup (`delete tmp`).
    - `front()`: $O(1)$ peek at the oldest pending request.
    - `size()`: Returns pending ticket count.
  - **Queue State Diagram:**
    ```
    [head] ➔ [Node: Req #4] ➔ [Node: Req #6] ➔ [tail] (Req #7) ➔ nullptr
    ```
  - **✅ README.md Task Fulfilled:**
    - `[x] queues: Hold Pending Request, FIFO order`
    - `[x] Assign next pending request to technician using FIFO queue`
- **Voiceover Script / Speaking Points:**
  > "A primary deliverable of this project is the explicit implementation of advanced data structures using dynamic memory and pointers, rather than simply relying on standard template library containers.
  >
  > Here you see our custom FIFO Queue, built with `Queue` and `QueueNode`. Each node holds a pointer to a `Request` object and a pointer to the `next` node. The `Queue` class tracks both `head` and `tail` pointers.
  >
  > This allows constant time $O(1)$ enqueue operations at the tail via `push()`, and $O(1)$ dequeue operations at the head via `pop()`.
  >
  > Why a FIFO Queue? In campus facility management, fairness is paramount. When students submit requests, new jobs are pushed to the back of the queue. When the Facility Manager reviews or assigns work, the oldest pending request is retrieved from `front()` and processed in exact First-In, First-Out order."

---

```
================================================================================
SLIDE 6: Custom Data Structure II — Pointer-Based Singly Linked List
================================================================================
```
- **Estimated Duration:** 1:15 min
- **Speaker:** Member 2
- **Visual Content:**
  - **Explicit Implementation Highlight:**
    - Explicit pointer-linked chain (no `std::list` used).
  - **Linked List Node Architecture:**
    - `LinkedList`: Holds `ChangeLog* val` and `LinkedList* next`.
    - `ChangeLog` Entity stores:
      - `date: string` — Event timestamp (`YYYY-MM-DD`).
      - `requestId: int` — Target ticket ID.
      - `status: string` — State transition (`PENDING`, `IN_PROGRESS`, `PENDING_PARTS`, `COMPLETED`, `CANCELLED`).
      - `repairNotes: string` — Technician remarks and dispatch details.
  - **Operations:**
    - Dynamic append at tail: `tail->updateNext(new LinkedList(log))`.
    - Sequential traversal for formatted table rendering.
    - Deep destructor deallocation in `DataManager::~DataManager()`.
  - **✅ README.md Task Fulfilled:**
    - `[x] linked lists: Maintain Service History of each request`
    - `[x] Changelog tracking: Date, Status Change, Repair Notes`
- **Voiceover Script / Speaking Points:**
  > "Our second custom data structure is an explicit Singly Linked List dedicated to the maintenance Service History and audit trail.
  >
  > In `LinkedList.h`, each node stores a pointer to a `ChangeLog` instance and a `next` pointer. Whenever a ticket is created, assigned to a technician, updated in status, or annotated with repair remarks, a new `ChangeLog` object is instantiated and appended to the linked list.
  >
  > As required by the assignment, each changelog node encapsulates four critical data points: the date, the request ID, the status change, and the detailed repair notes.
  >
  > Unlike fixed arrays, this dynamic linked list grows seamlessly on the heap as campus maintenance activity occurs. It provides an unalterable chronological audit trail that facility managers can review at any time."

---

```
================================================================================
SLIDE 7: Live Demonstration — Perspective 1: Requester (Sign-Up & Submission)
================================================================================
```
- **Estimated Duration:** 1:30 min
- **Speaker:** Member 3
- **Live Demo Screen Recording Steps:**
  1. Launch `main.exe`.
  2. Select `3. User (Requester)`.
  3. Select `2. Sign Up` ➔ Register a new student:
     - Name: `Sarah Jenkins`
     - Email: `sarah@campus.edu`
     - Password: `password123`
     - System outputs generated User ID (e.g., ID: `2`).
  4. Automatic transition into **Requester Dashboard** (`Requester::displayMenu()`):
     - Select `1. Submit New Request`.
     - Select Campus Location from dynamic menu (e.g., `1. field`).
     - Select Problem Category (e.g., `1. technical` or `2. electrical`).
     - Enter Description: `Main floodlight #3 flickering and buzzing`.
     - Enter Target Completion Date: `2026-11-15`.
     - System outputs: `[Success] Maintenance Request #5 submitted successfully!`
- **Visual Callouts on Screen:**
  - Highlighting email duplication check on Sign Up.
  - Highlighting auto-generated Request ID (`newId = max + 1`) to eliminate duplicates.
  - Instant insertion into the FIFO Queue and initial `ChangeLog` linked list node.
- **✅ README.md Task Fulfilled:**
  - `[x] Register requester (requester perspective)`
  - `[x] Submit maintenance request (requester perspective)`
  - `[x] Campus requests: faulty lights, air-conditioning, furniture`
  - `[x] Creating requests with duplicate IDs prevented (auto-generated ID)`
- **Voiceover Script / Speaking Points:**
  > "Now, let us begin the live demonstration from the perspective of our first user: the Requester.
  >
  > We start the program and choose Option 3. A new student, Sarah, registers an account. Notice that the system checks for existing email addresses to prevent duplicate registrations and automatically assigns a unique User ID.
  >
  > Upon registration, the overridden `displayMenu()` for Requester appears. Sarah chooses Option 1 to submit a repair request. Notice that campus locations and problem categories are loaded dynamically from our configuration files.
  >
  > She reports a faulty lighting issue on the sports field and sets a target completion date. Notice that the system automatically assigns Request #5 by finding the maximum existing ID and incrementing it, fulfilling the requirement to prevent duplicate ticket IDs.
  >
  > Behind the scenes, Request #5 is enqueued into our custom FIFO Queue with status 'PENDING', and an initial creation entry is appended to our service history linked list."

---

```
================================================================================
SLIDE 8: Live Demonstration — Perspective 1: Requester (Tracking & Cancellation)
================================================================================
```
- **Estimated Duration:** 1:00 min
- **Speaker:** Member 3
- **Live Demo Screen Recording Steps:**
  1. In Requester Dashboard, select `2. View Submitted Requests`:
     - System displays table showing all requests submitted by Sarah (Request `#5`, status `PENDING`, location, category, target date).
  2. Select `3. View Request Details` ➔ Enter `5`:
     - Shows full details: Description, Status `PENDING`, Assigned Technician: *Not yet assigned*.
  3. **Demonstrate Ticket Cancellation:**
     - Select `4. Cancel Request` ➔ Enter `5`.
     - System changes status to `CANCELLED` and logs: `Request cancelled by requester`.
  4. **Submit a Fresh Request for the Next Steps:**
     - Select `1. Submit New Request`.
     - Location: `court`, Category: `hygiene`, Description: `Water fountain pipe leaking near squash court`, Target Date: `2026-11-12`.
     - Result: Request `#6` created with status `PENDING`.
  5. Select `0. Logout`.
- **✅ README.md Task Fulfilled:**
  - `[x] View maintenance status: view submitted requests, view request details`
  - `[x] Cancel maintenance request (requester perspective)`
  - `[x] Unauthorized actions: users can only view and cancel their own requests`
- **Voiceover Script / Speaking Points:**
  > "Requesters also have complete visibility over their tickets.
  >
  > Using Option 2 and Option 3, Sarah can view all tickets she has submitted and inspect their full status. The system enforces authorization checks here: users can only view tickets linked to their own Requester ID.
  >
  > Option 4 allows requesters to cancel a ticket if the issue is resolved or submitted by mistake. When Sarah cancels ticket #5, the system validates that it is not already completed, marks it 'CANCELLED', and appends a cancellation log to the linked list.
  >
  > To continue our demonstration, we submit a new ticket—Request #6 for a plumbing leak—which is now waiting in the pending queue for the Facility Manager."

---

```
================================================================================
SLIDE 9: Live Demonstration — Perspective 2: Facility Manager (Queue Review & Assignment)
================================================================================
```
- **Estimated Duration:** 1:30 min
- **Speaker:** Member 4
- **Live Demo Screen Recording Steps:**
  1. From Main Menu, select `1. Facility Manager`.
  2. Enter Admin Credentials (`admin@campus.edu` / `admin123`).
  3. Facility Manager Dashboard appears (`FacilityManager::displayMenu()`).
  4. **Manage Technicians:**
     - Select `1. View All Technicians` (shows existing technicians).
     - Select `2. Add New Technician`:
       - Enter Name: `Alex`, Email: `alex@campus.edu`, Password: `tech123`.
       - System confirms Technician added with auto-generated ID.
  5. **FIFO Queue Review:**
     - Select `4. Review Latest Pending Request (Queue)`.
     - System calls `Queue::front()`, inspecting the oldest pending request (Request `#4` or `#6`).
  6. **Technician Assignment via Queue:**
     - Select `6. Assign Technician to Current Request`.
     - Enter Technician ID: `2` (`hello`).
     - Enter Date Assigned: `2026-11-04`.
     - Status updates from `PENDING` ➔ `IN_PROGRESS`.
     - System logs assignment to the Linked List and saves data.
- **✅ README.md Task Fulfilled:**
  - `[x] Register technician (manager perspective)`
  - `[x] View and remove technician (manager perspective)`
  - `[x] Review latest pending request using FIFO Queue (Queue::front())`
  - `[x] Assign next pending request to technician using FIFO queue`
  - `[x] Technician assignments recorded and persisted`
- **Voiceover Script / Speaking Points:**
  > "We now sign in as the Facility Manager using administrative credentials.
  >
  > The Facility Manager dashboard provides executive management over campus operations. First, under Options 1 and 2, the manager can view and register technicians. We add a new technician named Alex, who receives an auto-generated ID.
  >
  > Next, we demonstrate our custom FIFO queue in action. By selecting Option 4, the manager reviews the latest pending request. This directly invokes `front()` on our custom `Queue` class, displaying the ticket at the head of the pending queue.
  >
  > In Option 6, the manager assigns this pending request to Technician #2. The system validates that Technician 2 exists, prompts for the assignment date, changes the status to 'IN_PROGRESS', updates the persistent text files, and links an assignment event into the service history."

---

```
================================================================================
SLIDE 10: Live Demonstration — Perspective 2: Facility Manager (User Management, Filters & History)
================================================================================
```
- **Estimated Duration:** 1:15 min
- **Speaker:** Member 4
- **Live Demo Screen Recording Steps:**
  1. **User Management:**
     - Select `7. View All Users` (lists registered requesters).
     - Select `8. Remove User` (demonstrates user removal with ID verification).
  2. **Campus Configurations:**
     - Select `9. View Campus Locations` / `10. Add Campus Location`.
     - Select `12. View Problem Categories` / `13. Add Problem Category`.
  3. **Comprehensive Search & Filtering:**
     - Select `5. Review / Filter All Requests`:
       - Filter by Problem Category (`technical`, `hygiene`, etc.).
       - Filter by Campus Location (`field`, `court`).
       - Filter by Assigned Technician (ID `2`).
       - Filter by Overdue Requests (enter date `2026-11-05` to identify tickets past their target completion date).
  4. **View Complete Service History:**
     - Select `15. View Service History (Change Logs)`.
     - Traverses the custom `LinkedList`, displaying every historical transition.
  5. Select `0. Logout`.
- **✅ README.md Task Fulfilled:**
  - `[x] Manages User: View and remove user (manager perspective)`
  - `[x] Search by request ID, campus location, or problem category`
  - `[x] List: Active requests, Completed requests, Target dates, Overdue requests`
  - `[x] Service histories displayed from Linked List`
- **Voiceover Script / Speaking Points:**
  > "Continuing in the Facility Manager dashboard, Options 7 and 8 allow viewing and removing registered student accounts, while Options 9 through 14 allow dynamic additions and removals of campus locations and problem categories.
  >
  > Option 5 provides powerful filtering capabilities. The manager can search and filter requests by problem category, campus location, or assigned technician. Most importantly, option 5 includes an overdue filter: by entering the current date, the system compares target completion dates and lists active requests that have breached their deadline.
  >
  > Finally, Option 15 displays the complete campus Service History. This formatted report is generated by traversing our custom `LinkedList` node-by-node, showing the chronological log of every submission, technician assignment, status transition, and repair note.
  >
  > Next, let us log in as the technician to process the assigned job."

---

```
================================================================================
SLIDE 11: Live Demonstration — Perspective 3: Technician (Job Processing & Notes)
================================================================================
```
- **Estimated Duration:** 1:30 min
- **Speaker:** Member 5
- **Live Demo Screen Recording Steps:**
  1. From Main Menu, select `2. Technician`.
  2. Sign in as Technician `2` (Password: `123`).
  3. Technician Dashboard appears (`Technician::displayMenu()`).
  4. **View Assigned Requests:**
     - Select `1. View Assigned Requests`.
     - System filters requests where `assignedTechnicianId == 2` and status is active (`IN_PROGRESS`). Completed or cancelled tickets are hidden.
  5. **Update Job Status:**
     - Select `2. Update Request Status` ➔ Enter Request ID.
     - Choose `2. PENDING_PARTS` (e.g. waiting for replacement valves/ballast).
     - System updates status and records change in `ChangeLog`.
     - Re-select `2. Update Request Status` ➔ Choose `3. COMPLETED`.
  6. **Record Maintenance Progress / Notes:**
     - Select `3. Add Repair Notes` ➔ Enter Request ID.
     - Input Notes: `Replaced leaking PVC valve and re-pressurized line. Flow tested normal.`
     - System appends notes to Request and records a new `ChangeLog` linked list entry.
  7. Select `0. Logout`.
- **✅ README.md Task Fulfilled:**
  - `[x] View request (technician perspective for assigned requests only)`
  - `[x] Process assigned jobs: Update request status (IN_PROGRESS, PENDING_PARTS, COMPLETED)`
  - `[x] Records maintenance progress: Add repair notes`
  - `[x] Update job status & record service history`
- **Voiceover Script / Speaking Points:**
  > "We now sign in as Technician 'hello' using ID 2.
  >
  > The technician's menu is designed for focused on-site execution. When Option 1 is chosen, the system displays only active requests assigned to this specific technician ID. Unrelated tickets and already completed jobs are filtered out.
  >
  > In Option 2, the technician updates the job status as work progresses. We demonstrate updating the status to 'PENDING_PARTS' while waiting for replacement components, and then subsequently to 'COMPLETED' upon finishing the repair.
  >
  > In Option 3, the technician records detailed maintenance progress. We enter: 'Replaced leaking PVC valve and re-pressurized line'. The system appends these remarks to the ticket and immediately creates a new node in the `ChangeLog` linked list.
  >
  > Once marked completed, the ticket is archived from active assignments while preserving a complete audit record in persistent storage."

---

```
================================================================================
SLIDE 12: Exception & Error Handling Demonstration
================================================================================
```
- **Estimated Duration:** 1:15 min
- **Speaker:** Member 5
- **Visual Content & Live Demonstration Matrix:**
  | Edge Case / Error Scenario | System Behavior / Protection Mechanism | Code Validation |
  | :--- | :--- | :--- |
  | **Duplicate Request IDs** | Prevented by design: Request IDs are auto-generated as `max(existing_ids) + 1`. | `Requester::submitRequest()` |
  | **Non-Existent Users** | Requesters must register or authenticate; tickets are bound to verified session user ID. | `handleRequester()` |
  | **Non-Existent Technician ID** | Manager assignment checks if technician ID exists in vector before modifying state. | `FacilityManager::assignTechnician()` |
  | **Assigning from Empty Queue** | Guard check: `if (currentQueue == nullptr \|\| currentQueue->size() == 0)` displays friendly error. | `FacilityManager::assignTechnician()` |
  | **Unauthorized Actions** | Technicians can only update their own assigned tickets; Requesters can only view/cancel their own tickets. | ID ownership guards in Technician & Requester |
  | **Invalid Status Transitions** | Cannot update or cancel tickets already marked `COMPLETED` or `CANCELLED`. | Status guards in `Technician.cpp` & `Requester.cpp` |
  | **Invalid Input Stream Types** | Entering letters at numeric prompts triggers `cin.clear()` and `cin.ignore()` to prevent infinite loops. | Input guards in `main.cpp` |
- **✅ README.md Task Fulfilled:**
  - `[x] Exception and Error Handling:`
    - `Creating requests with duplicate IDs (auto-generated ID)`
    - `Creating requests for non-existent users`
    - `Invalid request ID & Invalid technician ID check before proceeding`
    - `Unauthorized actions protection`
    - `Invalid status change protection (completed/cancelled guards)`
    - `Assigning a completed request or processing an empty queue`
- **Voiceover Script / Speaking Points:**
  > "Software robustness is an essential requirement of the assignment rubric. We incorporated comprehensive exception and error handling across every user interaction:
  >
  > First, duplicate request IDs are prevented by architecture: the system scans existing tickets and auto-increments the maximum ID.
  > Second, assigning requests validates technician existence, and the system gracefully rejects attempts to assign from an empty queue.
  > Third, strict authorization barriers prevent cross-user interference: technicians cannot modify requests assigned to other personnel, and requesters cannot view or cancel tickets belonging to other students.
  > Fourth, invalid status transitions are blocked: tickets already completed or cancelled cannot be re-modified.
  > And fifth, non-numeric input errors are caught using `cin.clear()` and `cin.ignore()`, eliminating infinite terminal crash loops."

---

```
================================================================================
SLIDE 13: Technical Reflections & Engineering Trade-offs
================================================================================
```
- **Estimated Duration:** 0:45 min
- **Speaker:** Member 5
- **Visual Content:**
  - **Engineering Trade-off Discussion (Addressing README.md Note):**
    - *Why a FIFO Queue alone is not ideal for the entire system:*
      - **Queue Strength:** Perfect for fair, sequential job intake and dispatch ($O(1)$ push/pop).
      - **Queue Limitation:** A pure queue forbids random-access inspection, multi-criteria filtering, and historical queries without dequeuing all elements.
    - **Our Hybrid Architectural Solution:**
      - **Explicit Queue:** Dedicated solely to the unassigned pending request pipeline.
      - **Explicit Singly Linked List:** Dedicated to sequential append-only service history logging.
      - **Vectors:** Used within `DataManager` as an indexed cache for fast searching, filtering, and text file serialization.
  - **Future Extension:** Priority Queue supporting urgency weights (e.g. electrical hazards over minor cosmetic repairs).
  - **✅ README.md Task Fulfilled:**
    - `[x] Queue is not the most ideal data structure for the current implementation (that's why vector/hybrid is used) — Report analysis`
- **Voiceover Script / Speaking Points:**
  > "As noted in our project README and technical report, we also evaluated the theoretical trade-offs of our chosen data structures.
  >
  > A pure FIFO Queue is optimal for fair ticket intake and dispatch because of its constant-time $O(1)$ operations. However, a pure queue is not ideal for searching by location, filtering by category, or inspecting overdue dates, because queues do not support random access.
  >
  > For this reason, our architecture employs a purposeful hybrid design: our custom pointer-based Queue manages the active pending pipeline; our custom Linked List manages the sequential audit trail; and internal vectors provide indexed lookup for filtering and file persistence.
  >
  > In future iterations, this queue can be readily enhanced into a Priority Queue to prioritize urgent safety hazards over routine maintenance."

---

```
================================================================================
SLIDE 14: Conclusion & Specification Compliance
================================================================================
```
- **Estimated Duration:** 0:30 min
- **Speaker:** Member 5 (All team members visible on camera)
- **Visual Content:**
  - **Final Compliance Checklist (100% Fulfilled):**
    - [x] Object-Oriented Architecture: Base `Person` with 3 Derived Classes
    - [x] Runtime Polymorphism (`displayMenu()` overridden)
    - [x] Explicit Pointer-Based Queue for Pending Requests
    - [x] Explicit Pointer-Based Linked List for Service Histories
    - [x] Role-Based Interfaces (Requester, Manager, Technician)
    - [x] Bidirectional File I/O Persistence Across 6 Databases
    - [x] Proactive Error & Exception Handling
    - [x] Equitable Workload Distribution & Team Collaboration
  - GitHub Repository Link & Demonstration Video Link
  - Thank You & Acknowledgments
- **Voiceover Script / Speaking Points:**
  > "To conclude, our Smart Campus Facility Maintenance System satisfies every functional and architectural specification laid out in the assignment instructions and our project checklist.
  >
  > It demonstrates clean object-oriented inheritance, robust custom pointer-based data structures, dependable file persistence, and thorough error handling.
  >
  > On behalf of all five group members, thank you for your time, guidance, and evaluation. We look forward to your feedback."

---

## 🎬 Practical Video Recording Tips for the Team

1. **Terminal Appearance:** Use a modern terminal (Windows Terminal or VS Code integrated terminal) with clear font sizing (16–18pt) and a dark theme.
2. **Pre-populated Data:** Make sure your `data/` folder has a few sample requests, technicians, and locations ready before recording, so searches and filters populate realistically.
3. **Screen Layout:** Use a 2-window split screen:
   - **Left Half (40%):** Presentation Slides with the current slide's requirement badge.
   - **Right Half (60%):** Live CLI terminal showing the commands being executed.
4. **Subtitles / Captions:** Add text captions whenever custom data structures are executed (e.g. `[Queue::front() called]`, `[LinkedList Node Appended]`).
5. **Clean Data Reset:** Before the official recording take, delete any temporary test requests from `data/requests.txt` and `data/changelogs.txt` so the request numbers align neatly with your script.
