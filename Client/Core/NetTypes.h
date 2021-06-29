#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
struct Socket {
	int sockfd = -1;
	~Socket() { if (sockfd != -1) { close(sockfd); }  }
	bool Init();
	
	void UnblockInput();
	void BlockInput();
	
	int ReadBuf(void * buf, const int bytelen);
	bool SendBuf(const void * buf, const int bytelen);
};

namespace Client {

struct Server {
	struct sockaddr_in addr;
	
	bool InitHost(const char * hostname);
	void InitService(int port);
	Server() = default;
	Server(const char * hostname);
};

}


//**************** DETAILS *******************
int Socket::ReadBuf(void * buf, const int bytecap) {

    //bzero(buf, bytesize);
    int n = read(sockfd, buf, bytecap);
    if (n < 0) {
         fprintf(stderr, "ERROR writing to socket");
    }
    return n;
}

bool Socket::SendBuf(const void * buf, const int bytelen) {
    int n = write(sockfd, buf, bytelen);
    if (n < 0) {
         fprintf(stderr, "ERROR writing to socket");
         return false;
    }
    return true;
}

void Socket::UnblockInput() {
	int flags = fcntl(sockfd,F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}

void Socket::BlockInput() {
	int flags = fcntl(sockfd,F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags & !O_NONBLOCK);
}

	
bool Socket::Init() {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) { fprintf(stderr, "ERROR opening socket\n"); return false; }
	return true;
}

bool Client::Server::InitHost(const char * hostname) {
	struct hostent *server = gethostbyname(hostname);
	if (server == NULL) { return false; }
	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
		(char *)&addr.sin_addr.s_addr,
		server->h_length);
	return true;
}

void Client::Server::InitService(int port) {
	addr.sin_port = htons(port);
}

Client::Server::Server(const char * hostname) { InitHost(hostname); }
