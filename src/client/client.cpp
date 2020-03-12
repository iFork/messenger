#include "client.hpp"
#include "commands/commands.hpp"

#include <iostream>
#include <cassert>

Client::Client() noexcept
{
    m_ipv4 = new SocketAddress("127.0.0.1:8000");
    m_clientSocket = new StreamSocket(*m_ipv4);
    
    std::string s("Give me some information");
    m_outputBuffer = s.c_str();
    m_clientSocket->sendBytes(m_outputBuffer, sizeof(s));

//    int k = m_clientSocket->receiveBytes(m_inputBuffer,50);
//   std::cout << "Buffer " << k << " " << (std::string)m_inputBuffer << std::endl;     
  
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
    delete m_inputBuffer;
    delete m_outputBuffer;
    m_ipv4 = std::move(other.m_ipv4);
    m_clientSocket = std::move(other.m_clientSocket);
    m_inputBuffer = std::move(other.m_inputBuffer);
    m_outputBuffer = std::move(other.m_outputBuffer);
    return *this;
}

Client::~Client() noexcept
{    
    delete m_inputBuffer;
    delete m_outputBuffer;
    assert(nullptr != m_clientSocket);
    m_clientSocket->close();
}
