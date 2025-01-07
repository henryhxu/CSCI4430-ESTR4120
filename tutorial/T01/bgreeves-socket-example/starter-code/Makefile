CXX = g++
CXXFLAGS = -g -std=c++11 -pedantic

all: server client

server: server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o server

client: client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client

clean:
	rm -rf client server *.dSYM

.PHONY: clean
