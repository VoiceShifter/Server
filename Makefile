all: Server Client

Server: 
	g++ -g -o0 -o NewServer NewServer.cpp

Client: 
	g++ -g -o0 -o Client client.cpp

