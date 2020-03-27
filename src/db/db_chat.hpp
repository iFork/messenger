#ifndef MESSENGER_DATABASE_DB_CHAT_HPP
#define MESSENGER_DATABASE_DB_CHAT_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

/**
 * @file src/db/db_chat.hpp
 * @author ITC students
 * @brief database_chat class definition
*/

#include "db_entry.hpp"

#include <string>

namespace messenger {
	namespace database {
		/**
		 * @class database_chat
		 * @var m_db_entry
		 * JSON format for m_db_entry is:
		 * {"chat_id":"", "participants":[""], "messages":[{"msg_id":"", "author_id":"", "text":"", "time":""}]}
		 */
		class database_chat : public messenger::database::database_entry
		{
			private:
				/**
				 * @brief get chat_id from json oject
 				 */
				std::string get_chat_id() const noexcept;
				
			public:
				/**
				 * @brief update chat file for given chat_id in db
				 * stringify poco json object for given chat_id,
				 * call db.update_chat() for writing in db file
				 * @param chat_id	identifier for chat
 				 */
				void update_chat_data(const std::string& chat_id) noexcept;
				
				/**
				 * @brief search user in participants list
				 * @param user_id	identifier for user
				 * @return true	if user_id contains in participants list
				 * @return false otherwise
 				 */
				bool search_participant(const std::string& user_id) noexcept;
				
				/**
				 * @brief add new user in participants list
				 * check if user exist in db and if user doesn't exist in participants list
				 * add user in list, update corresponding chat file in db,
				 * otherwise return status  
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */
				int add_participant(const std::string& user_id) noexcept;
				
				/**
				 * @brief remove user from participants list
				 * check if user exist in db, iterate over participants list,
				 * get user_id index if it exist in list,
				 * remove user from list, update corresponding chat file in db,
				 * otherwise return status  
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */
				int remove_participant(const std::string& user_id) noexcept;
				
				/**
				 * @brief search message in message list
				 * iterate over message list, if msg_id exists return index 
				 * @param msg_id	identifier for message
				 * @return index of msg_id in list, -1 otherwise
 				 */
				int search_message(const std::string& msg_id) noexcept;
				
				/**
				 * @brief add new message in message list
				 * check if msg_id doesn't exist in message list
				 * if so extract message to poco json object and add in message list 
				 * update corresponding chat file in db 
				 * otherwise return status
				 * @param msg_id identifier for msg
				 * @param msg	message
				 * @return 0	if successful
				 * @return -1	otherwise
 				 */
				int add_message(const std::string& msg_id, const std::string& msg) noexcept;
				
				/**
				 * @brief add new message in message list
				 * check if msg_id exist in message list if so remove message from message list
				 * update corresponding chat file in db 
				 * otherwise return status
				 * @param msg_d	identifier for msg
				 * @return 0	if successful
				 * @return -1	otherwise
 				 */
				int remove_message(const std::string& msg_id, const std::string& msg) noexcept;
			
				/**
				 * @brief Def constructor
				 */
			    database_chat() = delete;
			    
				/**
				 * @brief Param constructor
				 * extract string to json object
				 * @param chat_data chat data
				 */		
				database_chat(const std::string& chat_json) noexcept;
				
				/**
				 * @brief Copy constructor
				 */
			    database_chat(const database_chat&) = delete;
			
			    /**
				 * @brief Move constructor
				 */ 
			    database_chat(const database_chat&&) = delete;
			
			    /**
				 * @brief Copy assignment operator
				 */ 
			    database_chat& operator=(const database_chat&) = delete;
			
			    /**
				 * @brief Move assignment operator
				 */ 
			    database_chat& operator=(const database_chat&&) = delete;
			
			    /**
				 * @brief Destructor
				 */ 
			    ~database_chat() noexcept;


		};
	}
}

#endif // MESSENGER_DATABASE_DB_CHAT_HPP
