###########################################################################
##                    Makefile for HW2 (CharLinkedList)                   ##
###########################################################################

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

test_list: unit_tests.o CharLinkedList.o 
	$(CXX) $(LDFLAGS) -o test_list unit_tests.o CharLinkedList.o

unit_tests.o: unit_tests.cpp CharLinkedList.h
CharLinkedList.o: CharLinkedList.cpp CharLinkedList.h

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.o core* *~ test_list