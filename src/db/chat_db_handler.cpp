/**
 * @file src/db/chat_db_handler.cpp
 * @author ITC students
 * @brief chat_database_handler class implementation
*/

#include "chat_db_handler.hpp"

#include <string>
#include <fstream>
#include <cassert>
#include <experimental/filesystem>

namespace messenger {
	namespace database {

		chat_database_handler::chat_database_handler() noexcept : m_dirname("db/chats"), m_filename("")
		{
		}
		
		chat_database_handler::~chat_database_handler() noexcept
		{
		}
		
		std::string chat_database_handler::get_filename() const noexcept
		{
			return m_filename;
		}

		void chat_database_handler::set_filename(const std::string& chat_id) noexcept
		{
			m_filename = "";
			m_filename.append(m_dirname).append("/").append(chat_id).append(".json");
		}

		int chat_database_handler::create_chat(const std::string& chat_id, const std::string& chat_name) noexcept
		{
			assert("" != chat_id);
			set_filename(chat_id);
			if (!search_chat(chat_id)) {
				std::ofstream file;
				file.open(get_filename());
				assert(!file.fail());
				file << chat_name;
				file.close();
				assert(!file.fail());
				return 0;
			}
			return -1;
		}
		
		std::string chat_database_handler::read_chat_data(const std::string& chat_id) noexcept
		{
			set_filename(chat_id);
			std::ifstream file;
			std::string chat_data, temp;
			file.open(get_filename());
			assert(!file.fail());
			while (!file.eof()) { 
				file >> temp;
				chat_data.append(temp);
			}
			file.close();
			assert(!file.fail());
			return chat_data;
		}
		
		bool chat_database_handler::search_chat(const std::string& chat_id) noexcept
		{
			std::string file_name1 = chat_id;
			std::string file_name2 = "";
			std::string temp = "";
			for (std::string::const_iterator it = chat_id.begin(); it != chat_id.end(); ++it) {
				if ('_' == *it) {					
					file_name2.append(++it, chat_id.end());
					break;
				} else {
					temp += *it;
				}
			}
			file_name1.append(".json");
			file_name2.append("_").append(temp).append(".json");
			std::experimental::filesystem::recursive_directory_iterator end;
			for (std::experimental::filesystem::recursive_directory_iterator it(m_dirname); it != end; ++it) {
				if (std::experimental::filesystem::is_regular_file(*it)) {
					if ((it->path().filename() == file_name1)) {
						file_name1.assign(file_name1.begin(), file_name1.end()-5);
						set_filename(file_name1);
						return true;
					} else	if (it->path().filename() == file_name2) {
						file_name2.assign(file_name2.begin(), file_name2.end()-5);
						set_filename(file_name2);
						return true;
					}
				}
			}
			return false;
		}

		void chat_database_handler::update_chat(const std::string& chat_id, const std::string& chat_data) noexcept
		{
			set_filename(chat_id);
			std::ofstream file;
			file.open(get_filename());
			assert(!file.fail());
			file << chat_data;
			file.close();
			assert(!file.fail());
		}

		int chat_database_handler::delete_chat(const std::string& chat_id) noexcept
		{
			set_filename(chat_id);
			return remove(get_filename().c_str());
		}
	}
}
