CXXFLAGS=-g -Wall -Wextra -pedantic -Werror

all: uzr

httplib.h.gch: httplib.h
	$(CXX) -c httplib.h

uzr: httplib.h.gch main.cpp
	$(CXX) main.cpp -lpthread $(CXXFLAGS) -o uzr
