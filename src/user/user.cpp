#include "user.hpp"
#include <iostream>

//static member initialization
int m_count = 0;

user::user(std::string username) : m_username(username),
                                 m_user_id(m_count++) 
{
    m_user_contacts = std::vector<std::pair<user*, bool>>();
}

user::~user()
{

}

void user::add_to_contacts(user* user) 
{
    m_user_contacts.push_back(std::make_pair(user,false));
}

void user::add_to_conversation(user* user)
{
    for(int i = 0; i < m_user_contacts.size(); ++i)
    {
        if(user == m_user_contacts[i].first)
        {
            m_user_contacts[i].second = true;
        }
        else
        {
            std::cout << "There is not such user in you contact list" << std::endl;
        }
        
    }
}

void user::delete_from_contacts(const user* user)
{
    for(int i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first == user)
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
    for(int i = 0; i < m_user_contacts.size(); ++i)
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
    for(int i = 0; i < m_user_contacts.size(); ++i)
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

void user::delete_from_conversation(const user* user)
{
    for(int i = 0; i < m_user_contacts.size(); ++i)
    {
        if(m_user_contacts[i].first == user)
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
    for(int i = 0; i < m_user_contacts.size(); ++i)
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
    for(int i = 0; i < m_user_contacts.size(); ++i)
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