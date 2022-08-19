#include "Group.h"

Group::Group() : position(0), groupName(nullptr), numPeople(0), isSpecialSeating(false),
				 specialSeatingInfo(nullptr), isOptInPromos(false) {}

Group::Group(int pos, char gName[], int numPersons, bool isSpecial, char specialInfo[], 
			 bool optInPromos) {
	init(pos, gName, numPersons, isSpecial, specialInfo, optInPromos);
}


Group::Group(const Group & aGroup) {
	init(aGroup.position, aGroup.groupName, aGroup.numPeople, aGroup.isSpecialSeating,
		 aGroup.specialSeatingInfo, aGroup.isOptInPromos);
}

Group::~Group() {
	if (groupName != nullptr || specialSeatingInfo != nullptr) {
		delete [] groupName;
		delete [] specialSeatingInfo;
	}
}

void Group::init(int pos, const char * gName, int num, bool isSpecial, 
				 const char * specialSeatInfo, bool isOptPromos) {
	position = pos;

	groupName = new char[strlen(gName) + 1];
	strcpy(groupName, gName);

	numPeople = num;

	isSpecialSeating = isSpecial;

	specialSeatingInfo = new char[strlen(specialSeatInfo) + 1];
	strcpy(specialSeatingInfo, specialSeatInfo);

	isOptInPromos = isOptPromos;
}


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
		 toBeCopied.isSpecialSeating, toBeCopied.specialSeatingInfo, toBeCopied.isOptInPromos);
	
	return *this;
}

int Group::getPosition() const {
	return position;
}

const char * Group::getGroupName() const {
	return groupName;
}

int Group::getNumPeople() const {
	return numPeople;
}

bool Group::getSpecialSeating() const {
	return isSpecialSeating;
}

const char * Group::getSpecialSeatingInfo() const {
	return specialSeatingInfo;
}

bool Group::getOptedIn() const {
	return isOptInPromos;
}


void Group::setPosition(int pos) {
	position = pos;
}


// For testing purposes, need to edit printing layout
ostream& operator<< (ostream& out, const Group& aGroup) {
	char specialSeating;
	char optIn;

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

