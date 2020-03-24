/**
 * @file src/db/db.hpp
 * @brief database class definition
*/
#ifndef MESSENGER_DATABASE_HPP
#define MESSENGER_DATABASE_HPP

#include <string>

namespace messenger 
{
	class database 
	{
		private:
			std::string m_dirname;
		
		public:
		    
			/**
		     * @brief Def constructor
		    */
		    database() noexcept;
		    
			/**
		     * @brief Copy constructor
		    */
		    database(const database&) = delete;
		
		    /**
		     * @brief Move constructor
		    */
		    database(const database&&) = delete;
		
		    /**
		     * @brief Copy assignment operator
		    */
		    database& operator=(const database&) = delete;
		
		    /**
		     * @brief Move assignment operator
		    */
		    database& operator=(const database&&) = delete;
		
		    /**
		     * @brief Destructor
		    */
		    ~database() noexcept;
		
		    /**
		     * @brief Create new user
			 * @param filename 
			 * @param username 
			*/
			void create_user(const std::string& filename, const std::string& username);
		    
			/**
		     * @brief Get user info from file
			 * #param username
		    */
			std::string read_user_data(const std::string& filename);
			
			/**
		     * @brief Check username already exists or not
			 * #param username
		    */
			bool search_user(const std::string& filename);
		    
			/**
		     * @brief Update user info
			 * #param username
		    */
			void update_user(const std::string& filename, const std::string& user_data);
			
			/**
		     * @brief Delete user
			 * @param username 
			*/
			int delete_user(const std::string& filename);
	};
}

#endif 
