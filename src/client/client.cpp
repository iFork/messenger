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

Client::Client() noexcept
{
    std::cout << "Connecting to host: "<< HOST << " ..." << std::endl;
    m_ipv4 = new SocketAddress(HOST);
    m_clientSocket = new StreamSocket(*m_ipv4);
    
    std::string s("Give me some information");
    m_outputBuffer = s.c_str();
    m_clientSocket->sendBytes(m_outputBuffer, SIZE);

//    int k = m_clientSocket->receiveBytes(m_inputBuffer, SIZE);
//    std::cout << "Buffer " << k << " " << (std::string)m_inputBuffer << std::endl;
}

Client::Client(const Client& other) noexcept
{
    m_ipv4 = other.m_ipv4;
    m_clientSocket = other.m_clientSocket;
    m_inputBuffer = other.m_inputBuffer;
    m_outputBuffer = other.m_outputBuffer;
}

Client& Client::operator=(const Client&& other) noexcept
{
    m_ipv4 = std::move(other.m_ipv4);
    m_clientSocket = std::move(other.m_clientSocket);
    m_inputBuffer = std::move(other.m_inputBuffer);
    m_outputBuffer = std::move(other.m_outputBuffer);

    return *this;

}

Client::~Client() noexcept
{
    assert(nullptr != m_clientSocket);
    m_clientSocket->close();
}
