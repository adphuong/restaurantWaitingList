/********************************************************************
 *	File:			Group.h
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This is the header file for Group ADT
 *******************************************************************/

#include "Group.h"


/******************************* Group() ****************************
 *	Default constructor
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
Group::Group() : position(0), groupName(nullptr), numPeople(0), 
				 isSpecialSeating(false), specialSeatingInfo(nullptr), 
				 isOptInPromos(false) {}


/******************************* Group() ****************************
 *	Constructor that takes params
 *
 *	@params - pos, gName, numPersons, isSpecial, specialInfo
 *	@returns - none
 *******************************************************************/
Group::Group(int pos, char gName[], int numPersons, bool isSpecial, 
			 char specialInfo[], bool optInPromos) {
	init(pos, gName, numPersons, isSpecial, specialInfo, optInPromos);
}


/******************************* Group() ****************************
 *	Copy Constructor
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
Group::Group(const Group & aGroup) {
	init(aGroup.position, aGroup.groupName, aGroup.numPeople,
		 aGroup.isSpecialSeating, aGroup.specialSeatingInfo, 
		 aGroup.isOptInPromos);
}


/******************************* ~Group() ***************************
 *	Destructor	
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
Group::~Group() {
	if (groupName != nullptr || specialSeatingInfo != nullptr) {
		delete [] groupName;
		delete [] specialSeatingInfo;
	}
}


/***************************** init() ******************************
 *  Helper function to initialize private data members of Group.
 *
 *	@params - pos, gName, num, isSpecial, specialSeatInfo, isOptPromo 
 *	@returns - none
 *******************************************************************/
void Group::init(int pos, const char * gName, int num, bool isSpecial, 
				 const char * newSpecialSeatInfo, bool isOptPromos) {
	position = pos;

	groupName = new char[strlen(gName) + 1];
	strcpy(groupName, gName);

	numPeople = num;

	isSpecialSeating = isSpecial;

	specialSeatingInfo = new char[strlen(newSpecialSeatInfo) + 1];
	strcpy(specialSeatingInfo, newSpecialSeatInfo);

	isOptInPromos = isOptPromos;
}


/************************** Overloaded (=) *************************
 *  Allows client to use the assignment operator on Group object
 *
 *	@params - address of Group object we want to assign with
 *	@returns - address of Group object with new copied data
 *******************************************************************/
Group &Group::operator=(const Group &toBeCopied) {
	if (this == &toBeCopied) {
		return *this;
	}

	if (this->groupName) {
		delete [] this->groupName;
	}

	if (this->specialSeatingInfo) {
		delete [] this->specialSeatingInfo;
	}

	init(toBeCopied.position, toBeCopied.groupName, toBeCopied.numPeople, 
		 toBeCopied.isSpecialSeating, toBeCopied.specialSeatingInfo, 
		 toBeCopied.isOptInPromos);
	
	return *this;
}


/************************** getPosition() ***************************
 *  Gets the position private data member
 *
 *	@params - none 
 *	@returns - position 
 *******************************************************************/
int Group::getPosition() const {
	return position;
}


/************************** getGroupName() ***************************
 *  Gets the groupName private data member
 *
 *	@params - none 
 *	@returns - groupName 
 *******************************************************************/
const char * Group::getGroupName() const {
	return groupName;
}


/************************** getNumPeople() ***************************
 *  Gets the numPeople private data member
 *
 *	@params - none 
 *	@returns - numPeople
 *******************************************************************/
int Group::getNumPeople() const {
	return numPeople;
}


/************************** getSpecialSeating() *********************
 *  Gets the isSpecialSeating private data member
 *
 *	@params - none 
 *	@returns - isSpecialSeating 
 *******************************************************************/
bool Group::getSpecialSeating() const {
	return isSpecialSeating;
}


/********************** getSpecialSeatingInfo() **********************
 *  Gets the specialSeatingInfo private data member
 *
 *	@params - none 
 *	@returns - specialSeatingInfo 
 *******************************************************************/
const char * Group::getSpecialSeatingInfo() const {
	return specialSeatingInfo;
}


/************************** getOptedIn() ***************************
 *  Gets the getOptedIn private data member
 *
 *	@params - none 
 *	@returns - getOptedIn 
 *******************************************************************/
bool Group::getOptedIn() const {
	return isOptInPromos;
}


/************************** setPosition() ***************************
 *  Sets the position private data member
 *
 *	@params - none 
 *	@returns - groupName 
 *******************************************************************/
void Group::setPosition(int pos) {
	position = pos;
}


/*********************** Overloaded << operator *********************
 *	Overloading << operator so client can print Group object.
 *	
 *	@params - address of ostream and Group we want to print out
 *	@returns - ostream we want to print
 *******************************************************************/
ostream& operator<< (ostream& out, const Group& aGroup) {
	char specialSeating;
	char optIn;

	// Prints 'Y' when true, 'N' when false. User friendly language
	if (aGroup.isSpecialSeating) {
		specialSeating = 'Y'; 	
	}
	else {
		specialSeating = 'N';
	}

	if (aGroup.isOptInPromos) {
		optIn = 'Y';
	}
	else {
		optIn = 'N';
	}
	
	if (aGroup.position) {
		out << left << setfill(' ') << setw(8) << aGroup.position
			<< left << setw(20) << aGroup.groupName
			<< setw(12) << left << aGroup.numPeople 
		 	<< setw(15) << left << specialSeating
		 	<< setw(30) << left << aGroup.specialSeatingInfo
		 	<< setw(20) << left << optIn; 
	}
	return out;
}

