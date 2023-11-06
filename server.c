#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(){
	int ss, cs, read;
	int opt = 1;
	struct sockaddr_in ser_adr, cli_adr;
	socklen_t len = sizeof(ser_adr);
	char buffer[1024] = { 0 };
	char* hello = "Hello from server";
	
	ss = socket(AF_INET, SOCK_STREAM, 0);
	
	ser_adr.sin_family = AF_INET;
	ser_adr.sin_addr.s_addr = INADDR_ANY;
	ser_adr.sin_port = htons(PORT);
	
	bind(ss, (struct sockaddr *) &ser_adr, sizeof(ser_adr));
	
	listen(ss, 3);
	
	printf("ITS A WORKIN");
	
	len = sizeof(cli_adr);
	cs = accept(ss, (struct sockaddr *) &cli_adr, &len);
	
	while (true){
		read = recv(cs, buffer, read, 0);
		if(read<0){
			break;
		}
		if (strlen(buffer) > 0)
			printf("LOL: %s\n", buffer);
		send(cs, hello, read, 0);
	}
	
	close(ss);
	close(cs);
	return 0;
}

#### CLIENT ####

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int valread, client_fd;
	struct sockaddr_in serv_addr;
	char* hello = "Hello from client";
	char buffer[1024] = { 0 };
	
	//IDK THIS EITHER
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	//IF ONLY I KNEW
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	//CONVERT ADDRESS TO BINARY
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

	//CONNECT
	connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	
	
	//SEND AND RECIEVE 
	send(client_fd, hello, strlen(hello), 0);
	read(client_fd, buffer, 1024 - 1);


	close(client_fd);
	return 0;
}
