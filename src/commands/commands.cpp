
#include "commands.hpp"

//Command_cat implementation
//C-tor
command_cat_t::command_cat_t(): m_cmd_cat(cmd_t::none)
{
	//null/terminal command
}
command_cat_t::command_cat_t(cmd_t cmd_c): m_cmd_cat(cmd_c)
{
}
//Accessors
cmd_t command_cat_t::get()
{
	return m_cmd_cat;
}
//Helper
std::string command_cat_t::to_string()
{
	std::string res;
	switch((int)m_cmd_cat){
		case (int)cmd_t::signup_request:
			res = "signup_request";
			break;
		//TODO: cases
	}
	return res;
}


//Command_t Implementation
//C-tor
command_t::command_t()
{
	//null/terminal command
}

command_t::command_t(std::string cmd)
{
	//validate that cmd follows our API format and put in m_command
	// or assert here and validate externally ?-  static validate() func
}
command_t::command_t(std::string user_ID, command_cat_t cmd_cat, std::string cmd_val)
{
	//m_command = "{" + R"("user_ID":")" + user_ID + 
	//create JSON using Poco and put in m_command
}


//Generic processing, dispatcher Implementation
command_t command_t::process()
{
	command_t response;
	switch((int) m_cmd_cat.get()) {
		case (int) cmd_t::signup_request:
			response = signup_request();
			break;
		//TODO: cases
	}
	return response;
}

//Specific processing, invoking model interfaces Implementation
command_t command_t::signup_request()
{

}
