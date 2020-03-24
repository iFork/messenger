/**
 * @file src/db/db.cpp
 * @brief database class implementation
*/

#include "db.hpp"

//#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <experimental/filesystem>

namespace messenger 
{
	database::database() noexcept : m_dirname("db")
	{	
	}
	
	database::~database() noexcept
	{
	}
	
	void database::create_user(const std::string& filename, const std::string& username) 
	{
		std::string path;
		path.append(m_dirname).append("/").append(filename);
		std::ofstream file;
		file.open(path);
		assert(!file.fail());
		file << username;
		file.close();
		assert(!file.fail());
	}
	
	std::string database::read_user_data(const std::string& filename) 
	{
		std::string path;
		path.append(m_dirname).append("/").append(filename);
		std::ifstream file;
		std::string user_data, temp;
		file.open(path);
		assert(!file.fail());
		while (!file.eof()) { 
			file >> temp;
			user_data.append(temp);
		}
		file.close();
		assert(!file.fail());
		return user_data;
	}
	
	bool database::search_user(const std::string& filename)
	{
		std::experimental::filesystem::recursive_directory_iterator end;
		for (std::experimental::filesystem::recursive_directory_iterator it(m_dirname); it != end; ++it) {
			if (std::experimental::filesystem::is_regular_file(*it) && (it->path().filename() == filename)) {
					return true;
			}
		}
		return false;
	}

	void database::update_user(const std::string& filename, const std::string& user_data)
	{
		std::string path;
		path.append(m_dirname).append("/").append(filename);
		std::ofstream file;
		file.open(path);
		assert(!file.fail());
		file << user_data;
		file.close();
		assert(!file.fail());
	}

	int database::delete_user(const std::string& filename) 
	{
		std::string path;
		path.append(m_dirname).append("/").append(filename);
		if (remove(path.c_str()))
			return 0;
		return 1;
	}
}
