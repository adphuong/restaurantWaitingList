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
		ContactInfo(char gName[], int numContactInfos, boolean isSpecial, char
			  		specialInfo[], boolean optInPromos);
		ContactInfo(const ContactInfo &aPerson);
		~ContactInfo();

		ContactInfo& operator= (const ContactInfo &aPerson);

		const char * getContactInfoName() const;
		int getNumPeople() const;
		boolean getSpecialSeating() const;
		const char * getSpecialSeatingInfo() const;
		boolean getOptInPromos() const;

		friend ostream& operator<< (ostream & out, const ContactInfo & aPerson);

	private:
		char * fullName;
		char * email;

		void init(const char * gName, int num, boolean isSpecial, const char *
				  specialSeatInfo, boolean isOptPromos);
};

#endif
