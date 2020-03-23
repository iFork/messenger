/**
 * @file client.cpp
 * @brief Implementation for the client library
 * @author ITC students
 * Instigate Training Center Foundation, Yerevan, 2020
 */

// includes from this project
#include "client.hpp"

// includes from C++ library
#include <iostream>

// includes from C library
#include <cassert>

// define values
#define SIZE 1024
#define IP "127.0.0.1"
#define PORT ":8000"
#define HOST IP PORT

client::client() noexcept
{   
    connect();
}

client::~client() noexcept
{
    assert(nullptr != m_client_socket);
    m_client_socket->close();
}

void client::send(std::string message)
{
    assert("" != message);
    std::string s("Give me some information");
    m_output_buffer = message.c_str();
    m_client_socket->sendBytes(m_output_buffer, SIZE);

}

std::string client::recive()
{
    int k = m_client_socket->receiveBytes(m_input_buffer, SIZE);
    std::string res = (std::string)m_input_buffer;
    std::cout << "Buffer " << k << " " << (std::string)m_input_buffer << std::endl;
    return res;
}

void client::connect()
{
    if(check_internet_connection())
    {
        m_ipv4 = new SocketAddress(HOST);
        m_client_socket = new StreamSocket();
        m_client_socket->connect(*m_ipv4);
    } 
    else 
    {
        std::cout << "Connection to server failed" << std::endl;
    }
}

bool client::check_internet_connection()
{
    std::cout << "_________________Checking internet connection________________" << std::endl;
    int connection = system("ping -c 1 8.8.8.8");
    if(connection)
    {
        std::cout << "_____________________________________________________________" << std::endl;
        std::cout << "There is no internet connection" << std::endl;
        return false;
    }
    else
    {                 
        std::cout << "_____________________________________________________________" << std::endl;
        std::cout << "There is internet connection" << std::endl;
        return true;
    }    
}

void client::log_in_helper(std::string username)
{
    std::cout << "Log In " << username << std::endl;
}

void client::sign_up_helper(std::string username)
{
    std::cout << "Sign Up " << username << std::endl;
}

void client::new_group_helper(std::string& name, std::vector<user> users)
{
    for(size_t i = 0; i < users.size(); ++i) 
    {
        std::cout << users[i].get_username() << std::endl;
    }

    std::cout << "New group " << name << std::endl;
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
