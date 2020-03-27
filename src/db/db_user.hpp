#ifndef MESSENGER_DATABASE_DB_USER_HPP
#define MESSENGER_DATABASE_DB_USER_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

/**
 * @file src/db/db_user.hpp
 * @author ITC students
 * @brief database_user class definition
*/

#include "db_entry.hpp"

#include <string>

namespace messenger {
	namespace database {

		/**
		* @class database_user
		* @var m_db_entry
		* JSON format for m_db_entry is:
		* {"user_id":"", "user_file":"", "f_name":"", "l_name":"",
		* "contacts":[""], "chats":[""] }
		*/
		class database_user : public messenger::database::database_entry 
		{
			private:
				
				/**
				 * @brief get chat_id from json oject
 				 */
				std::string get_user_id() const noexcept;
				
				/**
				 * @brief  create chat_id from given user_id
				 * @param user_id1 identifer for user
				 * @param user_id2 identifer for user
				 * @return string containing concatenation of user_ids user_id1_user_id2
 				 */
				std::string get_chat_id(const std::string& user_id1, const std::string& user_id2) const noexcept;

				/**
				 * @brief helper function for add contact in contact list
				 * check if user doesn't exists in contact list	
				 * if so add user in list
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */
				int add_contact_helper(const std::string& user_id) noexcept;
				
				/**
				 * @brief helper function for remove contact from contact list
				 * check if user exists in contact list
				 * if so remove user from list
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */
				int remove_contact_helper(const std::string& user_id) noexcept;
				
				/**
				 * @brief helper function for add chat in chat list
				 * check if chat doesn't exists in chat list	
				 * if so add chat in list
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */
				int add_chat_helper(const std::string& chat_id) noexcept;

				/**
				 * @brief helper function for remove chat from chat list
				 * check if user exists in chat list
				 * if so remove user from list
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */
				int remove_chat_helper(const std::string& chat_id) noexcept;

				/**
				 * @brief helper function for add chat in chat list
				 * create poco json object for chat_id
				 * stringify poco json object
				 * @param user_id	identifier for user
				 * @return string	containing stringified string
 				 */
				std::string create_chat_json(const std::string& chat_id) noexcept;

			public:

				/**
				 * @brief update data file for given user_id in db
				 * stringify poco json object for given user_id,
				 * call db.update_user() for writing in db file
				 * @param user_id	identifier for user
 				 */
				void update_user_data(const std::string& user_id) noexcept;
		
				/**
				 * @brief search user in contact list
				 * @param user_id	identifier for user
				 * @return true	if user_id contains in contact list
				 * @return false otherwise
 				 */
				bool search_contact(const std::string& user_id) noexcept;
				
				/**
				 * @brief add new user in contact list
				 * check if user exist in db if so call helper function for adding user in contact list and
				 * call add_chat function adding chat_id for users chat in chat list
				 * update corresponding user file in db
				 * repeat above steps adding user in contact and chat lists of given user
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */
				int add_contact(const std::string& user_id) noexcept;
				
				/**
				 * @brief remove user from contact list
				 * check if user exist in db if so call helper function for removing user from contact list and
				 * call remove_chat function removing chat_id for users chat in chat list
				 * update corresponding user file in db
				 * repeat above steps remove user from contact and chat lists of given user
				 * @param user_id	identifier for user
				 * @return status   0 successful, -1 otherwise
 				 */				
				int remove_contact(const std::string& user_id) noexcept;
			
				/**
				 * @brief search chat in chat list
				 * get new chat id from given chat_id   chat_id = id1_id2  new_chat_id = id2_id1  
				 * check if one of chat_id exist in chat list and
				 * @param chat_id	identifier for chat
				 * @return true	if one of ids exists, false otherwise 
 				 */	
				bool search_chat(const std::string& chat_id) noexcept;
				
				/**
				 * @brief add new chat in chat list
				 * check if chat exist in db if so call helper function for adding chat in chat list
				 * update corresponding user file in db
				 * repeat above steps adding chat in chat list of given user
				 * otherwise create chat in db and add in chat list
				 * @param chat_id	identifier for chat
				 * @return status   0 successful, -1 otherwise
 				 */
				int add_chat(const std::string& chat_id) noexcept;
			
				/**
				 * @brief remove chat in chat list
				 * check if chat exist in db if so call helper function for removing chat in chat list
				 * update corresponding user file in db
				 * repeat above steps removing chat in chat list of given user
				 * otherwise only remove from chat list
				 * @param chat_id	identifier for chat
				 * @return status   0 successful, -1 otherwise
 				 */
				int remove_chat(const std::string& chat_id) noexcept;

				/**
				 * @brief Def constructor
				 */
			    database_user() = delete;

			    /**
				 * @brief Param constructor
				 * extract string to json object
				 * @param user_data user data
				 */		
				database_user(const std::string& user_data) noexcept;
				
				/**
				 * @brief Copy constructor
				 */
			    database_user(const database_user&) = delete;
			
			    /**
				 * @brief Move constructor
				 */ 
			    database_user(const database_user&&) = delete;
			
			    /**
				 * @brief Copy assignment operator
				 */ 
			    database_user& operator=(const database_user&) = delete;
			
			    /**
				 * @brief Move assignment operator
				 */ 
			    database_user& operator=(const database_user&&) = delete;
			
			    /**
				 * @brief Destructor
				 */ 
			    ~database_user() noexcept;
		};
	}
}

#endif // MESSENGER_DATABASE_DB_USER_HPP
