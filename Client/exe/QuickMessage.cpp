#include "Connection.h"
#include <cstring>
#include <cstdio>
#include <vector>

int main(int argc, char * argv[]) {
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    
    Client::Connection cnxn;
    
    if (!cnxn.sock.Init()) {
    	fprintf(stdout, "Failed initializing a socket\n");
    	return 1;
    }
    
    if (!cnxn.serv.InitHost(argv[1])) { //check return on InitHost to see if it exists.
    	fprintf(stdout, "The host %s is not a valid hostname\n", argv[1]);
    	return 1;
    }
    int portno = atoi(argv[2]);
    cnxn.serv.InitService(portno); //DEFINES (likely) SERVICE AND PROTOCOL
    
    fprintf(stdout, "Connecting...\n");
    if (!cnxn.Connect()) {
    	fprintf(stderr, "Exiting Program\n");
    	return 1;
    }
    fprintf(stdout, "CONNECTED\n");
    
    
    char outbuf[256];
    
    printf("Please enter the message: \n");
    bzero(outbuf,256);
    fgets(outbuf,255,stdin);
    cnxn.sock.SendBuf(outbuf, strlen(outbuf));
    printf("SENT:\n%s\n", outbuf);
    
    printf("WAITING RECEIVE...\n");
    char inbuf[2048];
    cnxn.sock.ReadBuf(inbuf, 2048);
    fprintf(stdout, "RECEIVED:\n%s\n", inbuf);
}
