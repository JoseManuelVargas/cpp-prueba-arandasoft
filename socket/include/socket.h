#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <iostream>


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <winsock2.h>
#else
#include <netinet/in.h>

#define SOCKET int
#endif


using std::string;


class Socket {
        public:
		string readLine();
		void sendLine(const string & line);
		void close();
	protected:
		SOCKET this_socket;
		SOCKET connected_socket;
};


class SocketClient : public Socket {
	public:
		SocketClient(const string & host, int port);
};


class SocketServer: public Socket {
	public:
		SocketServer(int port);
		void acceptSocket();
	private:
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)      

#else   
		struct sockaddr_in address;
#endif   
};


#endif /* SOCKET_H */
