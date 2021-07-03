CXXFLAGS=-g -O0 -Wall -Wextra -pedantic -Werror -I src/vendor
OBJS=$(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
VEND=src/vendor

all: uzr

$(VEND)/httplib.o: $(VEND)/httplib.cc $(VEND)/httplib.h
	$(CXX) -c $< -o $(VEND)/httplib.o

$(VEND)/json.hpp.gch: $(VEND)/json.hpp
	$(CXX) -std=c++11 -c $^

%.o: %.cpp %.hpp
	$(CXX) $< -c -o $@ $(CXXFLAGS)

uzr: $(VEND)/httplib.o $(VEND)/json.hpp.gch $(OBJS)
	$(CXX) $(OBJS) $(VEND)/httplib.o -lcrypt -lpthread $(CXXFLAGS) -o uzr

clean:
	rm -f uzr **/*.o

cleaner: clean
	rm -f src/vendor/*.gch
