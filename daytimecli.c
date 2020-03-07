#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char * argv[]){
	int sockd, n;
	struct sockaddr_in servaddr;
	char line[27];

	sockd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	inet_pton(AF_INET, argv[1],&servaddr.sin_addr);

	connect(sockd,(struct sockaddr *) &servaddr,sizeof(servaddr) );

	while( (n=read(sockd,line,27))>0){
		line[26]='\0';
		fputs(line,stdout);

	}
	exit(0);
}


