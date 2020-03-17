/**
 * @file client.hpp
 * @author XCOM
 * @brief Client class header
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

//Includes project relates headers
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>

using SocketAddress = Poco::Net::SocketAddress;
using StreamSocket = Poco::Net::StreamSocket;

/**
 * @class class Client
*/
class Client 
{
private:
    SocketAddress* m_ipv4;
    StreamSocket* m_clientSocket;
    const char* m_outputBuffer;
    char* m_inputBuffer;

public:
    /**
     * @brief Def constructor
     */
    Client() noexcept;

    /**
     * @brief Copy constructor
     */
    Client(const Client& other) noexcept;

    /**
     * @brief Assignment move operator
     */
    Client& operator=(const Client&& other) noexcept;

    /**
     * @brief Destructor
     */
    ~Client() noexcept;
};

#endif // CLIENT_HPP
