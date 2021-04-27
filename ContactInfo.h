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
		ContactInfo(char gName[], int numContactInfos, bool isSpecial, char
			  		specialInfo[], bool optInPromos);
		ContactInfo(const ContactInfo &aPerson);
		~ContactInfo();

		ContactInfo& operator= (const ContactInfo &aPerson);

		const char * getContactInfoName() const;
		int getNumPeople() const;
		bool getSpecialSeating() const;
		const char * getSpecialSeatingInfo() const;
		bool getOptInPromos() const;

		friend ostream& operator<< (ostream & out, const ContactInfo & aPerson);

	private:
		char * fullName;
		char * email;

		void init(const char * gName, int num, bool isSpecial, const char *
				  specialSeatInfo, bool isOptPromos);
};

#endif
