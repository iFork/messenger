#ifndef __JSON_PARSER_HPP__
#define __JSON_PARSER_HPP__

/**
 * @file json_parser.hpp
 * @brief Common declaration for the Json Parser library
 * @author Vardan Vardanyan
 * @copy Instigate Training Center Foundation, Yerevan, 2020
 * @details This library is parsing the ".txt" format file to ".json" format
 * @todo Returns the given key value.
 */

// includes from PoCo library
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// includes from C++ library
#include <iostream>
#include <fstream>
#include <string>

// includes from c library
#include <cassert>

using namespace Poco::JSON;
using namespace Poco::Dynamic;

/// This struct is reading from given ".txt" file
struct File_reader {
	/// @name Special Members
	private:
		std::ifstream m_fread;
		const std::string m_name;
	/// @name Special Member Functions
	public:
		/// @name This constructor has initialazer list
		/// @name and initialazing the file name
		File_reader(const std::string& _name);
		/// @name This method is reading string row
		bool read_key_value(std::string& key_value);
		/// @name The destructor closes the readen file
		/// @name and has option "noexcept"
		~File_reader();
};

/// This struct is writing to given ".json" file
struct File_writer {
	/// @name Special Members
	private:
		std::ofstream m_fwrite;
		const std::string m_name;
	/// @name Special Member Functions
	public:
		/// @name This constructor has initialazer list
		/// @name and initialazing the file name
		File_writer(const std::string& name);
		/// @name This method is writing char symbols such as "\n t.c"
		bool write_symbol(char symbol);
		/// @name This method is writing string row
		bool write_string(std::string& string);
		/// @name The destructor closes the written file
		/// @name and has option "noexcept"
		~File_writer();
};
/// @name This function takes the key and returns it's value
std::string get_value(Object::Ptr json_object, const char* key_from_json);
/// @name This function is reading from file
bool file_reader(File_reader& f, std::string& file);
/// @name This function is writing to file
bool file_writer(File_writer& w, std::string& file, std::string& json_format);
/// @name This function is printing the parser result
void print_after_pars(std::string& json_file, Object::Ptr& json_object_value);

#endif // __JSON_PARSER_HPP__ json_parser.cpp
