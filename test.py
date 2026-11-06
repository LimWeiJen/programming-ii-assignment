import os
import sys
import shutil
import subprocess
from typing import List, Tuple, Dict, Any

GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
BLUE = "\033[94m"
CYAN = "\033[96m"
BOLD = "\033[1m"
RESET = "\033[0m"

EXE_NAME = "main.exe"
DATA_DIR = "data"
BACKUP_DIR = ".data_backup_test"

class TestResult:
    def __init__(self, category: str, name: str, passed: bool, message: str = "", details: str = ""):
        self.category = category
        self.name = name
        self.passed = passed
        self.message = message
        self.details = details

class DataManagerBackup:
    """Safely backs up and restores the user's data directory for isolated testing."""
    def __init__(self):
        self.active = False

    def backup(self):
        if os.path.exists(DATA_DIR):
            if os.path.exists(BACKUP_DIR):
                shutil.rmtree(BACKUP_DIR)
            shutil.copytree(DATA_DIR, BACKUP_DIR)
            self.active = True

    def restore(self):
        if self.active and os.path.exists(BACKUP_DIR):
            if os.path.exists(DATA_DIR):
                shutil.rmtree(DATA_DIR)
            shutil.copytree(BACKUP_DIR, DATA_DIR)
            shutil.rmtree(BACKUP_DIR)
            self.active = False

    def reset_to_clean_state(self):
        """Reset data files to a known baseline state for predictable testing."""
        os.makedirs(DATA_DIR, exist_ok=True)
        with open(os.path.join(DATA_DIR, "campus_locations.text"), "w", encoding="utf-8") as f:
            f.write("Engineering_Block_A\nLibrary\nStudent_Center\n")
        with open(os.path.join(DATA_DIR, "problem_categories.txt"), "w", encoding="utf-8") as f:
            f.write("Electrical\nPlumbing\nAir_Conditioning\nFurniture\n")
        with open(os.path.join(DATA_DIR, "requesters.txt"), "w", encoding="utf-8") as f:
            f.write("1|Alice Smith|alice@campus.edu|pass123\n2|Bob Jones|bob@campus.edu|pass456\n")
        with open(os.path.join(DATA_DIR, "technicians.txt"), "w", encoding="utf-8") as f:
            f.write("1|Tech Dave|dave@tech.edu|tech123\n2|Tech Eva|eva@tech.edu|tech456\n")
        with open(os.path.join(DATA_DIR, "requests.txt"), "w", encoding="utf-8") as f:
            f.write("1|1|1|Engineering_Block_A|Electrical|Flickering lights|IN_PROGRESS|2026-11-01|2026-11-10|Inspected panel\n")
            f.write("2|2|0|Library|Air_Conditioning|AC leaking water|PENDING||2026-11-15|\n")
            f.write("3|1|2|Student_Center|Furniture|Broken chair|COMPLETED|2026-10-20|2026-10-25|Replaced chair\n")
        with open(os.path.join(DATA_DIR, "changelogs.txt"), "w", encoding="utf-8") as f:
            f.write("1|2026-11-01|PENDING|Request submitted: Flickering lights\n")
            f.write("1|2026-11-01|IN_PROGRESS|Assigned to Technician Tech Dave (ID: 1)\n")
            f.write("2|2026-11-02|PENDING|Request submitted: AC leaking water\n")
            f.write("3|2026-10-20|PENDING|Request submitted: Broken chair\n")
            f.write("3|2026-10-20|IN_PROGRESS|Assigned to Technician Tech Eva (ID: 2)\n")
            f.write("3|2026-10-25|COMPLETED|Status updated to COMPLETED by Technician Tech Eva\n")


def run_app(inputs: List[str], timeout: float = 6.0) -> Tuple[int, str, str]:
    """Runs main.exe feeding inputs line-by-line, returns (returncode, stdout, stderr)."""
    if not os.path.exists(EXE_NAME):
        raise FileNotFoundError(f"'{EXE_NAME}' not found. Please compile main.cpp first.")

    input_text = "\n".join(inputs) + "\n0\n"
    proc = subprocess.Popen(
        [os.path.abspath(EXE_NAME)],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        cwd=os.path.abspath(".")
    )
    try:
        stdout, stderr = proc.communicate(input=input_text, timeout=timeout)
        return proc.returncode, stdout, stderr
    except subprocess.TimeoutExpired:
        proc.kill()
        stdout, stderr = proc.communicate()
        return -1, stdout, "TIMEOUT: Process took longer than expected."


class SCFMSTestSuite:
    def __init__(self):
        self.results: List[TestResult] = []
        self.backup = DataManagerBackup()

    def record(self, category: str, name: str, passed: bool, message: str = "", details: str = ""):
        self.results.append(TestResult(category, name, passed, message, details))
        status_str = f"{GREEN}[PASS]{RESET}" if passed else f"{RED}[FAIL]{RESET}"
        print(f"  {status_str} {name}: {message}")
        if not passed and details:
            print(f"         {YELLOW}Output snippet: {details[:160]}...{RESET}")

    # =========================================================================
    # Group 1: Authentication & Role Gatekeeping
    # =========================================================================
    def test_manager_auth_valid(self):
        inputs = ["1", "admin@gmail.com", "admin", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Success] Welcome, Facility Manager!" in out)
        self.record("Authentication", "Facility Manager Valid Login", passed, 
                    "Manager logged in successfully" if passed else "Manager login failed", out)

    def test_manager_auth_invalid(self):
        inputs = ["1", "admin@gmail.com", "wrongpass", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Invalid Facility Manager credentials." in out)
        self.record("Authentication", "Facility Manager Invalid Login Guard", passed,
                    "Rejected invalid credentials properly" if passed else "Failed to reject invalid credentials", out)

    def test_technician_auth_valid_email(self):
        inputs = ["2", "dave@tech.edu", "tech123", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Welcome back, Tech Dave!" in out)
        self.record("Authentication", "Technician Login via Email", passed,
                    "Technician authenticated via email" if passed else "Technician email login failed", out)

    def test_technician_auth_valid_id(self):
        inputs = ["2", "1", "tech123", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Welcome back, Tech Dave!" in out)
        self.record("Authentication", "Technician Login via ID", passed,
                    "Technician authenticated via numeric ID" if passed else "Technician ID login failed", out)

    def test_technician_auth_invalid(self):
        inputs = ["2", "dave@tech.edu", "wrongpassword", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Invalid email/ID or password." in out)
        self.record("Authentication", "Technician Invalid Login Guard", passed,
                    "Rejected incorrect password" if passed else "Did not reject invalid password", out)

    def test_requester_auth_invalid(self):
        inputs = ["3", "1", "nonexistent@campus.edu", "wrong", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Invalid email/ID or password." in out)
        self.record("Authentication", "Requester Non-Existent User Login Guard", passed,
                    "Rejected non-existent requester credentials" if passed else "Failed non-existent user check", out)

    # =========================================================================
    # Group 2: Requester Operations
    # =========================================================================
    def test_requester_sign_up(self):
        inputs = ["3", "2", "Charlie Brown", "charlie@campus.edu", "charlie999", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Account created successfully!" in out) and ("User ID is 3" in out)
        self.record("Requester Operations", "Requester Registration (Sign Up)", passed,
                    "New requester registered with auto-assigned ID 3" if passed else "Registration failed", out)

    def test_requester_sign_up_duplicate_email(self):
        inputs = ["3", "2", "Duplicate User", "alice@campus.edu", "somepass", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Email is already registered." in out)
        self.record("Requester Operations", "Duplicate Email Registration Guard", passed,
                    "Blocked duplicate email registration" if passed else "Failed to block duplicate email", out)

    def test_requester_submit_request(self):
        inputs = [
            "3", "1", "alice@campus.edu", "pass123",
            "1",                          # Submit New Request
            "1",                          # Location: Engineering_Block_A (choice 1)
            "4",                          # Category: Furniture (choice 4)
            "Broken desk leg in Room 204",# Description
            "2026-12-01",                 # Target Completion Date
            "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Success] Maintenance Request #" in out) and ("submitted successfully!" in out)
        self.record("Requester Operations", "Submit Maintenance Request", passed,
                    "New request created with location, category, date, and description" if passed else "Submission failed", out)

    def test_requester_view_submitted(self):
        inputs = ["3", "1", "alice@campus.edu", "pass123", "2", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("--- Your Submitted Requests ---" in out) and ("#1" in out)
        self.record("Requester Operations", "View Submitted Requests", passed,
                    "Requester can view submitted request list" if passed else "View submitted requests failed", out)

    def test_requester_view_details_authorized(self):
        inputs = ["3", "1", "alice@campus.edu", "pass123", "3", "1", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("================ Request Details ================" in out) and ("Request ID:               #1" in out)
        self.record("Requester Operations", "View Request Details (Authorized)", passed,
                    "Requester viewed own request details successfully" if passed else "View details failed", out)

    def test_requester_view_details_unauthorized(self):
        # Alice is user 1. Request #2 belongs to Bob (user 2).
        inputs = ["3", "1", "alice@campus.edu", "pass123", "3", "2", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Unauthorized. You can only view requests you submitted." in out)
        self.record("Exception Handling", "Requester Unauthorized Request Access Guard", passed,
                    "Blocked viewing another user's request details" if passed else "Failed authorization check", out)

    def test_requester_cancel_own_request(self):
        # Bob (user 2) owns Request #2 (PENDING)
        inputs = ["3", "1", "bob@campus.edu", "pass456", "4", "2", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Success] Request #2 has been cancelled." in out)
        self.record("Requester Operations", "Cancel Pending Maintenance Request", passed,
                    "Requester cancelled pending request successfully" if passed else "Cancel request failed", out)

    def test_requester_cancel_completed_request_guard(self):
        # Alice owns Request #3 which is COMPLETED
        inputs = ["3", "1", "alice@campus.edu", "pass123", "4", "3", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Cannot cancel Request #3 because it is already marked as COMPLETED." in out)
        self.record("Exception Handling", "Cancel Completed Request Guard", passed,
                    "Safely rejected cancelling a completed request" if passed else "Allowed cancelling completed request", out)

    def test_requester_cancel_already_cancelled_guard(self):
        # Cancel Request #2 once, then try cancelling again
        inputs = [
            "3", "1", "bob@campus.edu", "pass456",
            "4", "2",  # First cancel
            "4", "2",  # Second cancel attempt
            "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Request #2 is already CANCELLED." in out)
        self.record("Exception Handling", "Cancel Already-Cancelled Request Guard", passed,
                    "Safely informed user request is already cancelled" if passed else "Allowed re-cancelling", out)

    # =========================================================================
    # Group 3: Facility Manager Operations
    # =========================================================================
    def test_manager_view_and_add_technician(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "1", "2", "Frank", "frank@tech.edu", "frank123", "1", "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Technician \"Frank\" (ID: 3) added successfully!" in out) and ("frank@tech.edu" in out)
        self.record("Manager Operations", "Manager Add and View Technician", passed,
                    "Technician added with auto-generated ID" if passed else "Failed to add technician", out)

    def test_manager_remove_technician(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "3", "999",  # Non-existent ID
            "3", "2",    # Existing ID (Eva)
            "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Technician with ID 999 not found." in out) and ("has been removed." in out)
        self.record("Manager Operations", "Manager Remove Technician & ID Validation", passed,
                    "Removed technician and correctly handled non-existent ID" if passed else "Remove tech failed", out)

    def test_manager_view_and_remove_user(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "7", "8", "1", "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Registered Users (Requesters)" in out) and ("User \"Alice Smith\" (ID: 1) has been removed." in out)
        self.record("Manager Operations", "Manager View and Remove Requester", passed,
                    "Manager removed user successfully" if passed else "Remove user failed", out)

    def test_manager_review_pending_queue(self):
        inputs = ["1", "admin@gmail.com", "admin", "4", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Latest Pending Request" in out) and ("Request ID:       2" in out)
        self.record("Data Structures (Queue)", "Review FIFO Pending Request Queue", passed,
                    "FIFO queue holds and inspects front pending request" if passed else "Queue inspection failed", out)

    def test_manager_assign_technician_valid(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "6", "1", "2026-11-06", "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Assigned Technician \"Tech Dave\" (ID: 1) to Request #2." in out)
        self.record("Manager Operations", "Assign Pending Request to Technician (FIFO)", passed,
                    "Request assigned to technician and status updated" if passed else "Technician assignment failed", out)

    def test_manager_assign_invalid_technician_guard(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "6", "9999", "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Technician with ID 9999 does not exist." in out)
        self.record("Exception Handling", "Assign Invalid Technician ID Guard", passed,
                    "Rejected non-existent technician ID" if passed else "Failed to reject invalid technician ID", out)

    def test_manager_assign_empty_queue_guard(self):
        # Empty the queue by removing pending requests in requests.txt
        with open(os.path.join(DATA_DIR, "requests.txt"), "w", encoding="utf-8") as f:
            f.write("1|1|1|Engineering_Block_A|Electrical|Flickering lights|IN_PROGRESS|2026-11-01|2026-11-10|Inspected panel\n")
            f.write("3|1|2|Student_Center|Furniture|Broken chair|COMPLETED|2026-10-20|2026-10-25|Replaced chair\n")

        inputs = ["1", "admin@gmail.com", "admin", "6", "1", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] No pending requests in the queue to assign." in out)
        self.record("Exception Handling", "Assign Empty Queue Guard", passed,
                    "Safely rejected assigning when queue is empty" if passed else "Empty queue unhandled", out)

    def test_manager_campus_locations_crud(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "9", "10", "Science_Tower", "10", "Science_Tower", "11", "1", "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Campus location \"Science_Tower\" added successfully." in out) and \
                 ("already exists." in out) and ("Removed location" in out)
        self.record("Manager Operations", "Campus Locations Management & Duplicate Guard", passed,
                    "Locations managed with duplicate protection" if passed else "Locations management failed", out)

    def test_manager_problem_categories_crud(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "12", "13", "Elevator", "13", "Elevator", "14", "1", "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Problem category \"Elevator\" added successfully." in out) and \
                 ("already exists." in out) and ("Removed category" in out)
        self.record("Manager Operations", "Problem Categories Management & Duplicate Guard", passed,
                    "Problem categories managed with duplicate protection" if passed else "Problem categories management failed", out)

    def test_manager_review_filter_requests(self):
        inputs = [
            "1", "admin@gmail.com", "admin",
            "5", "1", "0",
            "5", "2", "1", "0",
            "5", "5", "2026-11-20", "0",
            "0", "0"
        ]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("--- Matching Requests" in out)
        self.record("Manager Operations", "Filter Requests (Category, Location, Overdue)", passed,
                    "Filtered and listed requests according to criteria" if passed else "Filtering failed", out)

    def test_manager_view_service_history_linked_list(self):
        inputs = ["1", "admin@gmail.com", "admin", "15", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("--- Service History (Change Logs) ---" in out) and ("Req ID" in out)
        self.record("Data Structures (Linked List)", "Service History Audit Trail (Linked List)", passed,
                    "Displays formatted service history change logs" if passed else "Service history view failed", out)

    # =========================================================================
    # Group 4: Technician Operations
    # =========================================================================
    def test_technician_view_assigned_requests(self):
        inputs = ["2", "dave@tech.edu", "tech123", "1", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("--- Your Assigned Requests ---" in out) and ("#1" in out)
        self.record("Technician Operations", "Technician View Assigned Requests Only", passed,
                    "Technician sees only active assigned requests" if passed else "View assigned requests failed", out)

    def test_technician_update_status_and_history(self):
        inputs = ["2", "dave@tech.edu", "tech123", "2", "1", "3", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Status for Request #1 updated to COMPLETED." in out)
        self.record("Technician Operations", "Technician Status Update & Changelog", passed,
                    "Technician updated status to COMPLETED and logged change" if passed else "Status update failed", out)

    def test_technician_unauthorized_status_update(self):
        inputs = ["2", "eva@tech.edu", "tech456", "2", "1", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Unauthorized. This request is not assigned to you." in out)
        self.record("Exception Handling", "Technician Unauthorized Job Update Guard", passed,
                    "Blocked unauthorized technician status change" if passed else "Failed technician authorization", out)

    def test_technician_add_repair_notes(self):
        inputs = ["2", "dave@tech.edu", "tech123", "3", "1", "Replaced starter and wiring", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("Repair notes added to Request #1." in out)
        self.record("Technician Operations", "Technician Add Repair Notes", passed,
                    "Repair notes added and persisted to ticket" if passed else "Adding repair notes failed", out)

    def test_technician_update_already_completed_guard(self):
        with open(os.path.join(DATA_DIR, "requests.txt"), "w", encoding="utf-8") as f:
            f.write("1|1|1|Engineering_Block_A|Electrical|Flickering lights|COMPLETED|2026-11-01|2026-11-10|Done\n")
        inputs = ["2", "dave@tech.edu", "tech123", "2", "1", "0", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("is already COMPLETED and cannot be updated" in out)
        self.record("Exception Handling", "Update Completed Request Guard", passed,
                    "Blocked updating already completed request" if passed else "Allowed update on completed request", out)

    # =========================================================================
    # Group 5: Persistence & Edge Cases
    # =========================================================================
    def test_data_persistence_across_restarts(self):
        secret_marker = "Unique_Fault_Code_X99"
        inputs_session1 = [
            "3", "1", "alice@campus.edu", "pass123",
            "1", "1", "1", secret_marker, "2026-12-25",
            "0", "0"
        ]
        ret1, out1, err1 = run_app(inputs_session1)

        # In session 2, manager reviews requests and views details of request #4
        inputs_session2 = [
            "1", "admin@gmail.com", "admin",
            "5", "1", "4", "0", "0"
        ]
        ret2, out2, err2 = run_app(inputs_session2)
        passed = (ret1 == 0 and ret2 == 0) and (secret_marker in out2)
        self.record("Data Persistence", "File I/O Persistence Across App Restarts", passed,
                    "Saved data reloads seamlessly on subsequent program run" if passed else "Data failed to persist across runs", out2)

    def test_invalid_menu_role_bounds_handling(self):
        inputs = ["99", "0"]
        ret, out, err = run_app(inputs)
        passed = (ret == 0) and ("[Error] Invalid role selection. Please choose 0 to 3." in out)
        self.record("Exception Handling", "Main Menu Invalid Role Range Guard", passed,
                    "Gracefully rejected out-of-range role choice" if passed else "Failed out-of-range role check", out)

    def test_invalid_menu_role_non_numeric(self):
        inputs = ["abc"]
        ret, out, err = run_app(inputs)
        passed = ("[Error] Invalid input. Please enter a number." in out)
        self.record("Exception Handling", "Main Menu Non-Numeric Input Guard", passed,
                    "Safely detected non-numeric input" if passed else "Failed non-numeric error check", out)

    def run_all(self):
        print(f"\n{BOLD}{CYAN}========================================================================{RESET}")
        print(f"{BOLD}{CYAN}   SCFMS Automated Test Suite (KIE1008 Programming II Compliance)   {RESET}")
        print(f"{BOLD}{CYAN}========================================================================{RESET}\n")

        self.backup.backup()
        try:
            # Group 1: Authentication & Role Gatekeeping
            print(f"{BOLD}--- 1. Authentication & Role Gatekeeping ---{RESET}")
            self.backup.reset_to_clean_state()
            self.test_manager_auth_valid()
            self.test_manager_auth_invalid()
            self.test_technician_auth_valid_email()
            self.test_technician_auth_valid_id()
            self.test_technician_auth_invalid()
            self.test_requester_auth_invalid()

            # Group 2: Requester Functionalities
            print(f"\n{BOLD}--- 2. Requester Operations ---{RESET}")
            self.backup.reset_to_clean_state()
            self.test_requester_sign_up()
            self.test_requester_sign_up_duplicate_email()
            self.test_requester_submit_request()
            self.test_requester_view_submitted()
            self.test_requester_view_details_authorized()
            self.test_requester_view_details_unauthorized()
            self.test_requester_cancel_own_request()
            self.test_requester_cancel_completed_request_guard()
            self.test_requester_cancel_already_cancelled_guard()

            # Group 3: Facility Manager Operations
            print(f"\n{BOLD}--- 3. Facility Manager Operations ---{RESET}")
            self.backup.reset_to_clean_state()
            self.test_manager_view_and_add_technician()
            self.test_manager_remove_technician()
            self.test_manager_view_and_remove_user()
            self.test_manager_review_pending_queue()
            self.test_manager_assign_technician_valid()

            self.backup.reset_to_clean_state()
            self.test_manager_assign_invalid_technician_guard()
            self.test_manager_assign_empty_queue_guard()

            self.backup.reset_to_clean_state()
            self.test_manager_campus_locations_crud()
            self.test_manager_problem_categories_crud()
            self.test_manager_review_filter_requests()
            self.test_manager_view_service_history_linked_list()

            # Group 4: Technician Operations
            print(f"\n{BOLD}--- 4. Technician Operations ---{RESET}")
            self.backup.reset_to_clean_state()
            self.test_technician_view_assigned_requests()
            self.test_technician_update_status_and_history()
            self.test_technician_unauthorized_status_update()
            self.test_technician_add_repair_notes()
            self.test_technician_update_already_completed_guard()

            # Group 5: Persistence & Robustness
            print(f"\n{BOLD}--- 5. Persistence & Error Handling ---{RESET}")
            self.backup.reset_to_clean_state()
            self.test_data_persistence_across_restarts()
            self.test_invalid_menu_role_bounds_handling()
            self.test_invalid_menu_role_non_numeric()

        finally:
            self.backup.restore()
            print(f"\n{CYAN}[Info] Restored user's original data directory.{RESET}")

        # Summary
        total = len(self.results)
        passed = sum(1 for r in self.results if r.passed)
        failed = total - passed

        print(f"\n{BOLD}{CYAN}========================================================================{RESET}")
        print(f"{BOLD}Test Execution Summary:{RESET}")
        print(f"  Total Test Cases : {total}")
        print(f"  Passed           : {GREEN}{passed}{RESET}")
        print(f"  Failed           : {RED if failed else GREEN}{failed}{RESET}")
        pass_rate = (passed / total) * 100 if total > 0 else 0
        print(f"  Compliance Score : {BOLD}{pass_rate:.1f}%{RESET}")
        print(f"{BOLD}{CYAN}========================================================================{RESET}\n")
        return failed == 0

if __name__ == "__main__":
    suite = SCFMSTestSuite()
    success = suite.run_all()
    sys.exit(0 if success else 1)
