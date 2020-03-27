#include "db_chat.hpp"
#include "db_entry.hpp"
#include "chat_db_handler.hpp"
#include "user_db_handler.hpp"


#include <string>
#include <sstream>
#include <cassert>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/ParseHandler.h>

namespace messenger {
	namespace database {

		database_chat::database_chat(const std::string& chat_data) noexcept
		{
			Poco::JSON::Parser parser;
			Poco::Dynamic::Var result = parser.parse(chat_data);
			m_db_entry = result.extract<Poco::JSON::Object::Ptr>();
			assert(m_db_entry);
		}

		database_chat::~database_chat() noexcept
		{
		}
		
		std::string database_chat::get_chat_id() const noexcept
		{
			std::string chat_id = m_db_entry->getValue<std::string>("chat_id");	
			assert("" != chat_id);
			return chat_id;
		}

		void database_chat::update_chat_data(const std::string& chat_id) noexcept
		{
			messenger::database::chat_database_handler db;
			std::stringstream chat_data;
			stringify(chat_data);
			db.update_chat(get_chat_id(), chat_data.str());
		}

		bool database_chat::search_participant(const std::string& user_id) noexcept
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
		
		int database_chat::add_participant(const std::string& user_id) noexcept
		{
			messenger::database::user_database_handler db;
			if (db.search_user(user_id)) {			

				Poco::JSON::Array::Ptr participants = m_db_entry->getArray("participants");
				assert(participants);
				if (!search_participant(user_id)) {
					participants->add(user_id);
					update_chat_data(get_chat_id());
					return 0;
				}
			}
			return -1;
		}
		
		int database_chat::remove_participant(const std::string& user_id) noexcept
		{
			messenger::database::user_database_handler db;
			if (db.search_user(user_id)) {	

				Poco::JSON::Array::Ptr participants = m_db_entry->getArray("participants");
				assert(participants);
				for (int i = 0; i < participants->size(); ++i) {
					if (participants->get(i) == user_id) {
						participants->remove(i);
						update_chat_data(get_chat_id());
						return 0;
					}
				}
			}
			return -1;
		}
		
		int database_chat::search_message(const std::string& msg_id) noexcept
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
		
		int database_chat::add_message(const std::string& msg_id, const std::string& msg) noexcept
		{	
			Poco::JSON::Parser parser;
			Poco::Dynamic::Var result = parser.parse(msg);
			Poco::JSON::Object::Ptr msg_obj = result.extract<Poco::JSON::Object::Ptr>();
			assert(msg_obj);
			Poco::JSON::Array::Ptr messages = m_db_entry->getArray("messages");
			assert(messages);
			int index = search_message(msg_id);
			if (-1 == search_message(msg_id)) {
				messages->add(msg_obj);
				update_chat_data(get_chat_id());
				return 0;
			}
			return -1;
		}
		
		int database_chat::remove_message(const std::string& msg_id, const std::string& msg) noexcept
		{
			Poco::JSON::Array::Ptr messages = m_db_entry->getArray("messages");
			assert(messages);
			
			int index = search_message(msg_id);
			if (-1 != index) {
				messages->remove(index);
				update_chat_data(get_chat_id());
				return 0;
			}
			return -1;
		}
	}
}
