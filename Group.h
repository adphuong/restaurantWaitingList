#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;

class Group {
	public:
		Group();
		Group(char gName[], int numPersons, boolean isSpecial, char
			  specialInfo[], boolean optInPromos);
		Group(const Group &aGroup);
		~Group();

		Group& operator= (const Group &aGroup);

		const char * getGroupName() const;
		int getNumPeople() const;
		boolean getSpecialSeating() const;
		const char * getSpecialSeatingInfo() const;
		boolean getOptInPromos() const;

		friend ostream& operator<< (ostream & out, const Group & aGroup);

	private:
		char * groupName;
		int numPeople;
		boolean isSpecialSeating;
		char * specialSeatingInfo;
		boolean isOptInPromos;

		void init(const char * gName, int num, boolean isSpecial, const char *
				  specialSeatInfo, boolean isOptPromos);
};

#endif
