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

void client::log_in_helper(std::string& username)
{
    std::cout << "Log In" << username << std::endl;
}

void client::sign_up_helper(std::string& username)
{
    std::cout << "Sign Up" << username << std::endl;
}

void client::new_group_helper(std::string& name, std::vector<user> users)
{
    for(size_t i = 0; i < users.size(); ++i) 
    {
        std::cout << users[i].get_username() << std::endl;
    }

    std::cout << "New group" << name << std::endl;
}

void client::call_helper(user& user)
{
    std::cout << user.get_user_id() << std::endl;
    std::cout << user.get_username() << std::endl;
}

void client::video_call_helper(user& user)
{
    std::cout << user.get_user_id() << std::endl;
    std::cout << user.get_username() << std::endl;
}

void client::open_camera_helper()
{

}

/*void client::send_file_helper(const File& file)
{

}*/

/*void client::send_smile_helper(const Image& img)
{

}*/

void client::send_messege_helper(std::string& messege)
{
    std::cout << "send messege " << messege << std::endl; 
}
