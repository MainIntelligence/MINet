#pragma once
#include "NetTypes.h"

namespace Client {

struct Connection {
    Socket sock;
    Server serv;
    
    
    Connection() { sock.Init(); }
    Connection(int recvcap, int sendcap) { sock.Init(); }
    bool Connect();
};

bool Connection::Connect() {
	if (connect(sock.sockfd, (struct sockaddr *) &serv.addr, sizeof(serv.addr)) < 0) {
		fprintf(stderr, "ERROR connecting\n");
		return false;
	}
	return true;
}

}
