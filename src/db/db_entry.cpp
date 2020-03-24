#include "db_entry.hpp"
#include "db.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

namespace messenger
{

	//Implementation of db_entry
	//Helper Implementation
	void db_entry::stringify(std::stringstream& sstr) const noexcept
	{
		m_db_entry->stringify(sstr, 4);
	}

	void db_entry::update_db(const std::string& file_name) const noexcept
	{
		messenger::database db;
		std::stringstream user_info;
		stringify(user_info);
		db.update_user(file_name, user_info.str());
	}


	//Implementation of db_user
	//TODO: check Doxygen inclusion
	/**
	* @class db_user
	* @var m_db_entry
	* JSON format for m_db_entry is:
	* {"user_id":"", "user_file":"", "f_name":"", "l_name":"",
	* "contacts":[""], "chats":[""] }
	*/
	db_user::db_user(const std::string& user_json)
	{
	
		//validate that user_json follows our API format and put in m_command
		// or assert here and validate externally ?-  static validate() func
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var result = parser.parse(user_json); //using default ParseHandler
		m_db_entry = result.extract<Poco::JSON::Object::Ptr>();
		assert(m_db_entry);
	}
	
	bool db_user::search_contact(const std::string& user_id)
	{
		Poco::JSON::Array::Ptr contacts = m_db_entry->getArray("contacts");
		assert(contacts);
		for (Poco::JSON::Array::ConstIterator it = contacts->begin(); it != contacts->end(); ++it) {
			if (it->convert<std::string>() == user_id) {
				return true;					
			}
		}
		return false;
	}
	
	int db_user::add_contact(const std::string& user_id)
	{
		std::string file_name = m_db_entry->getValue<std::string>("user_file");
		//check if exists user or not 
		//necessary user_file for user_id 
		//db.search_user(file_name, user_id);
		
		Poco::JSON::Array::Ptr contacts = m_db_entry->getArray("contacts");
		assert(contacts);
		if (!search_contact(user_id)) {
			contacts->add(user_id);
			update_db(file_name);
			return 0;
		}
		return -1;
	}
	
	int db_user::remove_contact(const std::string& user_id)
	{
		std::string file_name = m_db_entry->getValue<std::string>("user_file");
		//check if exists user or not 
		//user_id ? user_file
		//db.search_user(file_name, user_info.str());
		
		Poco::JSON::Array::Ptr contacts = m_db_entry->getArray("contacts");
		assert(contacts);
		for (int i = 0; i < contacts->size(); ++i) {
			if (contacts->get(i) == user_id) {
				contacts->remove(i);
				update_db(file_name);
				return 0;
			}
		}
		return -1;
	}
	
	bool db_user::search_chat(const std::string& chat_id)
	{
		Poco::JSON::Array::Ptr chats = m_db_entry->getArray("chats");
		assert(chats);
		for (Poco::JSON::Array::ConstIterator it = chats->begin(); it != chats->end(); ++it) {
			if (it->convert<std::string>() == chat_id) {
				return true;					
			}
		}
		return false;
	}
	
	int db_user::add_chat(const std::string& chat_id)
	{
		std::string file_name = m_db_entry->getValue<std::string>("user_file");
		
		Poco::JSON::Array::Ptr chats = m_db_entry->getArray("chats");
		assert(chats);
		if (!search_chat(chat_id)) {
			chats->add(chat_id);
			update_db(file_name);
			return 0;
		}
		return -1;
	}
	
	int db_user::remove_chat(const std::string& chat_id)
	{
		std::string file_name = m_db_entry->getValue<std::string>("user_file");
		
		Poco::JSON::Array::Ptr chats = m_db_entry->getArray("chats");
		assert(chats);
		for (int i = 0; i < chats->size(); ++i) {
			if (chats->get(i) == chat_id) {
				chats->remove(i);
				update_db(file_name);
				return 0;
			}
		}
		return -1;
	}
	
	//Implementation of db_chat
	//TODO: check Doxygen inclusion
	/**
	* @class db_chat
	* @var m_db_entry
	* JSON format for m_db_entry is:
	* {"chat_id":"", "participants":[""], 
	* "messages":[{"msg_id":"", "author_id":"", "text":"", "time":""}]}
	*/
	db_chat::db_chat(const std::string& chat_json)
	{
	
		//validate that user_json follows our API format and put in m_command
		// or assert here and validate externally ?-  static validate() func
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var result = parser.parse(chat_json); //using default ParseHandler
		m_db_entry = result.extract<Poco::JSON::Object::Ptr>();
		assert(m_db_entry);
	}
	
	bool db_chat::search_participant(const std::string& user_id)
	{
		Poco::JSON::Array::Ptr participants = m_db_entry->getArray("participants");
		assert(participants);

		for (Poco::JSON::Array::ConstIterator it = participants->begin(); it != participants->end(); ++it) {
			if (it->convert<std::string>() == user_id) {
				return true;					
			}
		}
		return false;
	}
	
	int db_chat::add_participant(const std::string& user_id)
	{
		std::string file_name = m_db_entry->getValue<std::string>("chat_file");
		//check if exists user or not 
		//necessary user_file for user_id 
		//db.search_user(file_name, user_id);
		
		Poco::JSON::Array::Ptr participants = m_db_entry->getArray("participants");
		assert(participants);
		if (!search_participant(user_id)) {
			participants->add(user_id);
			update_db(file_name);
			return 0;
		}
		return -1;
	}
	
	int db_chat::remove_participant(const std::string& user_id)
	{
		std::string file_name = m_db_entry->getValue<std::string>("chat_file");
		//check if exists user or not 
		//user_id ? user_file
		//db.search_user(file_name, user_info.str());
		
		Poco::JSON::Array::Ptr participants = m_db_entry->getArray("participants");
		assert(participants);
		for (int i = 0; i < participants->size(); ++i) {
			if (participants->get(i) == user_id) {
				participants->remove(i);
				update_db(file_name);
				return 0;
			}
		}
		return -1;
	}
	
	int db_chat::search_message(const std::string& msg_id)
	{	
		Poco::JSON::Array::Ptr messages = m_db_entry->getArray("messages");
		assert(messages);
		
		for (int i = 0; i < messages->size(); ++i) {
			Poco::JSON::Object::Ptr msg_obj = messages->getObject(i);
			assert(msg_obj);
			Poco::Dynamic::Var msg = msg_obj->get("msg_id");
			
			if (msg.toString() == msg_id) {
				return i;					
			}
		}
		return -1;
	}
	
	int db_chat::add_message(const std::string& msg)
	{
		std::string file_name = m_db_entry->getValue<std::string>("chat_file");
		//check if exists user or not 
		//necessary user_file for user_id 
		//db.search_user(file_name, user_id);
	
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var result = parser.parse(msg); //using default ParseHandler
		Poco::JSON::Object::Ptr msg_obj = result.extract<Poco::JSON::Object::Ptr>();
		assert(msg_obj);
		std::string msg_id = msg_obj->getValue<std::string>("msg_id");
			
		Poco::JSON::Array::Ptr messages = m_db_entry->getArray("messages");
		assert(messages);
		int index = search_message(msg_id);
		if (-1 == search_message(msg_id)) {
			messages->add(msg_obj);
			update_db(file_name);
			return 0;
		}
		return -1;
	}
	
	int db_chat::remove_message(const std::string& msg)
	{
		std::string file_name = m_db_entry->getValue<std::string>("chat_file");
		//check if exists user or not 
		//user_id ? user_file
		//db.search_user(file_name, user_info.str());
		
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var result = parser.parse(msg); //using default ParseHandler
		Poco::JSON::Object::Ptr msg_obj = result.extract<Poco::JSON::Object::Ptr>();
		assert(msg_obj);
		std::string msg_id = msg_obj->getValue<std::string>("msg_id");
		
		Poco::JSON::Array::Ptr messages = m_db_entry->getArray("messages");
		assert(messages);
		
		int index = search_message(msg_id);
		if (-1 != index) {
			messages->remove(index);
			update_db(file_name);
			return 0;
		}
		return -1;
	}
}
