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
		Group(char gName[], int numPersons, bool isSpecial, char specialInfo[], 
			 bool optInPromos);
		Group(const Group & aGroup);
		~Group();

		Group& operator= (const Group &toBeCopied);

		const char * getGroupName() const;
		int getNumPeople() const;
		bool getSpecialSeating() const;
		const char * getSpecialSeatingInfo() const;
		bool getOptInPromos() const;

		friend ostream& operator<< (ostream & out, const Group & aGroup);

	private:
		char * groupName;
		int numPeople;
		bool isSpecialSeating;
		char * specialSeatingInfo;
		bool isOptInPromos;

		void init(const char * gName, int num, bool isSpecial, 
				  const char * specialSeatInfo, bool isOptPromos);
};


#endif
