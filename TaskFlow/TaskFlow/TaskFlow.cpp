// File Name: TaskFlow.cpp

// Author: Group 4 (Developer: Larry Hellen, Lukas Li)

// Email Address: lhellen@go.pasadena.edu

// Project Version: 0.3

// Description: A task manager

// Last Changed: October 14, 2023

#include <iostream>
#include <vector>
using namespace std;

int currentDate[3] = {}; //{year, month, date}
vector<string> taskCategoriesList;

typedef void(*optionList)(); //Data type for arrays that hold void functions

void featureSelection();
void taskCreation();
void taskDeletion();
void taskView();
void dateSelection();
void taskCategoryMenu();
void taskCategoryCreator();
void taskCategoryDeleter();
void ender();

//Predefined messages for each option
string DATE_SELECT = "Date selection";
string NEW_DATE = "Enter a new date";
string CATEGORY_MENU = "Task category menu";
string NEW_TASK = "Create a new task";
string DELETE_TASK = "Delete a task";
string VIEW_TASK = "View your tasks";
string ANOTHER_TASK = "Create another task";
string ANOTHER_DELETE_TASK = "Delete another task";
string MAIN_MENU = "Return to main menu";
string CAT_MENU_RETURN = "Return to category menu";
string NEW_CAT = "Create a new task category";
string DELETE_CAT = "Delete a task category";
string ANOTHER_CAT = "Create another task category";
string ANOTHER_DELETE_CAT = "Delete another category";
string EXIT = "Exit program";

//The class for the object Task, stores information about tasks
class Task
{
	public:
		string name;
		string time;
		string category;
		string details;

		Task(string taskName, string taskTime, string taskCategory, string taskDetails)
		{
			name = taskName;
			time = taskTime;
			category = taskCategory;
			details = taskDetails;
		}
};

vector<Task> taskList; //Contains all the tasks within the program

//Class that creates menu objects that allow for various options to be provided to user
class Menu
{
public:
	optionList* options; //Array of functions
	string* optionTitles; //Array of messages
	int choice, len;

	//Fills in member values for the object
	void syncOptions(optionList* list, string* messages, int length)
	{
		len = length;
		options = new optionList[length];
		optionTitles = new string[length];
		

		for (int i = 0; i < len; i++)
		{
			options[i] = list[i];
			optionTitles[i] = messages[i];
		}
	}


	//Obtains user input and then executes the corresponding function
	void menuChoice()
	{
		//Lists options for user
		for (int i = 0; i < len; i++)
		{
			int listNum = i + 1;

			cout << listNum << ". " << optionTitles[i] << endl;
		}

		//Loop that will continue until user provides valid input
		while (true)
		{
			bool invalid;

			cout << endl << "Enter choice here: ";
			cin >> choice;
			invalid = cin.fail(); //Returns true if the wrong data type is entered

			if (invalid)
			{
				cout << "Please enter the number corresponding with one of the choices.";

				//Prevents eternal looping after cin.fail
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (choice > len || choice < 1 || choice != floor(choice)) //Makes sure the number is within the bounds that are given
			{
				cout << "Please enter the number corresponding with one of the choices."; 
			}
			else
			{
				break; //If input is valid, break from loop and continue
			}
		}

		cout << endl;
		options[choice - 1](); //Executes the next function
	}
};



int main()
{
	cout << "Welcome user!\n";
	cout << "Please define some task categories first, such as work, dentist, birthday.\n\n";
	taskCategoryCreator();
}

//Serves as the main menu for the program, displaying and leading to all the other features based on user input.
//Sends user to any of the menus availble based on input
void featureSelection()
{
	optionList currentFeatures1[] = { dateSelection, taskCategoryMenu, taskCreation, taskDeletion, taskView, ender };
	string optionNames1[] = { DATE_SELECT, CATEGORY_MENU, NEW_TASK, DELETE_TASK, VIEW_TASK, EXIT };

	optionList currentFeatures2[] = { dateSelection, taskCategoryMenu, ender };
	string optionNames2[] = { DATE_SELECT, CATEGORY_MENU, EXIT };

	Menu mainMenu;

	//Only allow the user access to the task options if they have selected a date already
	if (!(currentDate[0] == 0 && currentDate[1] == 0 && currentDate[2] == 0))
	{
		mainMenu.syncOptions(currentFeatures1, optionNames1, sizeof(currentFeatures1) / sizeof(currentFeatures1[0]));
	}
	else
	{
		mainMenu.syncOptions(currentFeatures2, optionNames2, sizeof(currentFeatures2) / sizeof(currentFeatures2[0]));
	}

	mainMenu.menuChoice();
}

//Overview: Create a new task based on player input and add its name into the totalTasks array.
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

	//Create a new task and add it to the list of tasks
	Task createdTask = Task(taskName, taskTime, taskCategory, details);
	taskList.push_back(createdTask);

	cout << "Alright, a new task " << taskName << " has been created!\n\n";

	optionList currentFeatures[] = { taskCreation, featureSelection };
	string optionNames[] = { ANOTHER_TASK, MAIN_MENU };

	Menu fromTaskCreation;
	fromTaskCreation.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromTaskCreation.menuChoice();
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

	//Find the task name in list of tasks and remove that element
	for (int i = 0; i < taskList.size(); i++)
	{
		if (taskList[i].name == taskName)
		{
			taskList.erase(taskList.begin() + i);
			break;
		}
	}

	cout << "Alright, the task " << taskName << " has been deleted!\n\n";

	optionList currentFeatures[] = { taskDeletion, featureSelection };
	string optionNames[] = { ANOTHER_DELETE_TASK, MAIN_MENU };

	Menu fromTaskDeletion;
	fromTaskDeletion.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromTaskDeletion.menuChoice();
}

//Overview: Print the current saved tasks to the console, and send user to main menu
void taskView()
{
	

	//Iterate through the list of tasks saved, and print all non empty tasks to the console.
	cout << "Here are your current tasks:\n";
	for (int i = 0; i < taskList.size(); i++)
	{
		cout << taskList[i].name;
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

	optionList currentFeatures[] = { dateSelection, featureSelection };
	string optionNames[] = { NEW_DATE, MAIN_MENU };

	Menu fromSetDate;
	fromSetDate.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromSetDate.menuChoice();
}

//Displays the current task categoreis created
//Sends the user to task category creation, deletion, or main menu based on input
void taskCategoryMenu()
{
	

	int userOption = 0;

	//Print all non empty task categories to console
	cout << "Here are your current task categories:\n";
	for (int i = 0; i < taskCategoriesList.size(); i++)
	{
		cout << taskCategoriesList[i] << endl;

	}
	cout << endl;

	optionList currentFeatures[] = { taskCategoryCreator, taskCategoryDeleter, featureSelection };
	string optionNames[] = { NEW_CAT, DELETE_CAT, MAIN_MENU };

	Menu fromCatMenu;
	fromCatMenu.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCatMenu.menuChoice();
}

//Create a new task category based on player input and add its name into the task categories list
//Sends user to either task category menu, main menu, or allows for more tasks to be created based on user input
void taskCategoryCreator()
{
	string taskCategoryName = "";
	int userOption = 0;

	cout << "Enter the new name for your task category: ";
	cin >> taskCategoryName;
	cout << endl;

	taskCategoriesList.push_back(taskCategoryName);

	cout << "Alright, a new task category " << taskCategoryName << " has been created!\n\n";

	optionList currentFeatures[] = { taskCategoryCreator, taskCategoryMenu, featureSelection };
	string optionNames[] = { ANOTHER_CAT, CAT_MENU_RETURN, MAIN_MENU };
	

	Menu fromCatCreate;
	fromCatCreate.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCatCreate.menuChoice();
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
	for (int i = 0; i < taskCategoriesList.size(); i++)
	{
		if (taskCategoriesList[i] == taskCategoryName)
		{
			taskCategoriesList.erase(taskCategoriesList.begin() + i);
			break;
		}
	}

	cout << "Alright, the task category " << taskCategoryName << " has been deleted!\n\n";

	optionList currentFeatures[] = { taskCategoryDeleter, taskCategoryMenu, featureSelection };
	string optionNames[] = { ANOTHER_DELETE_CAT, CAT_MENU_RETURN, MAIN_MENU };

	Menu fromCatDelete;
	fromCatDelete.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCatDelete.menuChoice();
}



//Function that ends program and fits into the optionList array
void ender()
{
	cout << "";
}