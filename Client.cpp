# include <iostream>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include <sys/socket.h>
# include <unistd.h>

signed int main()
{

	int Socket = socket(
			AF_INET,
			SOCK_STREAM,
			0);
	sockaddr_in SockAdr;
	SockAdr.sin_family = AF_INET;
	SockAdr.sin_port = htons(32323);
	SockAdr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(Socket, (const sockaddr *)(&SockAdr), sizeof(SockAdr));
	char Buffer[]{"PING"};
	send(Socket, Buffer, 4, MSG_NOSIGNAL);
	recv(Socket, Buffer, 4, MSG_NOSIGNAL);
	shutdown(Socket, SHUT_RDWR);
	close(Socket);
	printf("%s\n", Buffer);
	return 0;
}

