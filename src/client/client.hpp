#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>

using SocketAddress = Poco::Net::SocketAddress;
using StreamSocket = Poco::Net::StreamSocket;

class Client 
{
private:
    SocketAddress* m_ipv4;
    StreamSocket* m_clientSocket;
    const char* m_outputBuffer;
    char* m_inputBuffer;

public:
    Client() noexcept;
    Client(const Client& other) noexcept;
    Client& operator=(const Client&& other) noexcept;
    ~Client() noexcept;

};

#endif // CLIENT_HPP
