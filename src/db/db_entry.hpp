#ifndef DB_ENTRY
#define DB_ENTRY

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/ParseHandler.h>

#include <iostream>
#include <string>
#include <sstream>

namespace messenger
{

	/**
	* An abstract class specifying common interface for 
	* db entries 
	*/
	class db_entry 
	{
		protected:
			/**
			* JSON object pointer with the db entry.
			*/
			Poco::JSON::Object::Ptr m_db_entry;
		public:
		
		//Helpers
		
			/**
			* Write db_entry obj into provided stringstream 
			*/
			virtual void stringify(std::stringstream& str) const noexcept; 
			
			/**
			* Update in db file 
			*/
			virtual void update_db(const std::string& file_name) const noexcept; 
	};
	
	class db_user : public db_entry 
	{
		public:
			//C-tor
			db_user(const std::string& user_json);
			
			//Accessors
			//void set_f_name(std::string f_name);
			//void set_l_name(std::string l_name);
		
			bool search_contact(const std::string& user_id);
			
			int add_contact(const std::string& user_id);
			
			int remove_contact(const std::string& user_id);
		
			bool search_chat(const std::string& chat_id);
			
			int add_chat(const std::string& chat_id);
		
			int remove_chat(const std::string& chat_id);
	};
	
	class db_chat : public db_entry
	{
		public:
			//C-tor
			db_chat(const std::string& chat_json);
			
			//Accessors
			//void set_f_name(std::string f_name);
			//void set_l_name(std::string l_name);
			
			bool search_participant(const std::string& user_id);
			
			int add_participant(const std::string& user_id);
			
			int remove_participant(const std::string& user_id);
			
			int search_message(const std::string& msg_id);
		
			int add_message(const std::string& msg);
			
			int remove_message(const std::string& msg);
		
	//		void add_chat(const std::string& chat_id);
		
	//		void remove_chat(const std_string& chat_id);
	};

}
#endif //DB_ENTRY
