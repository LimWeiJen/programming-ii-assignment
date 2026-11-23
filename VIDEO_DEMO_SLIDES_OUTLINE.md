Demonstration on all three roles.

---

First of all, let's look at our file structure. We divided our files into three different folders, which are data structures, classes, and data.

In the classes folder, we have basically defined all the classes (or custom data types) that we will be working with on this project. The examples include request class (which stores the information of a user request), a technician class (which stores the information of a technician), and so on. As requested, we have created a base class called person, and "technician", "facility manager", and "requester (user)" inherited from that class.

The specific functions/attributes of each class is shown in this slide, or if you want, you can also look into the header files in the source code, which had outlined all the functions of each of the classes we have implemented. We also ensure that each of the classes followed the best practice, like adding destructors for memory management, labeling some functions as virtual or const when necessary, and so on.

In the data structure folder, we stored our implemented data structure, which is the queue and also the linked list. As we all know, a queue is a data structure which acts kind of like a list with it's own data type stored, just that we are only able to get or pop the first element. The data type we are storing in our queue is defined in queue node. And queue node is actually just a node that contains a pointer pointing to a request, and also another pointer to the next queue node. The specific implementation of our queue data structure can be seen in the source code.

If you look into the linked list folder, you will see a little more files than the queue folder. This is because the assignment explicitly forbid us to use build in data types like vector. This means we will have to use linked list everywhere. So, we've created a base class called linked list, and then we all created sub classes of linked list specific to the data type that we will be storing in the linked list. For instance, we want to store and array of strings, but since we cannot use the STL containers, so we have to create our own linked list data type just to store a bunch of strings in a list. Similarly, we have linked lists to store our change log, our requesters, our technicians, and so on.

Then in the data folder, we implement persistent data storage. We created a class called data manager which mainly handles persistent storange. It basically has functions to handle the loading of data and also the saving of data. The data is stored in text files. Each new line represents a new set of data, and in one line, the parameters in the data is separated by '|'. For example, to store the request data, we will basically go through all the details of the request, and add them into a string separating them by '|'. Then this string will be added as a new line into the request text file. The same logic is used to retrieve the request data. Basically, read the request text file, separate the text by line, then create new request objects and fill in the data by splitting the string using '|'.

Now finally, let's look at main.cpp, which is where our main logic is stored. It will first load the data from the data manager. Afterwards, it will ask user for its role for the user to select. Then depending on the role selected, it will create an object for that specific role. If that role requires authentication (for example, facility manager), it will ask for the username and password. Only after the username and password is successfully filled in, the program will only then let the user proceed. The program will then call the display menu function for that role, and then use a switch case to determine which action should be taken (or which function in the object should be called) depending on the user's choices.

---

The testing is actually done by writing a custom python script which can read and write to the terminal. This is because there are way too many edge cases for the current software. To manually test out all the test cases will be too time consuming. Hence, we've first manually listed out all the edge cases, like signing in with invalid credentials, trying to delete an non-existent request, etc, and then run a python script to help us test out all the cases.

---

The main challenge we face in this assignment is the restriction of using STL containers. We believe that the current implementation of our software is highly inefficient, and the most efficient way to implement this software is by using the built-in vector class. It basically serves as an array with dynamic size, meaning we can add and delete elements, and also use it as a function return type. This will make our code so much shorter and so much more convenient rather than implementing custom data types. But since it is restricted, our solution is to implement our own data structures, which are the queue and linked list.

Another challenge is the scope of this project, which is too big to ensure that everything works together. If you were to create the class one by one, you will soon realize that there are some functions that should be implemented but didn't. And also some functions that we implemented doesn't even get used in the end. So, if we were to implement the classes one by one, we will have to go back and forth, which is very time consuming. Our solution to this is to implement a hierarchal approach while creating this software. We start by creating all the folders, and creating all the necessary header files. Afterwards, we straight away code up our main function to identify what features we will need to have in each classes. This process requires going back and forth, but at least we can accurately outline all the functions needed and all of the parameters required in those functions. Finally, only then we created the cpp which will populate all the classes with the necessary implementations of the functions inside those classes.

The third challenge is permanent storage. This is because this knowledge is not learned in lectures and we will have to learn it ourselves. We have to learn libraries like fstream to store data and to read data into a text file.

---

Lim Wei Jen: I outlined all the file structures and created all the necessary header files. I also implemented the main function, which creates the main software loop.

Joo Eu-Jin: I am in charge of implementing the sub functions of each class (except for data storage), including the ones in data structures to make sure that all of them can work correctly without failure.

Tan Jia Shun: I am the researcher on permanent data storage. I am in charge of implementing everything inside the data folder to make sure that everything can get stored properly.

Lee Wen Yi: I am the tester of this project. I am in charge in outlining all the edge cases and writing the python code to test all the cases out.