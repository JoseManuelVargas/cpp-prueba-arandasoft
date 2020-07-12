#include <iostream>
#include "gtest/gtest.h"

#include "Scheduler.h"
#include "socket.h"

#define PORT_TEST 8080

bool server_created = false;
string recvFromServer = "";
string recvFromClient = "";


void createServer(const std::string & msg) {
	SocketServer server(PORT_TEST);
	server_created = true;
	std::cout << "Server socket created" << std::endl;
	server.acceptSocket();
	for (int i = 0; i < 5; i++) {
		server.sendLine(msg);
		std::cout << ">>>Server:  Se envío " << msg << " desde el server" << std::endl;
		recvFromClient = server.readLine();	
		std::cout << ">>>Server:  Se recibio " << recvFromClient << " desde el cliente" << std::endl;
	}
	server.close();
}


void createClient(const std::string & msg) {
	while (!server_created);
	SocketClient client("127.0.0.1", PORT_TEST);
	for (int i = 0; i < 5; i++) {
		recvFromServer = client.readLine();
		std::cout << "<<<Client:  Se recibio " << recvFromServer << " desde el server" << std::endl;
		client.sendLine(msg);
		std::cout << "<<<Client:  Se envío " << msg << " desde el cliente" << std::endl;
	}
	client.close();
}


TEST(SocketTest, SocketTest1) {
      	// number of tasks that can run simultaneously  
	// Note: not the number of tasks that can be added,
	// but number of tasks that can be run in parallel
	unsigned int max_n_threads = 12;
      
	// Make a new scheduling object.
	//   // Note: s cannot be moved or copied
	
	Bosma::Scheduler s(max_n_threads);
	// in one minute
	
	std::string clientMsg = "Msg from Client Socket.";
	s.in(std::chrono::seconds(0), createClient, clientMsg);
	std::string serverMsg = "Msg from Server Socket.";
	s.in(std::chrono::seconds(0), createServer, serverMsg);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	EXPECT_EQ(clientMsg, recvFromClient);
	EXPECT_EQ(serverMsg, recvFromServer);
}

