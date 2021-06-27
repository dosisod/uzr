CXXFLAGS=-g -O0 -Wall -Wextra -pedantic -Werror

all: uzr

httplib.h.gch: httplib.h
	$(CXX) -c httplib.h

%.o: %.cpp
	$(CXX) $^ -c -o $@ $(CXXFLAGS)

uzr: httplib.h.gch main.o api.o user.o
	$(CXX) main.o api.o user.o -lcrypt -lpthread $(CXXFLAGS) -o uzr

clean:
	rm -f uzr *.o

cleaner: clean
	rm -f httplib.h.gch
