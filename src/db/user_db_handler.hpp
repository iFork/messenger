#ifndef MESSENGER_DATABASE_USER_DB_HANDLER_HPP
#define MESSENGER_DATABASE_USER_DB_HANDLER_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

/**
 * @file src/db/user_db_handler.hpp
 * @author ITC students
 * @brief user_database_handler class definition
*/

#include <string>

namespace messenger {
	namespace database {
		class user_database_handler 
		{
			private:
				std::string m_dirname = "";
				std::string m_filename = "";
			
			private:
				std::string get_filename() const noexcept;
				void set_filename(const std::string&) noexcept;
			
			public:
			    
			    /**
			     * @brief Create new user with given user_id and user_name in db
				 * create new file for user, write user data in file
				 * @param user_id	identifier for user
				 * @param user_name	user name
				 */
				void create_user(const std::string& user_id, const std::string& user_name) noexcept;
			    
				/**
			     * @brief Get user data from db  
				 * @param user_id	identifier for user
				 * @return string containing information about user
				 */
				std::string read_user_data(const std::string& user_id) noexcept;
				
				/**
			     * @brief Check if user_id exists in db or not
				 * @param user_id	identifier for user
				 * @return true given user_id exist in db, false otherwise
				 */ 
				bool search_user(const std::string& user_id) noexcept;
			    
				/**
			     * @brief Update user info in db
				 * @param user_id	identifier for user
				 * @param user_data	user data
				 */ 
				void update_user(const std::string& user_id, const std::string& user_data) noexcept;
				
				/**
			     * @brief Delete user from db
				 * @param user_id	identifier for user
				 * @return 0 if successful, 1 otherwise
				 */ 
				int delete_user(const std::string& user_id) noexcept;
				
				/**
			     * @brief Def constructor
				 */ 
			    user_database_handler() noexcept;
			    
				/**
			     * @brief Copy constructor
				 */ 
			    user_database_handler(const user_database_handler&) = delete;
			
			    /**
			     * @brief Move constructor
				 */
			    user_database_handler(const user_database_handler&&) = delete;
			
			    /**
			     * @brief Copy assignment operator
				 */ 
			    user_database_handler& operator=(const user_database_handler&) = delete;
			
			    /**
			     * @brief Move assignment operator
				 */ 
			    user_database_handler& operator=(const user_database_handler&&) = delete;
			
			    /**
			     * @brief Destructor
				 */ 
			    ~user_database_handler() noexcept;
		};
	}
}

#endif // MESSENGER_DATABASE_USER_DB_HANDLER_HPP
