@echo off
echo Compiling SCFMS (main.exe)...
g++ -std=c++17 ^
  main.cpp ^
  "classes/person/Person.cpp" ^
  "classes/person/facility manager/FacilityManager.cpp" ^
  "classes/person/requester/Requester.cpp" ^
  "classes/person/technician/Technician.cpp" ^
  "classes/request/Request.cpp" ^
  "data/DataManager.cpp" ^
  "data structures/linked list/LinkedList.cpp" ^
  "data structures/linked list/RequestLinkedList.cpp" ^
  "data structures/linked list/TechnicianLinkedList.cpp" ^
  "data structures/linked list/RequesterLinkedList.cpp" ^
  "data structures/linked list/ChangeLogLinkedList.cpp" ^
  "data structures/linked list/StringLinkedList.cpp" ^
  "data structures/linked list/changelog/ChangeLog.cpp" ^
  "data structures/queue/Queue.cpp" ^
  "data structures/queue/queue node/QueueNode.cpp" ^
  -o main.exe

if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] main.exe compiled successfully!
) else (
    echo.
    echo [ERROR] Compilation failed.
)
