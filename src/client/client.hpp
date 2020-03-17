/**
 * @file client.hpp
 * @author XCOM
 * @brief Client class header
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

//3rd Party Includes
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>

/**
 * @class class client
*/
class client
{ 
public:
    using SocketAddress = Poco::Net::SocketAddress;
    using StreamSocket = Poco::Net::StreamSocket;

private:
    SocketAddress* m_ipv4;
    StreamSocket* m_client_socket;
    const char* m_output_buffer;
    char* m_input_buffer;

public:
    /**
     * @brief Def constructor
     */
    client() noexcept;

    /**
     * @brief Copy constructor
     */
    client(const client& other) = delete;

    /**
     * @brief Move Copy constructor
     */
    client(const client&& other) = delete;

    /**
     * @brief Assignment move operator
     */
    client& operator=(const client& other) = delete;

    /**
     * @brief Move Assignment move operator
     */
    client& operator=(const client&& other) = delete;

    /**
     * @brief Destructor
     */
    ~client() noexcept;
};

#endif // CLIENT_HPP
