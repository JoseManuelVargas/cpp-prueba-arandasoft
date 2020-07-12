#include "socket.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <cstring> 
#include <arpa/inet.h>


using std::cerr;
using std::string;
using std::endl;


string Socket::readLine() {
	char buffer [1024] = {0};
	if (read(connected_socket, buffer, 1024)) {
		return string(buffer);
	}
	return "";
}


void Socket::sendLine(const string & line) {
	send(connected_socket, line.c_str(), line.length(), 0);
}


void Socket::close() {

}


SocketClient::SocketClient(const string & host, int port) {
	connected_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connected_socket < 0) {
		cerr << "Error creating socket client" << endl;
		throw -1;
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr) <= 0) {
		cerr << "Invalid addres or address not supported" << endl;
		throw -2;
	}
	if (connect(connected_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		cerr << "Connection failed" << endl;
		throw -3;
	}
}


SocketServer::SocketServer(int port) {
	this_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this_socket == 0) {
		cerr << "Socket creation failed" << endl;
		throw -1;
	}
	int opt;
	if (setsockopt(this_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		cerr << "Socket setsockopt failed" << endl;
		throw -4;
	}
	address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons(port);
	if (bind(this_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
		cerr << "Error binding port" << endl;
		throw -5;
	}
}


void SocketServer::acceptSocket() {
	int addrlen = sizeof(address);
	if (listen(this_socket, 3) < 0) {
		cerr << "Error listening" << endl;
	   	throw -6;
    	}
    	if ((connected_socket = accept(this_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
		cerr << "Error acepting socket" << endl;
		throw -7;
    	}
}

