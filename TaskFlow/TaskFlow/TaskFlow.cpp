// File Name: TaskFlow.cpp

// Author: Group 4 (Developer: Larry Hellen)

// Email Address: lhellen@go.pasadena.edu

// Project Version: 0.1

// Description: A task manager

// Last Changed: October 4, 2023

#include <iostream>


int currentDate[3] = {}; //{year, month, date}
const int maxTaskCategories = 10;
const int maxTotalTasks = 10;
std::string taskCategories[maxTaskCategories] = {};
std::string totalTasks[maxTotalTasks] = {};

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
std::string DATE_SELECT = "Date selection";
std::string NEW_DATE = "Enter a new date";
std::string CATEGORY_MENU = "Task category menu";
std::string NEW_TASK = "Create a new task";
std::string DELETE_TASK = "Delete a task";
std::string VIEW_TASK = "View your tasks";
std::string ANOTHER_TASK = "Create another task";
std::string ANOTHER_DELETE_TASK = "Delete another task";
std::string MAIN_MENU = "Return to main menu";
std::string CAT_MENU_RETURN = "Return to category menu";
std::string NEW_CAT = "Create a new task category";
std::string DELETE_CAT = "Delete a task category";
std::string ANOTHER_CAT = "Create another task category";
std::string ANOTHER_DELETE_CAT = "Delete another category";
std::string EXIT = "Exit program";


//Class that creates menu objects that allow for various options to be provided to user
class menu
{
public:
	optionList* options; //Array of functions
	std::string* optionTitles; //Array of messages
	int choice, len;

	//Fills in member values for the object
	void syncOptions(optionList* list, std::string* messages, int length)
	{
		len = length;
		options = new optionList[length];
		optionTitles = new std::string[length];
		

		for (int i = 0; i <= (len - 1); i++)
		{
			options[i] = list[i];
			optionTitles[i] = messages[i];
		}
	}


	//Obtains user input and then executes the corresponding function
	void menuChoice()
	{
		//Lists options for user
		for (int i = 0; i <= (len - 1); i++)
		{
			int listNum = i + 1;

			std::cout << listNum << ". " << optionTitles[i] << std::endl;
		}

		//Loop that will continue until user provides valid input
		while (true)
		{
			bool invalid;

			std::cout << std::endl << "Enter choice here: ";
			std::cin >> choice;
			invalid = std::cin.fail(); //Returns true if the wrong data type is entered

			if (invalid)
			{
				std::cout << "Please enter the number corresponding with one of the choices.";

				//Prevents eternal looping after cin.fail
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (choice > len || choice < 1 || choice != floor(choice)) //Makes sure the number is within the bounds that are given
			{
				std::cout << "Please enter the number corresponding with one of the choices."; 
			}
			else
			{
				break; //If input is valid, break from loop and continue
			}
		}

		std::cout << std::endl;
		options[choice - 1](); //Executes the next function
	}
};



int main()
{
	using namespace std;

	cout << "Welcome user!\n";
	cout << "Please define some task categories first, such as work, dentist, birthday.\n\n";
	taskCategoryCreator();
}

//Serves as the main menu for the program, displaying and leading to all the other features based on user input.
//Sends user to any of the menus availble based on input
void featureSelection()
{
	using namespace std;


	/*
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
	*/


	optionList currentFeatures1[] = { dateSelection, taskCategoryMenu, taskCreation, taskDeletion, taskView, ender };
	string optionNames1[] = { DATE_SELECT, CATEGORY_MENU, NEW_TASK, DELETE_TASK, VIEW_TASK, EXIT };

	optionList currentFeatures2[] = { dateSelection, taskCategoryMenu, ender };
	string optionNames2[] = { DATE_SELECT, CATEGORY_MENU, EXIT };

	/*
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
	*/

	menu mainMenu;

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

//Overview: Create a new task based on player input and add its name into the totalTasks array. Note: nothing else about the task is stored for now
//Sends user to either main menu or allow more tasks to be created based on user input
void taskCreation()
{
	using namespace std;

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

	/*
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
	*/

	cout << "Alright, a new task " << taskName << " has been created!\n\n";

	optionList currentFeatures[] = { taskCreation, featureSelection };
	string optionNames[] = { ANOTHER_TASK, MAIN_MENU };

	menu fromTaskCreation;
	fromTaskCreation.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromTaskCreation.menuChoice();
}

//Overview: Finds a task based on the task name and then deletes it from the array of tasks
//Sends user to either main menu or allow more tasks to be deleted based on user input
void taskDeletion()
{
	using namespace std;

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

	/*
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
	*/

	cout << "Alright, the task " << taskName << " has been deleted!\n\n";

	optionList currentFeatures[] = { taskDeletion, featureSelection };
	string optionNames[] = { ANOTHER_DELETE_TASK, MAIN_MENU };

	menu fromTaskDeletion;
	fromTaskDeletion.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromTaskDeletion.menuChoice();
}

//Overview: Print the current saved tasks to the console, and send user to main menu
void taskView()
{
	using namespace std;

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
	using namespace std;

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

	/*
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
	*/

	optionList currentFeatures[] = { dateSelection, featureSelection };
	string optionNames[] = { NEW_DATE, MAIN_MENU };

	menu fromSetDate;
	fromSetDate.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromSetDate.menuChoice();
}

//Displays the current task categoreis created
//Sends the user to task category creation, deletion, or main menu based on input
void taskCategoryMenu()
{
	using namespace std;

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

	/*
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
	*/

	optionList currentFeatures[] = { taskCategoryCreator, taskCategoryDeleter, featureSelection };
	string optionNames[] = { NEW_CAT, DELETE_CAT, MAIN_MENU };

	menu fromCatMenu;
	fromCatMenu.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCatMenu.menuChoice();
}

//Create a new task category based on player input and add its name into the taskCategories array
//Sends user to either task category menu, main menu, or allows for more tasks to be created based on user input
void taskCategoryCreator()
{
	using namespace std;

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

	/*
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
	*/

	cout << "Alright, a new task category " << taskCategoryName << " has been created!\n\n";

	optionList currentFeatures[] = { taskCategoryCreator, taskCategoryMenu, featureSelection };
	string optionNames[] = { ANOTHER_CAT, CAT_MENU_RETURN, MAIN_MENU };
	

	menu fromCatCreate;
	fromCatCreate.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCatCreate.menuChoice();
}

//Delete an exisiting task category based on player input and add its name into the taskCategories array
//Sends user to either task category menu, main menu, or allows for more tasks to be created based on user input
void taskCategoryDeleter()
{
	using namespace std;

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

	/*
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
	*/

	cout << "Alright, the task category " << taskCategoryName << " has been deleted!\n\n";

	optionList currentFeatures[] = { taskCategoryDeleter, taskCategoryMenu, featureSelection };
	string optionNames[] = { ANOTHER_DELETE_CAT, CAT_MENU_RETURN, MAIN_MENU };

	menu fromCatDelete;
	fromCatDelete.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCatDelete.menuChoice();
}



//Function that ends program and fits into the optionList array
void ender()
{
	std::cout << "";
}



//I have made the list class, I am not sure what changes have been made that might make this class useless, but I hope it can be of some use. Old menu code is still present, just commented out.