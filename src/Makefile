CXX = g++
OBJS = main.o
CXXFLAGS = -std=c++14 -I/opt/homebrew/Cellar/opendht/3.1.7/include -I/opt/homebrew/Cellar/msgpack-cxx/6.1.0/include -I/opt/homebrew/Cellar/boost/1.84.0_1/include -I/opt/homebrew/Cellar/fmt/10.2.1_1/include -I/opt/homebrew/Cellar/gnutls/3.8.3/include
LDFLAGS = -L/opt/homebrew/Cellar/opendht/3.1.7/lib -lopendht

all: dfs

dfs: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o dfs $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -o main.o -c main.cpp

clean:
	rm -f dfs main.o
