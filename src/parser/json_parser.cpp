/**
 * @file json_parser.hpp
 * @brief Common declaration for the Json Parser library
 * @author Vardan Vardanyan
 * @copy Instigate Training Center Foundation, Yerevan, 2020
 * @details This library is parsing the ".txt" format file to ".json" format
 * @todo Returns the given key value.
 */

// includes from this project
#include "json_parser.hpp"

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

File_reader::File_reader(const std::string& name) : m_name(name)
{
	m_fread.open(m_name, std::ios::in);
	assert(m_fread.is_open() && "Can't read, file opening failure!!!");
}
bool File_reader::read_key_value(std::string& key_value)
{
	assert(m_fread && "Reading failure");
	return (m_fread >> key_value ? true : false);
}
File_reader::~File_reader() noexcept
{
	m_fread.close();
}

File_writer::File_writer(const std::string& name) : m_name(name)
{
	m_fwrite.open(m_name, std::ios::app);
	assert(m_fwrite.is_open() && "Can't write, file opening failure!!!");
}
bool File_writer::write_symbol(char symbol)
{
	assert(m_fwrite && "Writing failure");
	return (m_fwrite << symbol ? true : false);
}
bool File_writer::write_string(std::string& string)
{
	assert(m_fwrite && "Writing failure");
	return (m_fwrite << string ? true : false);
}
File_writer::~File_writer() noexcept
{
	m_fwrite.close();
}

std::string get_value(Object::Ptr json_object, const char* key_from_json) {
	//insted of writing Poco::Dynamic::Var used Var
	//
	Var variable;
	std::string key(key_from_json);
	// Get the member Variable
	//
	variable = json_object->get(key);
	// Returns the Value from the Variable
	//
	return variable.convert<std::string>();
}

bool file_reader(File_reader& f, std::string& file) {
	return f.read_key_value(file) ? true : false;
}

bool file_writer(File_writer& w, std::string& file, std::string& json_format) {
	File_reader f("./txt_files/file.txt");
	while(file_reader(f, file)) {
		w.write_string(file);
		json_format = file;
		w.write_symbol('\n');
	}
	return true;
}

void print_after_pars(std::string& json_file, Object::Ptr& json_object_value) {
	std::cout << json_file << std::endl;
	std::cout << std::endl;
	std::cout << "user_id : " << get_value(json_object_value, "user_id")
			  << std::endl;
	std::cout << "user_name : " << get_value(json_object_value, "user_name")
			  << std::endl;
	std::cout << "password : " << get_value(json_object_value, "password")
			  << std::endl;
	std::cout << "conversation_id : " << get_value(json_object_value, "conversation_id")
			  << std::endl;
	std::cout << "group_id : " << get_value(json_object_value, "group_id")
			  << std::endl;
}
