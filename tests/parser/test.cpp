// includes from this project
#include "json_parser.hpp"
// includes from PoCo library
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
// includes from C++ library
#include <iostream>
#include <fstream>
#include <string>

namespace messenger {
	namespace parser {
		/// @details This function tests the parser work and print
		/// 		 the given key's value
		void
		print_after_pars(Poco::JSON::Object::Ptr& json_object_value) noexcept
		{
			using namespace messenger::parser;
			std::cout << "user_id : " << get_value("user_id", json_object_value)
					  << std::endl;
			std::cout << "user_name : " << get_value("user_name", json_object_value)
					  << std::endl;
			std::cout << "password : " << get_value("password", json_object_value)
					  << std::endl;
			std::cout << "conversation_id : " << get_value("conversation_id", json_object_value)
					  << std::endl;
			std::cout << "group_id : " << get_value("group_id", json_object_value)
					  << std::endl;
		}
	}
}
int main() {
	Poco::JSON::Object::Ptr json_object_value;
	messenger::parser::parsing_from_txt_to_json(json_object_value);
	messenger::parser::print_after_pars(json_object_value);
	return 0;
}
