#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

int main(int argc , char **argv){
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buf[1024];
	time_t ticks;

	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("socket error");

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if( bind(listenfd,( struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		perror("bind error");

	if( listen(listenfd,10)<0)
		perror("listen error");

	for( ; ; ){
		connfd= accept(listenfd, (struct sockaddr *)NULL,NULL);
		ticks = time(NULL);
		snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&ticks));
		write(connfd, buf, strlen(buf));

		close(connfd);
	}
	exit(0);
}
