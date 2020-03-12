#ifndef SERVER_HPP
#define SERVER_HPP

#include "commands/commands.hpp"
#include <iostream>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

using SocketAddress = Poco::Net::SocketAddress;
using ServerSocket = Poco::Net::ServerSocket;
using StreamSocket = Poco::Net::StreamSocket;

class Server {
private:
    SocketAddress* m_ipv4;
    ServerSocket* m_serverSocket;
    const char* m_outputBuffer;
    char* m_inputBuffer;
    
public:
    Server() noexcept;
    Server(const Server& other) noexcept;
    Server& operator=(const Server&& other) noexcept;
    ~Server() noexcept;
};

#endif // SERVER_HPP
