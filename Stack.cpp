#include "Stack.h"


Stack::Stack() : stackOfContacts(nullptr), size(0) {}


Stack::Stack(int initSize) {
	size = initSize;

	stackOfContacts = new ContactInfo * [size];

	for (int i = 0; i < size; i++) {
		stackOfContacts[i] = nullptr;
	}
}


int Stack::getSize() const {
	return size;
}


bool Stack::push(const ContactInfo & aPerson) {
	 stackOfContacts[size] = new ContactInfo(aPerson);

	 size++;

	 return true;
}

bool Stack::pop() {
	char tempName[TMP_CAP];
	char tempEmail[TMP_CAP];

	if (!stackOfContacts) {
		return false;	
	}

	// Gets last data info from array and stores in temp variables
	strcpy(tempName, stackOfContacts[size - 1]->getFullName());
	strcpy(tempEmail, stackOfContacts[size - 1]->getEmail());

	// Create new ContactInfo object with temp variables and save it to file
	ContactInfo tempContact(tempName, tempEmail);
	saveToFile(tempContact);

	cout << "Successfully sent promo materials to " 
		 << endl << endl
		 << tempContact << endl;

	// Reset array index we just popped off and dec. size
	stackOfContacts[size - 1]->setFullName(nullptr);
	stackOfContacts[size - 1]->setEmail(nullptr);
	size--; 

	return true;
}


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
