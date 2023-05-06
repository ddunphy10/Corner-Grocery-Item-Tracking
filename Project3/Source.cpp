#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return presult ? _PyLong_AsInt(presult) : -1;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//Displays menu with choices for the user and handles those choices accordingly.
void DisplayMenu()
{
	char userChoice;
	do
	{
		cout << endl;
		cout << "CORNER GROCER ITEM TRACKING" << endl;
		cout << endl;
		cout << "1. Produce a list of all items purchased in a given day along with the number of times each item was purchased." << endl;
		cout << "2. Produce a number representing how many times a specific item was purchased in a given day." << endl;
		cout << "3. Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased." << endl;
		cout << "4. Exit program." << endl;
		cout << endl;
		cout << "Please select option 1, 2, 3, or 4" << endl;
		cin >> userChoice;
		cout << endl;

		if (userChoice == '1')
		{
			cout << "A list of each item purchased and quantity:" << endl;
			cout << endl;
			callIntFunc("itemAndQuantity", "TextFile.txt");
			cout << endl;
		}
		else if (userChoice == '2')
		{
			string item;
			cout << "Please enter the item with the first letter as uppercase:" << endl;
			cin >> item;
			cout << endl;
			cout << item << " " << "was purchased " << callIntFunc("singleItemQuantity", item) << " times.";
			cout << endl;
		}
		else if (userChoice == '3')
		{
			ifstream myFile;
			string itemName;
			int itemQuantity;

			cout << "TEXT-BASED HISTOGRAM" << endl;
			cout << endl;
			callIntFunc("textHistogram", "frequency.dat");
			myFile.open("frequency.dat");
			if (!myFile.is_open())
				cout << "Coult not open file frequency.dat" << endl;

			while (!myFile.eof())
			{
				myFile >> itemName;
				myFile >> itemQuantity;
				cout << itemName << " ";
				for (int i = 0; i < itemQuantity; ++i)
				{
					cout << '*';
				}
				cout << endl;
			}
		}
		else if (userChoice == '4')
		{
			cout << "GoodBye!" << endl;
			cout << endl;
		}
		else
		{
			cout << "That is not a valid input please try again." << endl;
			cout << endl;
		}
	} while (userChoice != '4');
}

void main()
{
	DisplayMenu();
}