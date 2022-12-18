#include <iostream>
#include <sys/socket.h>

#define PORT 8080

/**
 *
 * @auther Sachin Kumar
 * @version 18-12-2022
 *
 */


class Server
{
public:
	Server() 
	{
		// Creating socker file descriptor
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("socket failed");
			exit(EXIT_FAILURE);
		}

	}
	~Server()
	{
	}
private:
	int server_fd, new_socket, valread;
};


int main(int argc, char* argv[])
{
	Server server;
	return 0;
}
