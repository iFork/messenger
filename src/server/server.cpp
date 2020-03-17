/**
 * @file server.cpp
 * @author XCOM
 * @brief Server class implementation
*/

//Project includes
#include "server.hpp"

//Standard includes
#include <iostream>
#include <string>

server::server(ServerSocket* server_socket) :
    TCPServer(new TCPFactory(), *server_socket)
{
    std::cout << "Server created" << std::endl;
}

server::~server() noexcept 
{   
    stop();
}

void server::push_back(TCPServerConnection* connection) noexcept
{
    m_connection.push_back(connection);
}

void server::pop_back() noexcept
{
    m_connection.pop_back();
}