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

Server::Server(ServerSocket* serverSocket) :
    TCPServer(new TCPFactory(), *serverSocket)
{
    std::cout << "Server created" << std::endl;
}

Server::~Server() noexcept 
{   
    stop();
}

void Server::push_back(TCPServerConnection* connection) noexcept
{
    m_connection.push_back(connection);
}

void Server::pop_back() noexcept
{
    m_connection.pop_back();
}