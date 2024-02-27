# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <cstdio>

# include <iostream>
# include <string>

signed int SetNonBlock()
{
	return 0;
}

signed int main()
{
	signed int Socket = socket(AF_INET, SOCK_STREAM, 0);
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
		char Buffer[1024];
		std::string StringBuffer{};
		while(recv(SlaveSocket, Buffer, 1, MSG_NOSIGNAL) > 0)
		{
			std::cout << Buffer;
			StringBuffer += Buffer;

		}
		// if (Buffer == "close")
		// {
		// 	shutdown(SlaveSocket, SHUT_RDWR);
		// 	break;
		// }
		// std::getline(std::cin, StringBuffer);	
		StringBuffer+="\n";	
		const char* NewPointer{StringBuffer.c_str() + '\n'};
		printf("%s\n", NewPointer);
	}
	return 0;
}
