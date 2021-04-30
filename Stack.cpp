#include "Stack.h"


Stack::Stack() : persons(nullptr), size(0) {}


Stack::Stack(int initSize) {
	size = initSize;

	persons = new ContactInfo[size];
}


