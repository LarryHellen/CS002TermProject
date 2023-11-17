// File Name: TaskFlow.cpp

// Author: Group 4 (Developer: Larry Hellen, Lukas Li)

// Email Address: lhellen@go.pasadena.edu

// Project Version: 0.7

// Description: A task manager

// Last Changed: October 24, 2023

#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

typedef void(*optionList)(); //Data type for arrays that hold void functions
class Task;
class Menu;

vector<string> taskCategoriesList;
vector<Task> taskList; //Contains all the tasks within the program
vector<Task> viewingList; //Version of taskList that is edited by view settings function
int settings[]{ 0 , 0 }; //Holds the results of the view settings function

void featureSelection();
void taskCreation();
void taskDeletion();
void taskView();
void taskViewAll();
void viewSettings();
void sortByPriority();
void sortByDate();
void viewChoice();
void taskCategoryCreator();
void taskCategoryDeleter();
void editTask();
void completeTask();
void removeCompleted();
void applySettings();
int* stringToDate (string dateString);
void ender();

//Predefined messages for each option
string const NEW_TASK = "Create a new task";
string const DELETE_TASK = "Delete a task";
string const VIEW_TASK = "View your tasks";
string const VIEW_ONE = "View a specific date's tasks";
string const VIEW_ALL = "View all of your tasks";
string const EDIT_TASK = "Edit a task";
string const ANOTHER_TASK = "Create another task";
string const ANOTHER_DELETE_TASK = "Delete another task";
string const MAIN_MENU = "Return to main menu";
string const NEW_CAT = "Create a new task category";
string const DELETE_CAT = "Delete a task category";
string const ANOTHER_CAT = "Create another task category";
string const ANOTHER_DELETE_CAT = "Delete another category";
string const EDIT_ANOTHER = "Edit another task";
string const COMPLETE_TASK = "Set a task to completed";
string const COMPLETE_ANOTHER_TASK = "Set another task to completed";
string const VIEW_SETTINGS = "Change your view settings";
string const EXIT = "Exit program";

int const MAX_TIME_LENGTH = 11, MAX_DETAILS_LENGTH = 100, MAX_CATEGORY_LENGTH = 20, MAX_NAME_LENGTH = 30, MAX_DATE_LENGTH = 11, MAX_PRIORITY_LENGTH = 7;


int main()
{
	cout << "Welcome user!\n";
	cout << "Please define some task categories first, such as work, dentist, birthday.\n\n";
	taskCategoryCreator();
}

//The class for the object Task, stores information about tasks
class Task
{
	public:
		string name;
		string time;
		string category;
		string priority;
		string details;
		string completion = "false";
		int day;
		int month;
		int year;

		//taskDate must be in the format MM/DD/YYYY
		Task(string taskName, string taskDate, string taskTime, string taskCategory, string taskPriority, string taskDetails)
		{
			name = taskName;
			time = taskTime;
			category = taskCategory;
			priority = taskPriority;
			details = taskDetails;
			int* dateArr = stringToDate(taskDate);
			day = dateArr[1];
			month = dateArr[0];
			year = dateArr[2];
		}

		Task(string inputFormat)
		{
			int nameIndex = inputFormat.find('{') + 1;
			int timeIndex = inputFormat.find('}') + 1;
			int detailsIndex = inputFormat.find('|') + 1;
			int priorityIndex = inputFormat.find('-') + 1;
			int completionIndex = inputFormat.find('@') + 1;
			int monthIndex = inputFormat.find('~') + 1;
			int dayIndex = inputFormat.find('%') + 1;
			int yearIndex = inputFormat.find('^') + 1;

			category = setInfoFromSave(inputFormat, 0, (nameIndex - 1));
			name = setInfoFromSave(inputFormat, nameIndex, timeIndex);
			time = setInfoFromSave(inputFormat, timeIndex, detailsIndex);
			details = setInfoFromSave(inputFormat, detailsIndex, priorityIndex);
			priority = setInfoFromSave(inputFormat, priorityIndex, completionIndex);
			completion = setInfoFromSave(inputFormat, completionIndex, monthIndex);
			month = stoi(setInfoFromSave(inputFormat, monthIndex, dayIndex));
			day = stoi(setInfoFromSave(inputFormat, dayIndex, yearIndex));
			year = stoi(setInfoFromSave(inputFormat, yearIndex, -1));
		}

		string setInfoFromSave(string inputFormat, int firstIndex, int secondIndex)
		{
			string info = "";
			if (secondIndex != -1)
			{
				info = inputFormat.substr(firstIndex, (secondIndex - firstIndex - 1));
			}
			else
			{
				info = inputFormat.substr(firstIndex);
			}
			return info;
		}

		string outputFormat(bool isSave = false)
		{
			string taskInfo = "";
			if (isSave)
			{
				taskInfo += category + "{" + name + "}" + time + "|" + details + "-" + priority + '@' + completion + "~" + to_string(month) + "%" + to_string(day) + "^" + to_string(year);
			}
			else
			{
				taskInfo += category + " - " + name + " at " + time + ": " + details + "- " + priority + " priority| Completed: " + completion + ".";
			}

			return taskInfo;
		}

		void editName(string newName)
		{
			name = newName;
		}

		void editTime(string newTime)
		{
			time = newTime;
		}

		void editCategory(string newCategory)
		{
			category = newCategory;
		}

		void editPriority(string newPriority)
		{
			priority = newPriority;
		}

		void editDetails(string newDetails)
		{
			details = newDetails;
		}

		void editDate(string newDate)
		{
			int* newDateArr = stringToDate(newDate);
			day = newDateArr[1];
			month = newDateArr[0];
			year = newDateArr[2];
		}

		void completeTask()
		{
			completion = "true";
		}
};


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

void loadFromFile()
{
	ifstream saveFile;
	string fileStart;
	int taskSizeIndex;
	int taskSize;
	int catSizeIndex;
	int catSize;

	saveFile.open("save_file");

	saveFile >> fileStart;

	taskSizeIndex = fileStart.find(':') + 1;
	taskSize = stoi(fileStart.substr(taskSizeIndex));
	
	taskList.clear();

	for (int i = 0; i < taskSize; i++)
	{
		string taskContents;
		getline(saveFile, taskContents);

		Task loadedTask = Task(taskContents);
		
		taskList.push_back(loadedTask);
	}

	saveFile >> fileStart;

	catSizeIndex = fileStart.find(':') + 1;
	catSize = stoi(fileStart.substr(catSizeIndex));

	taskCategoriesList.clear();

	for (int i = 0; i < catSize; i++)
	{
		string catName;
		getline(saveFile, catName);

		taskCategoriesList.push_back(catName);
	}

	saveFile.close();
}


void saveToFile()
{
	ofstream saveFile;
	string saveContents;

	string taskSize = to_string(taskList.size());
	saveContents = "TASKLIST" + ':' + taskSize;
	

	for (int i = 0; i < taskList.size(); i++)
	{
		saveContents += taskList[i].outputFormat(true) + "\n";
	}

	string catSize = to_string(taskCategoriesList.size());
	saveContents += "CATLIST" + ':' + catSize;

	for (int i = 0; i < taskCategoriesList[i].size(); i++)
	{
		saveContents += taskCategoriesList[i] + "\n";
	}

	saveFile.open("save_file");

	saveFile << saveContents;

	saveFile.close();
}



//Serves as the main menu for the program, displaying and leading to all the other features based on user input.
//Sends user to any of the menus availble based on input
void featureSelection()
{
	//If a task exists
	optionList currentFeatures1[] = { taskCategoryCreator, taskCategoryDeleter, taskCreation, taskDeletion, viewChoice, viewSettings, editTask, completeTask, ender };
	string optionNames1[] = { NEW_CAT, DELETE_CAT, NEW_TASK, DELETE_TASK, VIEW_TASK, VIEW_SETTINGS, EDIT_TASK, COMPLETE_TASK, EXIT };

	//If no tasks exist
	optionList currentFeatures2[] = { taskCategoryCreator, taskCategoryDeleter, taskCreation, ender };
	string optionNames2[] = { NEW_CAT, DELETE_CAT, NEW_TASK, EXIT };

	Menu mainMenu;

	if (taskList.size() == 0)
		mainMenu.syncOptions(currentFeatures2, optionNames2, sizeof(currentFeatures2) / sizeof(currentFeatures2[0]));
	else
		mainMenu.syncOptions(currentFeatures1, optionNames1, sizeof(currentFeatures1) / sizeof(currentFeatures1[0]));

	mainMenu.menuChoice();
}

//Overview: Create a new task based on player input and add its name into the totalTasks array.
//Sends user to either main menu or allow more tasks to be created based on user input
void taskCreation()
{
	char taskName[MAX_NAME_LENGTH], taskDate[MAX_DATE_LENGTH], taskTime[MAX_TIME_LENGTH], taskCategory[MAX_CATEGORY_LENGTH], details[MAX_DETAILS_LENGTH], priority[MAX_PRIORITY_LENGTH];
	int userOption = 0;

	cin.ignore(); //Removes newline character to allow getline to work

	//Collect information about the new task
	cout << "Enter the name for you task: ";
	cin.getline(taskName, MAX_NAME_LENGTH); //Allows for multiword input
	cout << endl;

	cout << "Enter the date for this task (in the form M/D/Y): ";
	cin.getline(taskDate, MAX_DATE_LENGTH);
	cout << endl;

	cout << "Enter the time for this task: ";
	cin.getline(taskTime, MAX_TIME_LENGTH);
	cout << endl;

	

	while (true) //Ensures entered task exists
	{
		bool fail = true;

		cout << "Enter the category for this task: ";
		cin.getline(taskCategory, MAX_CATEGORY_LENGTH);
		cout << endl;

		for (int i = 0; i < taskCategoriesList.size(); i++)
		{
			if (taskCategory == taskCategoriesList[i])
			{
				fail = false;
				break;
			}
		}

		if (fail)
		{
			cout << "Please enter the name of an existing category.\n";
		}
		else
		{
			break; //If input is valid, break from loop and continue
		}
	}

	while (true)
	{
		cout << "Enter the priority of the task (low, medium, high): ";
		cin.getline(priority, MAX_PRIORITY_LENGTH);
		string fixedPriority = priority;

		if (fixedPriority != "low" && fixedPriority != "medium" && fixedPriority != "high")
			cout << "Please enter \"low\", \"medium\", or \"high\"" << endl;
		else
			break;
	}
	cout << endl;

	cout << "Enter the details for this task: ";
	cin.getline(details, MAX_DETAILS_LENGTH);
	cout << endl;

	//Create a new task and add it to the list of tasks
	Task createdTask = Task(taskName, taskDate, taskTime, taskCategory, priority, details);
	taskList.push_back(createdTask);
	viewingList.push_back(createdTask);

	applySettings();

	cout << "Alright, a new task \"" << taskName << "\" has been created!\n\n";

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
	char taskName[MAX_NAME_LENGTH];

	int userOption = 0;

	cin.ignore();
	cout << "Enter the name of the task to delete: ";
	cin.getline(taskName, MAX_NAME_LENGTH); //Allows for multiword input
	cout << endl;

	//Find the task name in list of tasks and remove that element
	for (int i = 0; i < taskList.size(); i++)
	{
		if (taskList[i].name == taskName)
		{
			taskList.erase(taskList.begin() + i);
			applySettings();
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

//Overview: Print the current saved tasks of a certain date to the console, and send user to main menu
void taskView()
{
	string dateToView = "";
	bool wrong = true;

	do
	{
		cout << "Which date's tasks would you like to view (Format MM/DD/YYYY)? ";
		cin >> dateToView;
		int* dateArr = stringToDate(dateToView);
		int day = dateArr[1];
		int month = dateArr[0];
		int year = dateArr[2];

		for (int i = 0; i < taskList.size(); i++)
		{
			if (day == taskList[i].day && month == taskList[i].month && year == taskList[i].year)
			{
				Task currentTask = taskList[i];
				string stringOutput = currentTask.outputFormat();
				cout << stringOutput << endl;
				wrong = false;
			}
		}
		
		if (wrong)
			cout << "Please enter a date where a task exists.\n";
		else
			cout << endl;

	} while (wrong);

	featureSelection();
}

//Overview: Print all current saved tasks to the console, and send user to main menu
void taskViewAll()
{
	for (Task n : viewingList)
	{
		string stringOutput = n.outputFormat();
		cout << n.month << "/" << n.day << "/" << n.year << ":" << endl;
		cout << stringOutput << endl;
	}
	cout << endl;

	featureSelection();
}

//Overview: Menu that allows user to view all tasks or specific tasks
void viewChoice()
{
	optionList viewOptions[] = { taskView, taskViewAll };
	string optionNames[] = { VIEW_ONE, VIEW_ALL};

	Menu viewMenu;

	viewMenu.syncOptions(viewOptions, optionNames, sizeof(viewOptions) / sizeof(viewOptions[0]));
	viewMenu.menuChoice();
}

//Overview: Allows user to change the order in which tasks are displayed when viewing all settings and decide whether they want to view completed tasks or not
void viewSettings()
{
	int sorting;
	string completion;

	cout << "Current View Settings:" << endl;

	switch (static_cast<char>(settings[0]))
	{
	case '\0':
		cout << "Sorted by order added" << endl;
		break;
	case '\1':
		cout << "Sorted by date" << endl;
		break;
	case '\2':
		cout << "Sorted by priority" << endl;
		break;
	}

	switch (static_cast<char>(settings[1]))
	{
	case '\0':
		cout << "View all tasks" << endl;
		break;
	case '\1':
		cout << "View uncompleted tasks only" << endl;
		break;
	}
	cout << endl;

	viewingList = taskList;

	while (true)
	{
		cout << "Would you like to sort by (1) order added, (2) by date, or (3) by priority?: ";
		cin >> sorting;

		if (sorting == 1)
		{
			settings[0] = 0;
			break;
		}
		else if (sorting == 2)
		{
			sortByDate();
			settings[0] = 1;
			break;
		}
		else if (sorting == 3)
		{
			sortByPriority();
			settings[0] = 2;
			break;
		}
		else
		{
			cout << "Please enter either 1, 2, or 3." << endl;
		}
	}

	while (true)
	{
		cout << "Would you like to only view uncompleted tasks?(yes/no): ";
		cin >> completion;

		if (completion == "yes")
		{
			removeCompleted();
			settings[1] = 1;
			break;
		}
		else if (completion == "no")
		{
			settings[1] = 0;
			break;
		}
		else
		{
			cout << "Please enter either \"yes\" or \"no\"." << endl;
		}
	}
	cout << endl;

	featureSelection();
}

//Overview: Sorts tasks of the viewing list from highest to lowest priority
void sortByPriority()
{
	Task intermediary = Task("n", "0/0/0", "n", "n", "n", "n");

	for (int i = 0; i < viewingList.size(); i++)
	{
		for (int n = i + 1; n < viewingList.size(); n++)
		{
			if ((viewingList[i].priority == "low" && (viewingList[n].priority == "medium" || viewingList[n].priority == "high")) || (viewingList[i].priority == "medium" && viewingList[n].priority == "high"))
			{
				intermediary = viewingList[n];
				viewingList[n] = viewingList[i];
				viewingList[i] = intermediary;
			}
		}
	}
}

//Overview: Sorts tasks of the viewing list from earliest to latest date
void sortByDate()
{
	Task intermediary = Task("n", "0/0/0", "n", "n", "n", "n");

	for (int i = 0; i < viewingList.size(); i++)
	{
		for (int n = i + 1; n < viewingList.size(); n++)
		{
			if (viewingList[i].year > viewingList[n].year || (viewingList[i].year == viewingList[n].year && viewingList[i].month > viewingList[n].month) || (viewingList[i].year == viewingList[n].year && viewingList[i].month == viewingList[n].month && viewingList[i].day > viewingList[n].day))
			{
				intermediary = viewingList[n];
				viewingList[n] = viewingList[i];
				viewingList[i] = intermediary;
			}
		}
	}
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

	optionList currentFeatures[] = { taskCategoryCreator, featureSelection };
	string optionNames[] = { ANOTHER_CAT, MAIN_MENU };
	

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

	//Print all non empty task categories to console
	cout << "Here are your current task categories:\n";
	for (int i = 0; i < taskCategoriesList.size(); i++)
	{
		cout << taskCategoriesList[i] << endl;

	}
	cout << endl;

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

	optionList currentFeatures[] = { taskCategoryDeleter, featureSelection };
	string optionNames[] = { ANOTHER_DELETE_CAT, MAIN_MENU };

	Menu fromCatDelete;
	fromCatDelete.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCatDelete.menuChoice();
}

//Lets user choose which task to change and which aspect of that task to change
//Sends user to main menu or lets them edit another task
void editTask()
{
	char name[MAX_NAME_LENGTH], date[MAX_DATE_LENGTH], time[MAX_TIME_LENGTH], category[MAX_CATEGORY_LENGTH], details[MAX_DETAILS_LENGTH], choose[MAX_NAME_LENGTH], priority[MAX_PRIORITY_LENGTH];
	bool fail = true;
	int location, changeChoice;

	cout << "Tasks\n";
	for (int i = 0; i < taskList.size(); i++)
	{
		cout << taskList[i].name << endl;
	}

	while (true) //Ensures entered task exists
	{
		cout << endl << "Please select a task to edit: ";
		cin.ignore();
		cin.getline(choose, MAX_NAME_LENGTH);

		for (int i = 0; i < taskList.size(); i++)
		{
			if (choose == taskList[i].name)
			{
				location = i; //Saves the index of the matching task
				fail = false;
				break;
			}
		}

		if (fail)
		{
			cout << "Please enter the name of an existing task.";
		}
		else
		{
			break; //If input is valid, break from loop and continue
		}
	}
	
	//Displays aspects of chosen task
	cout << "Date: " << taskList[location].month << "/" << taskList[location].day << "/" << taskList[location].year << endl;
	cout << taskList[location].outputFormat() << endl;

	while (true) //Ensures user enters valid input
	{
		bool invalid;

		cout << "What aspect would you like to change?\n";
		cout << "1. Name\n2. Date\n3. Time\n4. Category\n5. Priority\n6. Details\n\nEnter here: ";
		cin >> changeChoice;
		invalid = cin.fail(); //Returns true if the wrong data type is entered

		if (invalid)
		{
			cout << "Please enter the number corresponding with one of the choices.";

			//Prevents eternal looping after cin.fail
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (changeChoice > 6 || changeChoice < 1 || changeChoice != floor(changeChoice)) //Makes sure the number is between 1 and 5
		{
			cout << "Please enter the number corresponding with one of the choices.";
		}
		else
		{
			break; //If input is valid, break from loop and continue
		}
	}

	cin.ignore();

	//Edits corresponding aspect of task
	if (changeChoice == 1)
	{
		cout << "Enter the name for you task: ";
		cin.getline(name, MAX_NAME_LENGTH);
		cout << endl;

		taskList[location].editName(name);
	}
	else if (changeChoice == 2)
	{
		cout << "Enter the date for this task (in the form M/D/Y): ";
		cin.getline(date, MAX_DATE_LENGTH);

		taskList[location].editDate(date);
	}
	else if (changeChoice == 3)
	{
		cout << "Enter the time for this task: ";
		cin.getline(time, MAX_TIME_LENGTH);
		cout << endl;

		taskList[location].editTime(time);
	}
	else if (changeChoice == 4)
	{
		cout << "Enter the category for this task: ";
		cin.getline(category, MAX_CATEGORY_LENGTH);
		cout << endl;

		taskList[location].editCategory(category);
	}
	else if (changeChoice == 5)
	{
		cout << "Enter the priority for this task: ";
		cin.getline(priority, MAX_PRIORITY_LENGTH);
		cout << endl;

		taskList[location].editPriority(priority);
	}
	else if (changeChoice == 6)
	{
		cout << "Enter the details for this task: ";
		cin.getline(details, MAX_DETAILS_LENGTH);
		cout << endl;

		taskList[location].editDetails(details);
	}

	applySettings();

	cout << "Alright, the task has been changed!\n\n";

	optionList currentFeatures[] = { editTask, featureSelection };
	string optionNames[] = { EDIT_ANOTHER, MAIN_MENU };

	Menu fromEditTask;
	fromEditTask.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromEditTask.menuChoice();
}

//Overview: Allows the user to mark a task as complete
void completeTask()
{
	char taskName[MAX_NAME_LENGTH];
	bool match = false;

	for (Task n : taskList)
	{
		if (n.completion == "false")
			cout << n.outputFormat() << endl;
	}
	cout << endl;

	cin.ignore();
	do
	{
		cout << "Enter the name of the task you completed: ";
		cin.getline(taskName, MAX_NAME_LENGTH);

		string stringName = taskName;
		for (Task& n : taskList)
		{
			if (stringName == n.name)
			{
				n.completeTask();
				match = true;
			}
		}

		for (Task& n : viewingList)
		{
			if (stringName == n.name)
			{
				n.completeTask();

				applySettings();
			}
		}

		if (!match)
			cout << "Please enter the name of an existing task." << endl;

	} while (!match);
	cout << endl;

	optionList currentFeatures[] = { completeTask, featureSelection };
	string optionNames[] = { COMPLETE_ANOTHER_TASK, MAIN_MENU };

	Menu fromCompleteTask;
	fromCompleteTask.syncOptions(currentFeatures, optionNames, sizeof(currentFeatures) / sizeof(currentFeatures[0]));

	fromCompleteTask.menuChoice();
}

//Overview: Removes tasks from the viewing list if they are marked as completed
void removeCompleted()
{
	for (int i = 0; i < viewingList.size(); i++)
	{
		if (viewingList[i].completion == "true")
			viewingList.erase(viewingList.begin() + i);
	}
}

//Reapplies settings decided in the viewSettings function
void applySettings()
{
	viewingList = taskList;

	if (settings[0] == 1)
		sortByDate();
	else if (settings[0] == 2)
		sortByPriority();

	if (settings[1])
		removeCompleted();
}

//dateString must be in the format MM/DD/YYYY, the returned array will be in the format {MM, DD, YYYY}
int* stringToDate (string dateString)
{
	int day;
	int month;
	int year;

	//Iterate through the string, and collect the dates
	int count = 0;
	for(int i = 0; i < dateString.length(); i++)
	{
		if(dateString[i] == '/')
		{
			if(count == 0)
			{
				month = stoi(dateString.substr(0,i));
				count = i + 1;
			} else if(count > 0)
			{
				day = stoi(dateString.substr(count, i - count));
				year = stoi(dateString.substr(i + 1));
			}
		}
	}

	int* dateArray = new int[3];
	dateArray[0] = month;
	dateArray[1] = day;
	dateArray[2] = year;

	return dateArray;
}

//Function that ends program and fits into the optionList array
void ender()
{
	cout << "";
}