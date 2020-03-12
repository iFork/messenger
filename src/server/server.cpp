#include "server.hpp"
#include <string>

Server::Server() noexcept 
{
    m_ipv4 = new SocketAddress("127.0.0.1:8000");
    m_serverSocket = new ServerSocket(*m_ipv4);
        
    int count = 0;
    while (true) {
        StreamSocket clientSocket = m_serverSocket->acceptConnection();     
        m_inputBuffer = new char[50];    
        std::cout << "Client accepted " << ++count << "\n";
        int k = clientSocket.receiveBytes(m_inputBuffer, 50);
        std::cout << "Buffer " << k << " " << (std::string)m_inputBuffer << std::endl;
        std::string s("Here is your information");
        m_outputBuffer = s.c_str();
        clientSocket.sendBytes(m_outputBuffer, sizeof(s));
    
    }
        
}

Server::Server(const Server& other) noexcept
{
    m_ipv4 = other.m_ipv4;
    m_serverSocket = other.m_serverSocket;
    m_inputBuffer = other.m_inputBuffer;
    m_outputBuffer = other.m_outputBuffer;
}

Server& Server::operator=(const Server&& other) noexcept
{   
    delete m_inputBuffer;
    delete m_outputBuffer;
    m_ipv4 = std::move(other.m_ipv4);
    m_serverSocket = std::move(other.m_serverSocket);
    m_inputBuffer = std::move(other.m_inputBuffer);
    m_outputBuffer = std::move(other.m_outputBuffer);
    return *this;
}

Server::~Server() noexcept 
{   
    delete m_inputBuffer;
    delete m_outputBuffer;
    m_serverSocket->close();
}
