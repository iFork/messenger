/**
 * @file client.cpp
 * @author XCOM
 * @brief Client class implementation
*/

//Project includes
#include "client.hpp"

//Standard includes
#include <iostream>
#include <cassert>

//define values
#define SIZE 1024
#define IP "127.0.0.1"
#define PORT ":8000"
#define HOST IP PORT

client::client() noexcept
{
    std::cout << "Connecting to host: "<< HOST << " ..." << std::endl;
    m_ipv4 = new SocketAddress(HOST);
    m_client_socket = new StreamSocket(*m_ipv4);
    
    std::string s("Give me some information");
    m_output_buffer = s.c_str();
    m_client_socket->sendBytes(m_output_buffer, SIZE);

//    int k = m_clientSocket->receiveBytes(m_inputBuffer, SIZE);
//    std::cout << "Buffer " << k << " " << (std::string)m_inputBuffer << std::endl;
}

client::~client() noexcept
{
    assert(nullptr != m_client_socket);
    m_client_socket->close();
}
