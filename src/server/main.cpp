#include "server.hpp"

#include <Poco/Net/NetException.h>

#include <iostream>

using SocketAddress = Poco::Net::SocketAddress;
using ServerSocket = Poco::Net::ServerSocket;
using Event = Poco::Event;

int main() 
{
    try 
    {
        Event terminator;
        SocketAddress* ipv4 = new SocketAddress("127.0.0.1:8000"); 
        ServerSocket* server_socket = new ServerSocket(*ipv4);
        server srv = server(server_socket);
        srv.start();
        std::cout << "TCP server listening on port " << ipv4->port() << '.'
			 << std::endl << "Press Ctrl-C to quit." << std::endl;
        terminator.wait();

    } catch(Poco::Net::NetException& e) 
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
