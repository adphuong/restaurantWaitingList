#include "Group.h"

Group::Group() : groupName(nullptr), numPeople(0), isSpecialSeating(false),
				 specialSeatingInfo(nullptr), isOptInPromos(false) {}

Group::Group(char gName[], int numPersons, bool isSpecial, char specialInfo[], 
			 bool optInPromos) {
	init(gName, numPersons, isSpecial, specialInfo, optInPromos);
}


Group::Group(const Group & aGroup) {
	init(aGroup.groupName, aGroup.numPeople, aGroup.isSpecialSeating,
		 aGroup.specialSeatingInfo, aGroup.isOptInPromos);
}

Group::~Group() {
	if (groupName != nullptr || specialSeatingInfo != nullptr) {
		delete [] groupName;
		delete [] specialSeatingInfo;
	}
}

void Group::init(const char * gName, int num, bool isSpecial, const char *
				 specialSeatInfo, bool isOptPromos) {
	groupName = new char[strlen(gName) + 1];
	strcpy(groupName, gName);

	numPeople = num;

	isSpecialSeating = isSpecial;

	specialSeatingInfo = new char[strlen(specialSeatInfo) + 1];
	strcpy(specialSeatingInfo, specialSeatInfo);

	isOptInPromos = isOptPromos;
}

// For testing purposes
ostream& operator<< (ostream& out, const Group& aGroup) {
	out << "Group name: " << aGroup.groupName << endl
		<< "Num People: " << aGroup.numPeople << endl
		<< "Special Seating? " << aGroup.isSpecialSeating << endl
		<< "Special Seating Info: " << aGroup.specialSeatingInfo << endl
		<< "Opt in for promos? " << aGroup.isOptInPromos 
		<< endl;

	return out;
}

