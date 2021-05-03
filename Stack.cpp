/********************************************************************
 *	File:			Stack.cpp
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This includes all the implementations for the 
 *					Stack ADT:
 *					- Default constructor & Copy Constructor
 *					- Destructor
 *					- Getter: getSize()
 *					- Overloaded (=) and (<<) operators
 *					- Stack operations:
 *						- push(), pop(), peek()
 *					- Private member functions:
 *						- destroy(), copy(), display(), saveToFile()
 *******************************************************************/

#include "Stack.h"

/*************************** Stack() *******************************
 *	Default constructor
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
Stack::Stack() : stackOfContacts(nullptr), size(0) {}


/*************************** Stack() *******************************
 *	Constructor that takes in one param (size)
 *
 *	@params - int size to initialize array
 *	@returns - none
 *******************************************************************/
Stack::Stack(int initSize) {
	size = initSize;

	stackOfContacts = new ContactInfo * [size];
}


/*************************** ~Stack() *******************************
 *	Destructor
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
Stack::~Stack() {
	destroy();
}


/*************************** destroy() *****************************
 *	Helper function for destructor to release memory
 *
 *	@params - pointer of node we want to destroy
 *	@returns - none
 *******************************************************************/
void Stack::destroy() {
	for (int i = 0; i < size; i++) {
		delete stackOfContacts[size];
	}

	delete [] stackOfContacts;
}


/*************************** getSize() *****************************
 *	Gets the size of the array/stack
 *
 *	@params - none
 *	@returns - size of array
 *******************************************************************/
int Stack::getSize() const {
	return size;
}


/*************************** push() *********************************
 *	Adds new ContactInfo object to the top of the stack
 *
 *	@params - address of a person's contact info to add to stack
 *	@returns - true if added successfully, false otherwise
 *******************************************************************/
bool Stack::push(const ContactInfo & aPerson) {
	 stackOfContacts[size] = new ContactInfo(aPerson);
	 size++;

	 return true;
}


/*************************** pop() **********************************
 *	Removes a person's contact info from the top of the stack
 *
 *	@params - none
 *	@returns - true if removed successfully, false otherwise
 *******************************************************************/
bool Stack::pop() {
	char tempName[TMP_CAP];
	char tempEmail[TMP_CAP];

	if (size == 0) {
		return false;
	}

	// Gets last data info from array and stores in temp variables
	strcpy(tempName, stackOfContacts[size - 1]->getFullName());
	strcpy(tempEmail, stackOfContacts[size - 1]->getEmail());

	// Create new ContactInfo object with temp variables and save it to file
	ContactInfo tempContact(tempName, tempEmail);
	saveToFile(tempContact);

	cout << "Successfully sent promo materials to: " 
		 << endl << endl
		 << tempContact << endl;

	// Reset array index we just popped off and dec. size
	stackOfContacts[size - 1]->setFullName(nullptr);
	stackOfContacts[size - 1]->setEmail(nullptr);
	size--; 

	return true;
}


/*************************** peek() *********************************
 *	Retrieves the contact info that is at the top of the stack
 *
 *	@params - none
 *	@returns - true if retrieved successfully, false otherwise
 *******************************************************************/
bool Stack::peek() const {
	char tempName[TMP_CAP];
	char tempEmail[TMP_CAP];
	
	if (size == 0) {
		return false;
	}

	// Gets last data info from array and stores in temp variables
	strcpy(tempName, stackOfContacts[size - 1]->getFullName());
	strcpy(tempEmail, stackOfContacts[size - 1]->getEmail());

	// Create new ContactInfo object with temp variables and save it to file
	ContactInfo topContact(tempName, tempEmail);

	cout << "Contact at the top of the stack: " << endl << endl
		 << topContact
		 << endl;
	
	return true;
}


/*************************** display() ******************************
 *	Displays the stack of contact info list
 *
 *	@params - address of the ostream to print
 *	@returns - none
 *******************************************************************/
void Stack::display(ostream & out) const {
	if (size != 0) {
		cout << "Promotional opt-ins list of contacts:" << endl << endl;

		cout << setfill('-') << setw(100) << "-" << endl;
		
		cout << setfill(' ') <<setw(20) << left << "FULL NAME"
			 << setw(12) << left << "EMAIL ADDRESS"
			 << endl;
	
		cout << setfill('-') << setw(100) << "-" << endl;	
		
		for (int i = size - 1; i >= 0; i--) {
			out << setfill(' ') <<setw(20) << stackOfContacts[i]->getFullName()
				<< setw(12) << left << stackOfContacts[i]->getEmail()
				<< endl;
		}
	}
	else {
		cout << "There are currently no contacts in the promotional opt-in list." 
			 << endl;
	}

}


/*********************** Overloaded << operator *********************
 *	Overloading << operator so client can print Stack object.
 *	
 *	@params - address of ostream and stack we want to print
 *	@returns - ostream we want to print
 *******************************************************************/
ostream& operator<< (ostream & out, const Stack & aStack) {
	aStack.display(out);

	return out;
}


/*************************** saveToFile() ***************************
 *	When contact info is popped off the stack, it will be saved
 *  to a text file 
 *	
 *	@params - address of a contact's info we want to save
 *	@returns - none
 *******************************************************************/
void Stack::saveToFile(ContactInfo & aContact) {
	ofstream out;
	char filename[] = "StackContacts.txt";
	
	out.open(filename, fstream::app);

		if (!out) {
		cerr << "Failed to open " << filename << " for writing!" << endl;
		exit(1);
	}

	out << aContact.getFullName() << ","
		<< aContact.getEmail() << endl;
	
	out.close();
}



