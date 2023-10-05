// File Name: TaskFlow.cpp

// Author: Group 4 (Developer: Larry Hellen)

// Email Address: lhellen@go.pasadena.edu

// Project Version: 0.1

// Description: A task manager

// Last Changed: October 4, 2023

#include <iostream>

using namespace std;
int currentDate[3] = {}; //{year, month, date}
const int maxTaskCategories = 10;
const int maxTotalTasks = 10;
string taskCategories[maxTaskCategories] = {};
string totalTasks[maxTotalTasks] = {};

void featureSelection();
void taskCreation();
void taskDeletion();
void taskView();
void dateSelection();
void taskCategoryMenu();
void taskCategoryCreator();
void taskCategoryDeleter();

int main()
{
	cout << "Welcome user!\n";
	cout << "Please define some task categories first, such as work, dentist, bithday.\n\n";
	taskCategoryCreator();
}

//Serves as the main menu for the program, displaying and leading to all the other features based on user input.
//Sends user to any of the menus availble based on input
void featureSelection()
{
	//The possible options for the user
	const string dateOption = "1. Date selection\n";
	const string taskCategoryOption = "2. Task cateogory menu\n";
	const string taskCreationOption = "3. Create a new task\n";
	const string taskDeletionOption = "4. Delete a task\n";
	const string taskViewOption = "5. View your tasks\n";
	string currentFeatures = "0. Exit the program\n";
	int userOption = 0;

	//Only allow the user access to the task options if they have selected a date already
	currentFeatures += dateOption + taskCategoryOption;
	if (!(currentDate[0] == 0 && currentDate[1] == 0 && currentDate[2] == 0))
	{
		currentFeatures += taskCreationOption + taskDeletionOption + taskViewOption;
	}

	//Display the current possible features and ask the user what they want to do
	cout << "Here are the currently availble features:\n";
	cout << currentFeatures;
	cout << "Please choose a feature by number: ";
	cin >> userOption;
	cout << endl;
	
	//Send the user to the right menu
	if (userOption == 0)
	{
		return;
	}
	else if (userOption == 1)
	{
		dateSelection();
	}
	else if (userOption == 2)
	{
		taskCategoryMenu();
	}
	else if (userOption == 3)
	{
		taskCreation();
	}
	else if (userOption == 4)
	{
		taskDeletion();
	}
	else if (userOption == 5)
	{
		taskView();
	}
}

//Overview: Create a new task based on player input and add its name into the totalTasks array. Note: nothing else about the task is stored for now
//Sends user to either main menu or allow more tasks to be created based on user input
void taskCreation()
{
	string taskName = "";
	string taskTime = "";
	string taskCategory = "";
	string details = "";
	int userOption = 0;

	//Collect information about the new task
	cout << "Enter the name for you task: ";
	cin >> taskName;
	cout << endl;

	cout << "Enter the time for this task: ";
	cin >> taskTime;
	cout << endl;

	cout << "Enter the category for this task: ";
	cin >> taskCategory;
	cout << endl;

	cout << "Enter the details for this task: ";
	cin >> details;
	cout << endl;

	//Find the first empty spot in the totalTasks array and add the task name there
	for (int i = 0; i < maxTotalTasks; i++)
	{
		if (totalTasks[i] == "")
		{
			totalTasks[i] = taskName;
			break;
		}
	}

	cout << "Alright, a new task " << taskName << " has been created!\nEnter 1 to return to create another task or 2 to return to the main menu: ";
	cin >> userOption;
	cout << endl;

	//Based on user input, send them to a new menu
	if (userOption == 1)
	{
		taskCreation();
	}
	else if (userOption == 2)
	{
		featureSelection();
	}
}

//Overview: Finds a task based on the task name and then deletes it from the array of tasks
//Sends user to either main menu or allow more tasks to be deleted based on user input
void taskDeletion()
{
	string taskName = "";

	int userOption = 0;

	cout << "Enter the name of the task to delete: ";
	cin >> taskName;
	cout << endl;

	//Find the task name in the array of totalTasks and set that position to be blank
	for (int i = 0; i < maxTotalTasks; i++)
	{
		if (totalTasks[i] == taskName)
		{
			totalTasks[i] = "";
			break;
		}
	}

	cout << "Alright, the task " << taskName << " has been deleted!\nEnter 1 to return to delete another task or 2 to return to the main menu: ";
	cin >> userOption;
	cout << endl;

	//Send the user to a new menu
	if (userOption == 1)
	{
		taskDeletion();
	}
	else if (userOption == 2)
	{
		featureSelection();
	}
}

//Overview: Print the current saved tasks to the console, and send user to main menu
void taskView()
{
	//Iterate through the list of tasks saved, and print all non empty tasks to the console.
	cout << "Here are your current tasks (the maximum is 10):\n";
	for (int i = 0; i < maxTotalTasks; i++)
	{
		if (totalTasks[i] != "")
		{
			cout << totalTasks[i] << endl;
		}
	}
	featureSelection();
}

//Prompts user for the date they want to modify and saves it to currentDate
//Sends the user to the main menu or allows them to select a new date based on input
void dateSelection()
{
	int year = 0;
	int month = 0;
	int day = 0;
	int userOption = 0;

	cout << "Which year would you like to go to: ";
	cin >> year;
	cout << "Which month number would you like to go to (ex 4 for april): ";
	cin >> month;
	cout << "Which day would you like to go to: ";
	cin >> day;
	cout << endl;

	//Save the date, month, and day to their locations in the array
	currentDate[0] = year;
	currentDate[1] = month;
	currentDate[2] = day;

	//Repeat their date back to them
	cout << "Your selected date is (m/d/y): " << month << ", " << day << ", " << year << endl;

	cout << "What would you like to do? Enter 1 to choose a new date or 2 to return to the main menu: ";
	cin >> userOption;
	cout << endl;

	//Sends user to new menu
	if (userOption == 1)
	{
		dateSelection();
	}
	else if (userOption == 2)
	{
		featureSelection();
	}
}

//Displays the current task categoreis created
//Sends the user to task category creation, deletion, or main menu based on input
void taskCategoryMenu()
{
	int userOption = 0;

	//Print all non empty task categories to console
	cout << "Here are your current task categories (the maximum is 10):\n";
	for (int i = 0; i < maxTaskCategories; i++)
	{
		if (taskCategories[i] != "")
		{
			cout << taskCategories[i] << endl;
		}
	}
	cout << endl;

	cout << "What would you like to do? Enter 1 to create a new task category, 2 to delete a task category, and 3 to exit to the main menu: ";
	cin >> userOption;
	cout << endl;

	//Send to new menu
	if (userOption == 1)
	{
		taskCategoryCreator();
	}
	else if (userOption == 2)
	{
		taskCategoryDeleter();
	}
	else if (userOption == 3)
	{
		featureSelection();
	}
}

//Create a new task category based on player input and add its name into the taskCategories array
//Sends user to either task category menu, main menu, or allows for more tasks to be created based on user input
void taskCategoryCreator()
{
	string taskCategoryName = "";
	int userOption = 0;

	cout << "Enter the new name for your task category: ";
	cin >> taskCategoryName;
	cout << endl;

	//Find the first empty spot in the taskCategories array and add the task category there
	for (int i = 0; i < maxTaskCategories; i++)
	{
		if (taskCategories[i] == "")
		{
			taskCategories[i] = taskCategoryName;
			break;
		}
	}

	cout << "Alright, a new task category " << taskCategoryName << " has been created!\nEnter 1 to return to create another task category, 2 to return to the task category menu, and 3 to return to the main menu: ";
	cin >> userOption;
	cout << endl;

	//Send the user to a new menu
	if (userOption == 1)
	{
		taskCategoryCreator();
	}
	else if (userOption == 2)
	{
		taskCategoryMenu();
	}
	else if (userOption == 3)
	{
		featureSelection();
	}
}

//Delete an exisiting task category based on player input and add its name into the taskCategories array
//Sends user to either task category menu, main menu, or allows for more tasks to be created based on user input
void taskCategoryDeleter()
{
	string taskCategoryName = "";
	int userOption = 0;

	cout << "Enter the name of the cateogory you want to delete: ";
	cin >> taskCategoryName;
	cout << endl;


	//Find the task category name in the array of taskCategories and set that position to be blank
	for (int i = 0; i < maxTaskCategories; i++)
	{
		if (taskCategories[i] == taskCategoryName)
		{
			taskCategories[i] = "";
			break;
		}
	}

	cout << "Alright, the task category " << taskCategoryName << " has been deleted!\nEnter 1 to return to delete another task category, 2 to return to the task category menu, and 3 to return to the main menu: ";
	cin >> userOption;
	cout << endl;

	//Send user to new menu
	if (userOption == 1)
	{
		taskCategoryDeleter();
	}
	else if (userOption == 2)
	{
		taskCategoryMenu();
	}
	else if (userOption == 3)
	{
		featureSelection();
	}
}