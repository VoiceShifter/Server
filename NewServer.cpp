# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <cstdio>
# include <iostream>
# include <string>
signed int main()
{
	signed int Socket = socket(
			AF_INET, //domain - IPv4 protocol
			SOCK_STREAM,
			0);

	sockaddr_in SocketAddres;
	SocketAddres.sin_family = AF_INET;
	SocketAddres.sin_port = htons(32323);
	//inet_aton("0.0.0.0", &SocketAddres.sin_addr.s_addr);
	//printf("%s\n", INADDR_ANY);
	SocketAddres.sin_addr.s_addr = htonl(INADDR_ANY); //0.0.0.0
	signed int result = bind(Socket, (const sockaddr *)(&SocketAddres), sizeof(SocketAddres));
	listen(Socket, SOMAXCONN);
	while(1)
	{
		signed int SlaveSocket = accept(Socket, 0, 0);
		std::cout << "Connection established\n";
		char Buffer[99]{};
//		scanf("", Buffer);
		recv(SlaveSocket, Buffer, 99, MSG_NOSIGNAL);
		printf("%s\n", Buffer);
		std::string StringBuffer{};
		std::getline(std::cin, StringBuffer);
		StringBuffer+="\n";
		const char* NewPointer{StringBuffer.c_str()};
		send(SlaveSocket, NewPointer, sizeof(NewPointer), MSG_NOSIGNAL);
		shutdown(SlaveSocket, SHUT_RDWR);
		//printf("%s\n",Buffer);
	}
	return 0;
}
