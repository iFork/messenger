#include "db_user.hpp"
#include "db_entry.hpp"
#include "user_db_handler.hpp"
#include "chat_db_handler.hpp"

#include <string>
#include <sstream>
#include <cassert>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/ParseHandler.h>

namespace messenger {
	namespace database {
		
		database_user::database_user(const std::string& user_data) noexcept
		{
			Poco::JSON::Parser parser;
			Poco::Dynamic::Var result = parser.parse(user_data);
			m_db_entry = result.extract<Poco::JSON::Object::Ptr>();
			assert(m_db_entry);
		}
		
		database_user::~database_user() noexcept
		{
		}

		std::string database_user::get_user_id() const noexcept
		{
			std::string user_id = m_db_entry->getValue<std::string>("user_id");	
			assert("" != user_id);
			return user_id;
		}

		std::string database_user::get_chat_id(const std::string& user_id1, const std::string& user_id2) const noexcept
		{
			assert("" != user_id1);
			assert("" != user_id2);
			std::string chat_id = user_id1;
			chat_id.append("_").append(user_id2);
			assert("" != chat_id);
			return chat_id;
		}

		void database_user::update_user_data(const std::string& user_id) noexcept
		{
			messenger::database::user_database_handler db;
			std::stringstream user_data;
			stringify(user_data);
			db.update_user(get_user_id(), user_data.str());

		}

		bool database_user::search_contact(const std::string& user_id) noexcept
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
		
		int database_user::add_contact_helper(const std::string& user_id) noexcept
		{
			Poco::JSON::Array::Ptr contacts = m_db_entry->getArray("contacts");
			assert(contacts);
			//if user_id doesn't exist in contact list and user don't add self id
			if (!search_contact(user_id) && (get_user_id() != user_id)) {
				contacts->add(user_id);
				return 0;
			}
			return -1;
		}


		int database_user::add_contact(const std::string& user_id) noexcept
		{
			//check if user exists in db or not 
			messenger::database::user_database_handler db;
			if (db.search_user(user_id)) {
				if ((-1 != add_contact_helper(user_id)) && (-1 != add_chat(get_chat_id(get_user_id(), user_id)))) {
					update_user_data(get_user_id());
					std::string obj_user_id = get_user_id();

					Poco::JSON::Object::Ptr db_entry = m_db_entry;
					Poco::JSON::Parser parser;
					Poco::Dynamic::Var result = parser.parse(db.read_user_data(user_id)); //using default ParseHandler
					m_db_entry = result.extract<Poco::JSON::Object::Ptr>();
					if ((-1 != add_contact_helper(obj_user_id)) && (-1 != add_chat(get_chat_id(get_user_id(), obj_user_id)))) {
						update_user_data(get_user_id());
						
						m_db_entry = db_entry;
						return 0;
					}
				}
			}
			return -1;
		}
		
		int database_user::remove_contact_helper(const std::string& user_id) noexcept
		{
			Poco::JSON::Array::Ptr contacts = m_db_entry->getArray("contacts");
			assert(contacts);
			for (int i = 0; i < contacts->size(); ++i) {
				if (contacts->get(i) == user_id) {
					contacts->remove(i);
					return 0;
				}
			}
			return -1;
		}

		int database_user::remove_contact(const std::string& user_id) noexcept
		{
			//check if user exists in db or not 
			messenger::database::user_database_handler db;
			if (db.search_user(user_id)) {
				if ((-1 != remove_contact_helper(user_id)) && (-1 != remove_chat(get_chat_id(get_user_id(), user_id)))) {
					update_user_data(get_user_id());

					std::string obj_user_id = get_user_id();
				
					Poco::JSON::Object::Ptr db_entry = m_db_entry;
					Poco::JSON::Parser parser;
					Poco::Dynamic::Var result = parser.parse(db.read_user_data(user_id)); //using default ParseHandler
					m_db_entry = result.extract<Poco::JSON::Object::Ptr>();

					if ((-1 != remove_contact_helper(obj_user_id)) && (-1 != remove_chat(get_chat_id(get_user_id(), obj_user_id)))) {
						update_user_data(get_user_id());

						m_db_entry = db_entry;
						return 0;
					}
				}
			}
			return -1;
		}
		
		bool database_user::search_chat(const std::string& chat_id) noexcept
		{
			std::string new_id = "";
			std::string temp = "";
			for (std::string::const_iterator it = chat_id.begin(); it != chat_id.end(); ++it) {
				if ('_' == *it) {					
					new_id.append(++it, chat_id.end());
					break;
				} else {
					temp += *it;
				}
			}
			new_id.append("_").append(temp);
			
			Poco::JSON::Array::Ptr chats = m_db_entry->getArray("chats");
			assert(chats);	
			for (Poco::JSON::Array::ConstIterator it = chats->begin(); it != chats->end(); ++it) {
				if (it->convert<std::string>() == chat_id || it->convert<std::string>() == new_id) {
					return true;					
				}
			}
			return false;
		}
		
		int database_user::add_chat_helper(const std::string& chat_id) noexcept
		{
			Poco::JSON::Array::Ptr chats = m_db_entry->getArray("chats");
			assert(chats);
			if (!search_chat(chat_id)) {
				chats->add(chat_id);
				return 0;
			}
			return -1;
		}

		std::string database_user::create_chat_json(const std::string& chat_id) noexcept
		{
			Poco::JSON::Object::Ptr chat_obj = new Poco::JSON::Object();
			chat_obj->set("chat_id", chat_id);
			Poco::JSON::Array participants = Poco::JSON::Array();
			Poco::JSON::Array messages = Poco::JSON::Array();
			chat_obj->set("participants", participants);
			chat_obj->set("messages", messages);
			std::stringstream chat;
			chat_obj->stringify(chat, 4);
			return chat.str();
		}

		int database_user::add_chat(const std::string& chat_id) noexcept
		{
			//add chat in db
			messenger::database::chat_database_handler db;
			if (!db.search_chat(chat_id)) {
				std::string chat = create_chat_json(chat_id);
				if (-1 != db.create_chat(chat_id, chat)) {
					if (-1 != add_chat_helper(chat_id)) {
						update_user_data(get_user_id());
						return 0;
					}
				}
			} else {
				if (-1 != add_chat_helper(chat_id)) {
					update_user_data(get_user_id());
					return 0;
				}
			}
			return -1;			
		}	

		int database_user::remove_chat_helper(const std::string& chat_id) noexcept
		{
			Poco::JSON::Array::Ptr chats = m_db_entry->getArray("chats");
			assert(chats);
			for (int i = 0; i < chats->size(); ++i) {
				if (chats->get(i) == chat_id) {
					chats->remove(i);
					return 0;
				}
			}
			return -1;
		}

		int database_user::remove_chat(const std::string& chat_id) noexcept
		{
			//remove chat in db
			messenger::database::chat_database_handler db;
			if (!db.search_chat(chat_id)) {
				if (-1 != db.delete_chat(chat_id)) {
					if (-1 != remove_chat_helper(chat_id)) {
						update_user_data(get_user_id());
						return 0;
					}
				}
			} else {
				if (-1 != remove_chat_helper(chat_id)) {
					update_user_data(get_user_id());
					return 0;
				}
			}
			return -1;	
		}
	}
}
