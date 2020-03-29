#ifndef MESSENGER_DATABASE_CHAT_DB_HANDLER_HPP
#define MESSENGER_DATABASE_CHAT_DB_HANDLER_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

/**
 * @file src/db/chat_db_handler.hpp
 * @author ITC students
 * @brief chat_database_handler class definition
*/

#include <string>

namespace messenger {
	namespace database {
		class chat_database_handler 
		{
			private:
				std::string m_dirname = "";
				std::string m_filename = "";
			
			private:
				std::string get_filename() const noexcept;
				void set_filename(const std::string&) noexcept;

			public:
				
			    /**
			     * @brief Create new chat with given chat_id and chat_name in db
				 * create new file from given chat_id in db and write given chat data in that file
				 * @param chat_id	identifier for chat
				 * @param chat_data	chat data 	
				 * @return 0 if successful, -1 otherwise
				 */
				int create_chat(const std::string& chat_id, const std::string& chat_data) noexcept;
			    
				/**
			     * @brief Get chat data from db  
				 * @param chat_id	identifier for chat
				 * @return string containing chat data
				 */
				std::string read_chat_data(const std::string& chat_id) noexcept;
				
				/**
			     * @brief Check if chat_id exists in db or not
				 * @param chat_id	identifier for chat
				 * @return true given chat_id exist in db, false otherwise
				 */
				bool search_chat(const std::string& chat_id) noexcept;
			    
				/**
			     * @brief Update chat data in db
				 * @param chat_id	identifier for chat
				 * @param chat_data	chat data
				 */
				void update_chat(const std::string& chat_id, const std::string& chat_data) noexcept;
				
				/**
			     * @brief Delete chat from db
				 * @param chat_id	identifier for chat
				 * @return 0 if successful, -1 otherwise
				 */ 
				int delete_chat(const std::string& chat_id) noexcept;
				
				/**
			     * @brief Def constructor
				 */
			    chat_database_handler() noexcept;
			    
				/**
			     * @brief Copy constructor
				 */ 
			    chat_database_handler(const chat_database_handler&) = delete;
			
			    /**
			     * @brief Move constructor
				 */ 
			    chat_database_handler(const chat_database_handler&&) = delete;
			
			    /**
			     * @brief Copy assignment operator
				 */
			    chat_database_handler& operator=(const chat_database_handler&) = delete;
			
			    /**
			     * @brief Move assignment operator
				 */ 
			    chat_database_handler& operator=(const chat_database_handler&&) = delete;
			
			    /**
			     * @brief Destructor
				 */ 
			    ~chat_database_handler() noexcept;
		};
	}
}

#endif // MESSENGER_DATABASE_CHAT_DB_HANDLER_HPP
