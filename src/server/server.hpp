/**
 * @file server.hpp
 * @author XCOM
 * @brief Server class header
*/
#ifndef SERVER_HPP
#define SERVER_HPP

//Standard includes
#include <vector>

//Relates includes
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Event.h"

//Project includes
#include "client_connection_handler.hpp"

using SocketAddress = Poco::Net::SocketAddress;
using ServerSocket = Poco::Net::ServerSocket;
using StreamSocket = Poco::Net::StreamSocket;
using TCPServer = Poco::Net::TCPServer;
using Event = Poco::Event;

class Server : public TCPServer {
private:
    std::vector<TCPServerConnection*> m_connection;
public:
    /**
     * @brief Def constructor
     * @param ServerSocket server's socket
     */
    Server(ServerSocket*);

    /**
     * @brief Copy constructor
     */
    Server(const Server& other) = delete;

    /**
     * @brief Assignment operator
     */
    Server& operator=(const Server&& other) = delete;

    /**
     * @brief Destructor
     */
    ~Server() noexcept;

    /**
     * @brief Push back @params to vector
     * @param TCPServerConnection* 
     */
    void push_back(TCPServerConnection* connection) noexcept;

    /**
     * @brief Pop back from vector
     */
    void pop_back() noexcept;
};

#endif // SERVER_HPP
