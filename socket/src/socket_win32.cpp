#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "socket.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


using std::cerr;
using std::string;
using std::endl;
using std::cout;


string Socket::readLine() {
        char buffer [1024] = {0};
        if (recv(connected_socket, buffer, 1024, 0)) {
                return string(buffer);
        }
        return "";
}


void Socket::sendLine(const string & line) {
        send(connected_socket, line.c_str(), line.length(), 0);
}


void Socket::close() {
	if (connected_socket != INVALID_SOCKET) {
		shutdown(connected_socket, SD_SEND);
		closesocket(connected_socket);
	}
	if (this_socket != INVALID_SOCKET) {
		closesocket(this_socket);
	}
	WSACleanup();
}


SocketClient::SocketClient(const string & host, int port) {
	struct addrinfo *result = NULL, hints;
	WSADATA wsaData;
	connected_socket = INVALID_SOCKET;
	this_socket = INVALID_SOCKET;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		cerr << "WSAStartup failed with error " << iResult << endl;
		throw -1;
	}
	ZeroMemory( &hints, sizeof(hints));
    	hints.ai_family = AF_UNSPEC;
    	hints.ai_socktype = SOCK_STREAM;
    	hints.ai_protocol = IPPROTO_TCP;
	char port_str[32];
	sprintf(port_str, "%d", port);
	if (host == "127.0.0.1" || host == "localhost") {
		iResult = getaddrinfo(NULL, port_str, &hints, &result);
	}
	else {
		iResult = getaddrinfo(host.c_str(), port_str, &hints, &result);
	}
	if (iResult != 0) {
                cerr << "Address error or not supportedr " << iResult << endl;
                throw -2;
        }
	connected_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (connected_socket == INVALID_SOCKET) {
		cerr << "Socket failed with error " << WSAGetLastError() << endl;
		throw -3;
	}
	iResult = connect(connected_socket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connected_socket);
            connected_socket = INVALID_SOCKET;
            cerr <<"Error connecting to server socket" << endl;
        }
	freeaddrinfo(result);
}


SocketServer::SocketServer(int port) {
	struct addrinfo *result = NULL, hints;
        WSADATA wsaData;
        connected_socket = INVALID_SOCKET;
        int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        if (iResult != 0) {
                cerr << "WSAStartup failed with error " << iResult << endl;
                throw -1;
        }
        ZeroMemory( &hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	
	
	char port_str [32];
	sprintf(port_str, "%d", port);
        iResult = getaddrinfo(NULL, port_str, &hints, &result);
        if (iResult != 0) {
                cerr << "Address error or not supportedr " << iResult << endl;
                throw -2;
        }
        this_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (this_socket == INVALID_SOCKET) {
                cerr << "Socket failed with error " << WSAGetLastError() << endl;
                throw -3;
        }
	iResult = bind(this_socket, result->ai_addr, (int)result->ai_addrlen);
    	if (iResult == SOCKET_ERROR) {
		cerr << "bind failed with error: " <<  WSAGetLastError() << endl;
		freeaddrinfo(result);
		closesocket(this_socket);
		WSACleanup();
		throw -4;
    	}
    	freeaddrinfo(result);
}


void SocketServer::acceptSocket() {
	int iResult = listen(this_socket, SOMAXCONN);
    	if (iResult == SOCKET_ERROR) {
		cerr << "listen failed with error: " <<  WSAGetLastError() << endl;
		closesocket(this_socket);
		WSACleanup();
		throw -5;
    	}
    	connected_socket = accept(this_socket, NULL, NULL);
    	if (connected_socket == INVALID_SOCKET) {
		cerr << "accept failed with error: " <<  WSAGetLastError() << endl;
		closesocket(this_socket);
		WSACleanup();
		throw -6;
    	}
}

