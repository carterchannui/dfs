CXX = g++
OBJS = main.o
CXXFLAGS = -std=c++14 -I/opt/homebrew/Cellar/ffmpeg/7.0_1/include -I/opt/homebrew/Cellar/opendht/3.1.11/include -I/opt/homebrew/Cellar/msgpack-cxx/6.1.1/include -I/opt/homebrew/Cellar/boost/1.84.0_1/include -I/opt/homebrew/Cellar/fmt/10.2.1_1/include -I/opt/homebrew/Cellar/gnutls/3.8.4/include -I/opt/homebrew/Cellar/openssl@3/3.2.1/include
LDFLAGS = -L/opt/homebrew/Cellar/opendht/3.1.11/lib -lopendht -L/opt/homebrew/Cellar/openssl@3/3.2.1/lib -lssl -lcrypto

all: dfs

dfs: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o dfs $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -o main.o -c main.cpp

clean:
	rm -f dfs main.o retrieved_video.mp4
