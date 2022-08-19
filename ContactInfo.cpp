/********************************************************************
 *	File:			ContactInfo.cpp
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This includes all the implementations for the 
 *					ContactInfo ADT:
 *					- Default constructor & Copy Constructor
 *					- Destructor
 *					- Constructor that takes name and email params
 *					- Getters: getFullName() and getEmail()
 *					- Setters: setFullName() and setEmail()
 *					- Overloaded (=) and (<<) operators
 *					- Private member functions:
 *						- init()
 *******************************************************************/

#include "ContactInfo.h"


/************************* ContactInfo() ****************************
 *	Default constructor
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
ContactInfo::ContactInfo() : fullName(nullptr), email(nullptr) {}


/************************* ContactInfo() ****************************
 *  Constructor that takes params and initializes fullName and email	
 *
 *	@params - nameToInit and emailToInit, both cstrings
 *	@returns - none
 *******************************************************************/
ContactInfo::ContactInfo(char nameToInit[], char emailToInit[]) {
	init(nameToInit, emailToInit);	
}


/************************* ContactInfo() ****************************
 *  Copy constructor
 *
 *	@params - address of contact info we want to copy from
 *	@returns - none
 *******************************************************************/
ContactInfo::ContactInfo(const ContactInfo & aPerson) {
	init(aPerson.fullName, aPerson.email);
}


/***************************** init() ******************************
 *  Helper function to initialize fullName and email private data
 *	members.
 *
 *	@params - nameToInit and emailToInit, both char pointers
 *	@returns - none
 *******************************************************************/
void ContactInfo::init(const char * nameToInit, const char * emailToInit) {
	fullName = new char[strlen(nameToInit) + 1];
	strcpy(fullName, nameToInit);

	email = new char[strlen(emailToInit) + 1];
	strcpy(email, emailToInit);
}


/************************** ~ContactInfo() **************************
 *  Destructor
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
ContactInfo::~ContactInfo() {
	if (fullName) {
		delete [] fullName;
	}

	if (email) {
		delete [] email;
	}
}


/************************** Overloaded (=) *************************
 *  Allows client to use the assignment operator on ContactInfo object
 *
 *	@params - address of ContactInfo object we want to assign with
 *	@returns - address of ContactInfo object with new copied data
 *******************************************************************/
ContactInfo &ContactInfo::operator=(const ContactInfo &toBeCopied) {
	if (this == &toBeCopied) {
		return *this;
	}

	if (this->fullName) {
		delete [] this->fullName;
	}

	if (this->email) {
		delete [] this->email;
	}

	init(toBeCopied.fullName, toBeCopied.email);
	
	return *this;
}


/************************** getFullName() **************************
 *  Gets fullName private data member
 *
 *	@params - none
 *	@returns - fullName
 *******************************************************************/
const char * ContactInfo::getFullName() const {
	return fullName;
}


/************************** getFullName() **************************
 *  Gets email private data member
 *
 *	@params - none
 *	@returns - email
 *******************************************************************/
const char * ContactInfo::getEmail() const {
	return email;
}


/************************** setFullName() **************************
 *  Sets fullName private data member
 *
 *	@params - pointer to name we want to set fullName to
 *	@returns - none
 *******************************************************************/
void ContactInfo::setFullName(char * name) {
	this->fullName = name;
}


/************************** setEmail() ******************************
 *  Sets email private data member
 *
 *	@params - pointer to email we want to set email to
 *	@returns - none
 *******************************************************************/
void ContactInfo::setEmail(char * email) {
	this->email = email;
}


/*********************** Overloaded << operator *********************
 *	Overloading << operator so client can print Queue object.
 *	
 *	@params - address of ostream and ContactInfo we want to print out
 *	@returns - ostream we want to print
 *******************************************************************/
ostream& operator<< (ostream& out, const ContactInfo & aPerson) {
	out << "Full name: " << aPerson.fullName << endl
		<< "Email: " <<  aPerson.email << endl
		<< endl;

	return out;
}

