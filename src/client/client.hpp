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


//STL Includes
#include <vector>

#include "shared/user.hpp"

/**
 * @class class client
*/
class client
{ 
public:
    using SocketAddress = Poco::Net::SocketAddress;
    using StreamSocket = Poco::Net::StreamSocket;

private:
    user* m_user;
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
     * @brief Send message to Server 
     */
    void send(std::string message);
    
    /**
     * @brief Recive message from Server 
     */
    std::string recive();

    /**
     * @brief Connect to Server 
     */
    void connect();

    /**
     * @brief Checking internet connection
     */
    bool check_internet_connection();
    
    /**
     * @brief Destructor
     */
    ~client() noexcept;

public:
    void log_in_helper(std::string username);
    void sign_up_helper(std::string username);
    void new_group_helper(std::string& name, std::vector<user> users);
    void call_helper(user& user);
    void video_call_helper(user& user);
    void open_camera_helper();
    //void send_file_helper(const File& file);
    //void send_smile_helper(const Image& img);
    void send_messege_helper(std::string& messege);

};

#endif // CLIENT_HPP
