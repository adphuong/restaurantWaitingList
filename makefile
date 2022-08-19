CPP = g++
CPPFLAGS = -Wall -g -std=c++11 

main: main.o Group.o ContactInfo.o Queue.o Stack.o 
	$(CPP) $(CPPFLAGS) -o main main.o Group.o ContactInfo.o Queue.o Stack.o

main.o:	main.cpp Group.h ContactInfo.h Queue.h Stack.h
	$(CPP) $(CPPFLAGS) -c main.cpp

Group.o: Group.h Group.cpp 
	$(CPP) $(CPPFLAGS) -c Group.h Group.cpp

ContactInfo.o: ContactInfo.h ContactInfo.cpp
	$(CPP) $(CPPFLAGS) -c ContactInfo.h ContactInfo.cpp

Queue.o: Queue.h Queue.cpp 
	$(CPP) $(CPPFLAGS) -c Queue.h Queue.cpp

Stack.o: Stack.h Stack.cpp
	$(CPP) $(CPPFLAGS) -c Stack.h Stack.cpp

clean:
	rm *.o *.h.gch main
