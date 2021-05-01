#include "Stack.h"


Stack::Stack() : stackOfContacts(nullptr), size(0) {}


Stack::Stack(int initSize) {
	size = initSize;

	stackOfContacts = new ContactInfo * [size];
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
	char tempName[20];
	char tempEmail[20];

	if (!stackOfContacts) {
		cout << "Looks like there are no contacts in this list right now"
			 << endl;
	}

	strcpy(tempName, stackOfContacts[size - 1]->getFullName());
	strcpy(tempEmail, stackOfContacts[size - 1]->getEmail());

	ContactInfo tempContact(tempName, tempEmail);
	saveToFile(tempContact);

	stackOfContacts[size - 1]->setFullName(nullptr);
	stackOfContacts[size - 1]->setEmail(nullptr);

	return true;
}


void Stack::saveToFile(ContactInfo & aContact) {
	ofstream out;
	char filename[] = "StackContacts.txt";
	out.open(filename);

	if (!out) {
		cerr << "Failed to open " << filename << " for writing!" << endl;
		exit(1);
	}	

	out << aContact.getFullName() << ","
		<< aContact.getEmail() << "," << endl;

	out.close();
}
