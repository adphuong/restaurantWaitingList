#include "Stack.h"


Stack::Stack() : stackOfContacts(nullptr), size(0) {}


Stack::Stack(int initSize) {
	size = initSize;

	stackOfContacts = new ContactInfo * [size];

}


Stack::~Stack() {
	destroy();
}


void Stack::destroy() {
	for (int i = 0; i < size; i++) {
		delete stackOfContacts[size];
	}

	delete [] stackOfContacts;
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

	if (size == 0) {
		return false;
	}
	/*
	if (!stackOfContacts) {
		return false;	
	
	}
	*/

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



ostream& operator<< (ostream & out, const Stack & aStack) {
	aStack.display(out);

	return out;
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



