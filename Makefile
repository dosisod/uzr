CXXFLAGS=-g -O0 -Wall -Wextra -pedantic -Werror -I src/vendor
OBJS=$(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
VEND=src/vendor

all: uzr

$(VEND)/httplib.h.gch: $(VEND)/httplib.h
	$(CXX) -c $^

%.o: %.cpp
	$(CXX) $^ -c -o $@ $(CXXFLAGS)

uzr: $(VEND)/httplib.h.gch $(OBJS)
	$(CXX) $(OBJS) -lcrypt -lpthread $(CXXFLAGS) -o uzr

clean:
	rm -f uzr **/*.o

cleaner: clean
	rm -f src/vendor/httplib.h.gch
