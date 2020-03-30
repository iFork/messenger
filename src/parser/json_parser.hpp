/**
 * @file json_parser.hpp "json_parser.hpp"
 * @brief Common declaration for the Json Parser library
 * @details This library is parsing the ".txt" format file to ".json" format
 * 			and returns the value of given key's.
 * @authors ITC students
 * @version 0.0.1
 * @copyright Instigate Training Center Foundation, Yerevan
 * @date March 2020 year
 * @warning This class is made only for this project
 */

#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

// includes from PoCo library
#include <Poco/JSON/Parser.h>

// includes from C++ library
#include <fstream>
#include <string>

namespace messenger {
	namespace parser {

		/// @brief This class is reading from given ".txt" file
		class file_reader {
			/// @brief Special Members
			private:
				std::ifstream m_fread; ///< Input file stream type variable for
									   /// reading from ".txt" file
				const std::string m_name; ///< The file name where from
										  /// should be reading
				/// @brief Special Member Function
			public:
				/// @brief This method is reading string row
				/// @param [in] row contains row of string
				bool read_row(std::string& row) noexcept;
			private:
				/// @brief This class is not default-constructible 
				file_reader() = delete;
				/// @brief This class in not copy-constructible
				file_reader(const file_reader&) = delete;
				file_reader& operator=(const file_reader&) = delete;
				/// @brief This class is not move-constructible
				file_reader(file_reader&&) = delete;
				file_reader& operator=(file_reader&&) = delete;
			public:
				/// @details This constructor has initialazer list
				///			 and initialazing the file name
				/// 		 then opens the file and
				/// 		 prepares it for reading string row
				explicit file_reader(const std::string& name = "");
				/// @brief The destructor closes the file after
				/// 	   reading and not any throwing exception
				~file_reader() noexcept;
		};

		/// @brief This class is writing to given ".json" file
		class file_writer {
			/// @brief Special Members
			private:
				std::ofstream m_fwrite; ///< Output file stream type variable for
									    /// writing to ".json" file
				const std::string m_name; ///< The file name where should be
										  /// writing the json format text

				/// @brief Special Member Functions
			public:
				/// @brief This method is writing symbols such as "\n etc."
				/// @param [out] symbol which is used as end of line
				bool write_symbol(char symbol) noexcept;
				/// @brief This method is writing json to file
				/// @param [out] json contains row of json
				bool write_json(std::string& json) noexcept;
			private:
				/// @brief This class is not default-constructible 
				file_writer() = delete;
				/// @brief This class in not copy-constructible
				file_writer(const file_writer&) = delete;
				file_writer& operator=(const file_writer&) = delete;
				/// @brief This class is not move-constructible
				file_writer(file_writer&&) = delete;
				file_writer& operator=(file_writer&&) = delete;
			public:
				/// @details This constructor has initialazer list
				/// 		 and initialazing the file name
				/// 		 then opens the file and
				/// 		 prepares it for writing json row
				explicit file_writer(const std::string& name);
				/// @brief The destructor closes the file after
				/// 	   writing and not throwing any exception
				~file_writer() noexcept;
		};

		/// @brief This function is writing to file
		/// @param [in] w opens file for writing
		/// @param [in] file reads and writs to file
		/// @param [out] json_format written file
		/// @return true if read from file and write to
		///			file was successful or false if not
		bool
		read_write_to_file(file_writer& w, std::string file,
						   std::string& json_format) noexcept;

		/// @brief This function is parsing from ".txt" to ".json" format
		/// @param [in] json_object_value tackes the argument by reference
		///				and extracts the json object for further use
		void
		parsing_from_txt_to_json(Poco::JSON::Object::Ptr& json_object_value) noexcept;

		/// @brief This function takes the key and returns it's value
		/// @param [in] key_from_json the key in file
		/// @param [out] json_object_value the value of given key
		/// @return string after converting from Poco::Dynamic::Var
		std::string
		get_value(std::string key_from_json,
				  Poco::JSON::Object::Ptr& json_object_value) noexcept;
	} // namespace parser
} // namespace messenger

#endif // JSON_PARSER_HPP json_parser.cpp
