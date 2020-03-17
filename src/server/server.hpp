/**
 * @file server.hpp
 * @author XCOM
 * @brief Server class header
*/
#ifndef SERVER_HPP
#define SERVER_HPP

//Standard includes
#include <vector>

//3rd Party includes
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Event.h>

//Project includes
#include "client_connection_handler.hpp"

class server : public Poco::Net::TCPServer 
{
public:
    using SocketAddress = Poco::Net::SocketAddress;
    using ServerSocket = Poco::Net::ServerSocket;
    using StreamSocket = Poco::Net::StreamSocket;
    using TCPServer = Poco::Net::TCPServer;
    using TCPServerConnection = Poco::Net::TCPServerConnection;
    using Event = Poco::Event;

private:
    std::vector<TCPServerConnection*> m_connection;

public:
    /**
     * @brief Def constructor
     * @param server_socket server's socket
     */
    server(ServerSocket* server_socket);

    /**
     * @brief Copy constructor
     */
    server(const server& other) = delete;

    /**
     * @brief Move Copy constructor 
     */
    server(const server&& other) = delete;

    /**
     * @brief Assignment operator
     */
    server& operator=(const server& other) = delete;

    /**
     * @brief Move Assignment operator
     */
    server& operator=(const server&& other) = delete;

    /**
     * @brief Destructor
     */
    ~server() noexcept;

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
