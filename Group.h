/********************************************************************
 *	File:			Group.cpp
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This includes all the implementations for the 
 *					Group ADT:
 *					- Default constructor & Copy Constructor
 *					- Constructor that takes params
 *					- Destructor
 *					- Getters: getPosition(), getNumPeople(), getOptedIn()
 *						getSpecialSeating(), getSpecialSeatingInfo()
 *					- Setter: setPosition()
 *					- Overloaded (=) and (<<) operators
 *					- Private member functions:
 *						- init()
 *******************************************************************/

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
		Group(int pos, char gName[], int numPersons, bool isSpecial, char specialInfo[], 
			  bool optInPromos);
		Group(const Group & aGroup);
		~Group();

		Group& operator= (const Group &toBeCopied);
		
		int getPosition() const;
		const char * getGroupName() const;
		int getNumPeople() const;
		bool getSpecialSeating() const;
		const char * getSpecialSeatingInfo() const;
		bool getOptedIn() const;

		void setPosition(int pos);

		friend ostream& operator<< (ostream & out, const Group & aGroup);

	private:
		int position;
		char * groupName;
		int numPeople;
		bool isSpecialSeating;
		char * specialSeatingInfo;
		bool isOptInPromos;

		void init(int pos, const char * gName, int num, bool isSpecial, 
				  const char * specialSeatInfo, bool isOptPromos);
};


#endif
