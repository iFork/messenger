#include "user.hpp"
#include <iostream>

//static member initialization
int user::m_count = 0;

user::user(std::string username) : m_user_id(m_count++),
                                   m_username(username)
                                 
{
    m_user_contacts = std::vector<std::pair<user*, bool>>();
}

user::~user()
{

}

void user::add_to_contacts(user* username) 
{
    m_user_contacts.push_back(std::make_pair(username,false));
}

void user::add_to_conversation(user* username)
{
    for(size_t i = 0; i < m_user_contacts.size(); ++i)
    {
        if(username == m_user_contacts[i].first)
        {
            m_user_contacts[i].second = true;
        }
        else
        {
            std::cout << "There is not such user in you contact list" << std::endl;
        }
        
    }
}

void user::delete_from_contacts(const user* username)
{
    for(size_t i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first == username)
        {
            m_user_contacts.erase(m_user_contacts.begin() + i);
        }
        else
        {
            std::cout << "There is not such user in you contact list" << std::endl;
        }
    }

}

void user::delete_from_contacts(size_t user_id) 
{
    for(size_t i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first->m_user_id == user_id)
        {
            m_user_contacts.erase(m_user_contacts.begin() + i);
        }
        else
        {
            std::cout << "There is not such user in you contact list" << std::endl;
        }
    }
}

void user::delete_from_contacts(std::string& username)
{
    for(size_t i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first->m_username == username)
        {
            m_user_contacts.erase(m_user_contacts.begin() + i);
        }
        else
        {
            std::cout << "There is not such user in you contact list" << std::endl;
        }
    }
}

void user::delete_from_conversation(const user* username)
{
    for(size_t i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first == username)
        {
            m_user_contacts[i].second = false;
        }
        else
        {
            std::cout << "There is not such user in you conversation list" << std::endl;
        }
    }
}

void user::delete_from_conversation(size_t user_id)
{
    for(size_t i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first->m_user_id == user_id)
        {
            m_user_contacts[i].second = false;
        }
        else
        {
            std::cout << "There is not such user in you conversation list" << std::endl;
        }
    }
}

void user::delete_from_conversation(std::string& username)
{
    for(size_t i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first->m_username == username)
        {
            m_user_contacts[i].second = false;
        }
        else
        {
            std::cout << "There is not such user in you conversation list" << std::endl;
        }
    }
}

void user::set_username(std::string& username) 
{
    m_username = username;
}

std::vector<std::pair<user*,bool>> user::get_user_contacts() const
{
    return m_user_contacts;
}

size_t user::get_user_id() const
{
    return m_user_id;
}

std::string user::get_username() const
{
    return m_username;
}