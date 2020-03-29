/**
 * @file src/db/user_db_handler.cpp
 * @author ITC students
 * @brief user_database_handler class implementation
*/

#include "user_db_handler.hpp"

#include <string>
#include <fstream>
#include <cassert>
#include <experimental/filesystem>

namespace messenger {
	namespace database {

		user_database_handler::user_database_handler() noexcept : m_dirname("db/users"), m_filename("")
		{	
		}
		
		user_database_handler::~user_database_handler() noexcept
		{
		}

		std::string user_database_handler::get_filename() const noexcept
		{
			return m_filename;
		}

		void user_database_handler::set_filename(const std::string& user_id) noexcept
		{
			m_filename = "";
			m_filename.append(m_dirname).append("/").append(user_id).append(".json");
		}

		int user_database_handler::create_user(const std::string& user_id, const std::string& user_data) noexcept
		{
			assert("" != user_id);
			assert("" != user_data);
			set_filename(user_id);
			if (!search_user(user_id)) {
				std::ofstream file;
				file.open(get_filename());
				assert(!file.fail());
				file << user_data;
				file.close();
				assert(!file.fail());
					return 0;
			}
			return -1;
		}
		
		std::string user_database_handler::read_user_data(const std::string& user_id) noexcept
		{
			set_filename(user_id);
			std::ifstream file;
			std::string user_data, temp;
			file.open(get_filename());
			assert(!file.fail());
			while (!file.eof()) { 
				file >> temp;
				user_data.append(temp);
			}
			file.close();
			assert(!file.fail());
			return user_data;
		}
		
		bool user_database_handler::search_user(const std::string& user_id) noexcept
		{
			set_filename(user_id);
			std::experimental::filesystem::recursive_directory_iterator end;
			for (std::experimental::filesystem::recursive_directory_iterator it(m_dirname); it != end; ++it) {
				if (std::experimental::filesystem::is_regular_file(*it) && (it->path() == get_filename())) {
						return true;
				}
			}
			return false;
		}

		void user_database_handler::update_user(const std::string& user_id, const std::string& user_data) noexcept
		{
			set_filename(user_id);
			std::ofstream file;
			file.open(get_filename());
			assert(!file.fail());
			file << user_data;
			file.close();
			assert(!file.fail());
		}

		int user_database_handler::delete_user(const std::string& user_id) noexcept
		{
			set_filename(user_id);
			return remove(get_filename().c_str());
		}
	}
}
