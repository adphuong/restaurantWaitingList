#include "main.h"

int MAX = 101;
int main() {
	
	char fullName[MAX] = "April Phuong";
	char email[MAX] = "aprilphuong@gmail.com";
	
	
	ContactInfo aPerson(fullName, email);
	cout << "aPerson Info: " << endl << aPerson << endl;

	ContactInfo anotherPerson(aPerson);
	cout << "anotherPerson: " << endl << anotherPerson << endl;

	char sarahName[] = "Sarah Tinder";
	char newEmail[] = "sarahismycrush@gmail.com";

	ContactInfo sarah(sarahName, newEmail);

	cout << "Sarah's Info: " << endl << sarah << endl;

	aPerson = sarah;

	cout << "aPerson changed: " << endl << aPerson << endl;
	cout << endl;

	cout << aPerson.getFullName() << endl
		 << aPerson.getEmail() << endl;


	/*	TESTING FOR GROUP CLASS
	char name[] = "Test Name";
	int num = 5;
	bool isSpecial = true;
	char info[] = "Test Info";

	bool promos = true;

	Group aGroup(name, num, isSpecial, info, promos);

	cout << "A Group: " << endl
		 << aGroup << endl;

	Group anotherGroup(aGroup);

	cout << "Another Group: " << endl
		 << anotherGroup<< endl;

	Group thirdGroup;

	thirdGroup = aGroup;

	cout << "Third Group: " << endl
		 << thirdGroup << endl;

	cout << thirdGroup.getGroupName() << endl
		<< thirdGroup.getNumPeople() << endl
		<< thirdGroup.getSpecialSeating() << endl
		<< thirdGroup.getSpecialSeatingInfo() << endl
		<< thirdGroup.getOptInPromos() << endl;

	*/

	return 0;
}
