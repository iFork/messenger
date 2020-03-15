#include "json_parser.hpp"
#include <iostream>
#include <fstream>

using namespace Poco::JSON;
using namespace Poco::Dynamic;

int main() {
	std::string json_file;
	std::string file;
	// insted of writing Poco::JSON::Parser used Parser
	//
	Parser parse_from;
	File_writer w("./json_files/w_file.json");
	file_writer(w, file, json_file);
	// Parse the JSON and get the Results
	//insted of writing Poco::Dynamic::Var used Var
	//
	Var parsed_json = parse_from.parse(json_file);
	Var parsed_json_result = parse_from.result();
	// Get the JSON Object
	// insted of writing Poco::JSON::Object::Ptr used Object::Ptr
	//
	Object::Ptr json_object_value = parsed_json_result.extract<Object::Ptr>();
	// Get the values for the member variables and print
	//
	print_after_pars(json_file, json_object_value);
	return 0;
}
