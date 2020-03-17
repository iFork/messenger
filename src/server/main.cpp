#include "server.hpp"

#include "Poco/Net/NetException.h"

#include <iostream>

Event terminator;

int main() {
    try {
        SocketAddress* ipv4 = new SocketAddress("127.0.0.1:8000"); 
        ServerSocket* serverSocket = new ServerSocket(*ipv4);
        Server srv = Server(serverSocket);
        srv.start();
        std::cout << "TCP server listening on port " << ipv4->port() << '.'
			 << std::endl << "Press Ctrl-C to quit." << std::endl;
        terminator.wait();

    } catch(Poco::Net::NetException& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
