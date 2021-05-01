#ifndef CONTACTINFO_H
#define CONTACTINFO_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cctype>


using namespace std;

class ContactInfo {
	public:
		ContactInfo();
		ContactInfo(char nameToInit[], char emailToInit[]);
		ContactInfo(const ContactInfo & aPerson);
		~ContactInfo();

		ContactInfo& operator= (const ContactInfo & aPerson);

		const char * getFullName() const;
		const char * getEmail() const;

		void setFullName(char * name);
		void setEmail(char * email);

		friend ostream& operator<< (ostream & out, const ContactInfo & aPerson);

	private:
		char * fullName;
		char * email;

		void init(const char * nameToInit, const char * emailToInit);

};

#endif
