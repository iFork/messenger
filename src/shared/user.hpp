/**
 * @file user.hpp
 * @author XCOM
 * @brief user class header
*/

#ifndef USER_HPP
#define USER_HPP

//STL Includes
#include <string>
#include <vector>

class user {
private:
    static int m_count;
    size_t m_user_id;
    std::string m_username;
    std::vector<std::pair<user*,bool>> m_user_contacts;
public:
    user(std::string username);
    ~user();

    void add_to_contacts(user* username);
    void add_to_conversation(user* username);

    void delete_from_contacts(const user* username);
    void delete_from_contacts(size_t user_id);
    void delete_from_contacts(std::string& username);

    void delete_from_conversation(const user* username);
    void delete_from_conversation(size_t user_id);
    void delete_from_conversation(std::string& username);

    void set_username(std::string& username);

    std::vector<std::pair<user*,bool>> get_user_contacts() const;
    size_t get_user_id() const;
    std::string get_username() const;   
};

#endif // USER_HPP