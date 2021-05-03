#include "ContactInfo.h"

ContactInfo::ContactInfo() : fullName(nullptr), email(nullptr) {}


ContactInfo::ContactInfo(char nameToInit[], char emailToInit[]) {
	init(nameToInit, emailToInit);	
}


ContactInfo::ContactInfo(const ContactInfo & aPerson) {
	init(aPerson.fullName, aPerson.email);
}


void ContactInfo::init(const char * nameToInit, const char * emailToInit) {
	fullName = new char[strlen(nameToInit) + 1];
	strcpy(fullName, nameToInit);

	email = new char[strlen(emailToInit) + 1];
	strcpy(email, emailToInit);
}

ContactInfo::~ContactInfo() {
	if (fullName || email) {
		delete [] fullName;
		delete [] email;
	}
}


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


const char * ContactInfo::getFullName() const {
	return fullName;
}


const char * ContactInfo::getEmail() const {
	return email;
}


void ContactInfo::setFullName(char * name) {
	this->fullName = name;
}


void ContactInfo::setEmail(char * email) {
	this->email = email;
}


ostream& operator<< (ostream& out, const ContactInfo & aPerson) {
	out << "Full name: " << aPerson.fullName << endl
		<< "Email: " <<  aPerson.email << endl
		<< endl;

	return out;
}

