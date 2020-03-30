/**
 * @file json_parser.cpp
 * @brief Implementation for the Json Parser library
 * @author ITC students
 * Instigate Training Center Foundation, Yerevan, 2020
 * @details This library is parsing the ".txt" format file to ".json" format
 * @todo Returns the given key value.
 */

// includes from this project
#include "json_parser.hpp"

// includes from PoCo library
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// includes from C++ library
#include <iostream>
#include <fstream>
#include <string>

// includes from c library
#include <cassert>

namespace messenger {
	namespace parser {

		/// @brief This method is reading string row
		/// @param [in] row contains row of string
		bool
		file_reader::
		read_row(std::string& row) noexcept
		{
			return (m_fread >> row ? true : false);
		}

		/// @details This constructor has initialazer list
		///			 and initialazing the file name
		/// 		 then opens the file and
		/// 		 prepares it for reading string row
		file_reader::
		file_reader(const std::string& name) : m_name(name)
		{
			m_fread.open(m_name, std::ios::in);
			assert(m_fread.is_open() && "Can't read, file opening failure!!!");
		}

		/// @brief The destructor closes the file after
		/// 	   reading and not any throwing exception
		file_reader::
		~file_reader() noexcept
		{
			m_fread.close();
		}

		/// @brief This method is writing symbols such as "\n etc."
		/// @param [out] symbol which is used as end of line
		bool
		file_writer::
		write_symbol(char symbol) noexcept
		{
			return (m_fwrite << symbol ? true : false);
		}

		/// @brief This method is writing json to file
		/// @param [out] json contains row of json
		bool
		file_writer::
		write_json(std::string& json) noexcept
		{
			return (m_fwrite << json ? true : false);
		}

		/// @details This constructor has initialazer list
		/// 		 and initialazing the file name
		/// 		 then opens the file and
		/// 		 prepares it for writing json row
		file_writer::
		file_writer(const std::string& name) : m_name(name)
		{
			m_fwrite.open(m_name, std::ios::app);
			assert(m_fwrite.is_open() && "Can't write, file opening failure!!!");
		}

		/// @brief The destructor closes the file after
		/// 	   writing and not throwing any exception
		file_writer::
		~file_writer() noexcept
		{
			m_fwrite.close();
		}

		/// @brief This function is writing to file
		/// @param [in] w opens file for writing
		/// @param [in] file reads and writs to file
		/// @param [out] json_format written file
		/// @return true if read successful or false if not
		bool
		read_write_to_file(file_writer& w, std::string file,
						   std::string& json_format) noexcept
		{
			/// @brief opening ".txt" file for reading
			file_reader f("../../txt_files/file.txt");
			/// @brief reading from ".txt" while true 
			while(f.read_row(file)) {//read_from_file(f, file)) {
				/// @brief writing to ".json" file
				w.write_json(file);
				json_format = file;
				/// @brief puts the end of line in file
				w.write_symbol('\n');
			}
			return true;
		}

		/// @brief This function is parsing from ".txt" to ".json" format
		/// @param [in] json_object_value tackes the argument by reference
		///				and extracts the json object for further use
		void
		parsing_from_txt_to_json(Poco::JSON::Object::Ptr& json_object_value) noexcept
		{
			std::string file;
			std::string json_file;
			Poco::JSON::Parser parse_from;

			/// @brief file_writer class prepares the file for writing
			messenger::parser::file_writer w("../../json_files/w_file.json");
			/// @brief read_write_to_file reading for ".txt" file and
			///		   writing to ".json" file at the same time
			/// @param [in] w the file where to write
			/// @param [in] file the read row
			/// @param [out] json_file written row to file
			messenger::parser::read_write_to_file(w, file, json_file);
			/// @brief parsing to json and get the results
			Poco::Dynamic::Var parsing_to_json = parse_from.parse(json_file);
			Poco::Dynamic::Var parsed_json_result = parse_from.result();

			/// @brief exception ot json object
			json_object_value = parsed_json_result.extract<Poco::JSON::Object::Ptr>();
		}

		/// @brief This function takes the key and returns it's value
		/// @param [in] key_from_json the key in file
		/// @param [out] json_object_value the value of given key
		/// @return string after converting from Poco::Dynamic::Var
		std::string
		get_value(std::string key_from_json,
				  Poco::JSON::Object::Ptr& json_object_value) noexcept
		{
			Poco::Dynamic::Var variable;
			/// @brief getting the value of given key
			variable = json_object_value->get(key_from_json);
			/// @brief converting the value to string
			return variable.convert<std::string>();
		}

	} // namespace parser
} // namespace messenger
