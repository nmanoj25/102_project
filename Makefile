CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = MWST.o

MWST: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o MWST MWST.o

MWST.o: MWST.cpp
		$(CXX) -g $(CXXFLAGS) -c MWST.cpp

clean:
		rm -f *.o
		rm MWST 
