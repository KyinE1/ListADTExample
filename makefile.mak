#
# PROGRAM:    list_ADT
# PROGRAMMER: Kyin Edwards
# DATE WRITTEN:   4/8/2021
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11 
        
# Rule to link object code files to create executable file
test_mylist: test_mylist.o
	$(CXX) $(CXXFLAGS) -o test_mylist $^

# Rules to compile source code file to object code
test_mylist: test_mylist.cpp mylist.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f test_mylist *.o
