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
