
#include "commands.hpp"

#include <cassert>

namespace messenger {
namespace commands {

//Command Implementation
//Static Methods Implementation
command* command::response_factory(const std::string& stringified_cmd) noexcept
{
	//validate that cmd follows our API format
	// or assert here and validate externally ?-  static validate() func
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(stringified_cmd); //using default ParseHandler
	//NOTE: on catching poco exceptions inside a debug macro, but no added value since 
	//this in our case shoud be asserted, not cought as runtime exceptions
	//but poco throws exceptions. These are no substitute for assert so may Skip this.
	Poco::JSON::Object::Ptr obj_p = 
		result.extract<Poco::JSON::Object::Ptr>();
 	int cmd_cat = obj_p->getValue<int>("cmd_cat"); 
	//validate that cmd_cat is of supported types for the server
	Poco::JSON::Object::Ptr cmd_val = 
		obj_p->getObject("cmd_val"); 
	command* cmd = nullptr;
	switch (cmd_cat) {
		case static_cast<int>(command_category::signup_response):
			cmd = new cmd_signup_response(cmd_val);
			break;
		case static_cast<int>(command_category::msg_in_response):
			//cmd = new 
				
			break;
		default:
			assert(false && "command category is not supported");
	}
	//TODO: use smart pointers when returning w/ new. use unique-ptr
	return cmd;

}

command* command::request_factory(const MSNGR_USERID_T originator_user_id, 
		const std::string& stringified_cmd) noexcept
{
	//validate that cmd follows our API format and put in m_command
	// or assert here and validate externally ?-  static validate() func
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(stringified_cmd); //using default ParseHandler
	Poco::JSON::Object::Ptr obj_p = 
		result.extract<Poco::JSON::Object::Ptr>();
 	int cmd_cat = obj_p->getValue<int>("cmd_cat"); 
	//validate that cmd_cat is of supported types for the client
	Poco::JSON::Object::Ptr cmd_val = 
		obj_p->getObject("cmd_val"); 
	command* cmd = nullptr;
	switch (cmd_cat) {
		case static_cast<int>(command_category::signup_request):
			cmd = new cmd_signup_request(cmd_val);
			break;
		case static_cast<int>(command_category::msg_out_request):
			cmd = new cmd_msg_out_request(originator_user_id, 
					cmd_val);
			break;
		default:
			assert(false && "Command category is not supported");
	}
	//TODO: use smart pointers when returning w/ new. use unique-ptr
	return cmd;
}

//Helper Implementation
void command::stringify(std::stringstream& sstr) const noexcept
{
	//TODO: assert m_cmd_val != nullptr
	m_cmd_val->stringify(sstr);
}

//TODO: move dress-helper before dress (in declarations??) - will be easy for linker

inline void command::dress_helper(command_category cmd_cat) noexcept
{
	Poco::JSON::Object::Ptr new_cmd = new Poco::JSON::Object;
//TODO: Rename fileds - cat to category
	new_cmd->set("cmd_cat", static_cast<int>(cmd_cat));
	assert(m_cmd_val != nullptr);
	new_cmd->set("cmd_val", m_cmd_val);
	m_cmd_val = new_cmd;
	//no need to delete as poco's shared ptr handles this 
}

//TODO: use smart pointers / unique-ptr

//Implementation of cmd_terminal
//C-tors
cmd_terminal::cmd_terminal() noexcept
{
	m_cmd_val = nullptr;
}

//Virtual Method Overrides
void cmd_terminal::dress() noexcept
{
}

void cmd_terminal::strip() noexcept
{
}

command* cmd_terminal::process() noexcept
{
	return nullptr;
}

void cmd_terminal::stringify(std::stringstream& sstr) const noexcept
{
	sstr.str("");
}

//Implementation of cmd_signup_request
//C-tors
//TODO: check Doxygen inclusion
/**
* @class cmd_signup_request
* @var m_cmd_val
* JSON format for m_cmd_val in cmd_signup_request is:
* {"user_id":"string"}
*/
cmd_signup_request::cmd_signup_request(MSNGR_USERID_T requested_u_id) noexcept
{
	m_is_stripped = false;
	m_is_dressed = false;
	m_cmd_val = new Poco::JSON::Object;
	m_cmd_val->set("user_id", requested_u_id);
}

cmd_signup_request::cmd_signup_request(const Poco::JSON::Object::Ptr cmd_val) noexcept
{
	m_is_stripped = false;
	m_is_dressed = false;
	m_cmd_val = cmd_val;
}

//Virtual Method Overrides

void cmd_signup_request::dress() noexcept
{
	//verify that this is not stripped already as in that 
	//cas we need to recover
	assert(m_is_stripped == false);
	assert(m_is_dressed == false);
	m_is_dressed = true;
	dress_helper(command_category::signup_request);
}

void cmd_signup_request::strip() noexcept
{
	//verify that this is not dressed already as in that 
	//cas we need to strip more fields
	//assert(m_is_dressed == false);
	//assert(m_is_stripped == false);
	//m_is_stripped = true;

	//TODO: evaluate the need for pure virtual of this func in base class
	//no need to strip signup_request as it will not be written into a file
}


command* cmd_signup_request::process() noexcept
{
	command* response = nullptr;
	//TODO - assert m_cmd_vall != nullptr
	MSNGR_USERID_T user_id = m_cmd_val->getValue<MSNGR_USERID_T>("user_id");

	std::cout << "user id to find is:" << user_id << std::endl;
	assert((std::is_same<MSNGR_USERID_T, std::string>::value));
			//ASSUMPTION: MSNGR_USERID_T is string, otherwise
			//additional pre-processing may be needed
	//check if user_id is free 	
	bool is_occupied = true;
	//bool is_occupied = bd_handler::find_file(user_id);
	
	if(!is_occupied) {
		std::cout << "creating user file for " << user_id << std::endl;
		response = new cmd_signup_response(0, user_id);
	}
	else {
		response = new cmd_signup_response(1);
	}
	return response;		
	//use uniqe ptr
}


//Implementation of cmd_signup_response
//C-tors
//TODO: check Doxygen inclusion
/**
* @class cmd_signup_response
* @var m_cmd_val
* JSON format for m_cmd_val is:
* when signup succeeds:
* {"status":int, "user_id":"string"};
* when signup fails:
* {"status":int};
* when wrtitten into a user file (stripped):
* {"status":int};
*/
cmd_signup_response::cmd_signup_response(const int status_code, 
			const std::string user_id) noexcept
{ 
	m_is_stripped = false;
	m_is_dressed = false;
	m_cmd_val = new Poco::JSON::Object;
	m_cmd_val->set("status", status_code);
	if (status_code == 0) {
		m_cmd_val->set("user_id", user_id);
	}
}

cmd_signup_response::cmd_signup_response(const Poco::JSON::Object::Ptr cmd_val) noexcept
{
	m_is_stripped = false;
	m_is_dressed = false;
	m_cmd_val = cmd_val;
}

//Virtual Method Overrides

void cmd_signup_response::dress() noexcept
{
	//verify that this is not stripped already as in that 
	//cas we need to recover
	assert(m_is_stripped == false);
	assert(m_is_dressed == false);
	m_is_dressed = true;
	dress_helper(command_category::signup_response);
}

void cmd_signup_response::strip() noexcept
{
	//verify that this is not dressed already as in that 
	//cas we need to strip more fields
	assert(m_is_dressed == false);
	assert(m_is_stripped == false);
	m_is_stripped = true;
	m_cmd_val->remove("status");
}


command* cmd_signup_response::process() noexcept
{
	command* request  = nullptr;
	int status_code = m_cmd_val->getValue<int>("status");
	if (status_code == 0) {
		MSNGR_USERID_T user_id = m_cmd_val->getValue<MSNGR_USERID_T>("user_id");
		assert((std::is_same<MSNGR_USERID_T, std::string>::value));
				//ASSUMPTION: MSNGR_USERID_T is string, otherwise
				//additional pre-processing may be needed
		//write file
		strip(); //strip for writing
		std::stringstream ss;
		stringify(ss);
		std::cout <<"Processing: Signup succeeded\n";
		std::cout <<"Processing: Writing into user.json: " << ss.str() << std::endl;
		//gui/client.db_handler.create_file(user_id, user_id)
		std::cout <<"Processing: Calling gui.signup_success\n";
		//gui.signup_success(user_id)
	}
	else {

		std::cout <<"Processing: Signup failed\n";
		std::cout <<"Processing: Calling gui.signup_failure\n";
		//gui.signup_failure();
	}	
	return request  = new cmd_terminal();

}


//Implementation of cmd_msg_out_request
//C-tors
//TODO: check Doxygen inclusion
/**
* @class cmd_msg_out_request
* @var m_cmd_val
* JSON format for m_cmd_val is:
* when created by client:
* {"chat_id":int, //TODO: or string
*  "time":"string",
*  "msg_txt":"string"};
* when created by receiving server:
* {"chat_id":int, //TODO: or string
*  "author_id":"string", 
*  "time":"string",
*  "msg_txt":"string"};
* when wrtitten into a chat (stripped):
* {
*  "author_id":"string", 
*  "time":"string",
*  "msg_txt":"string"}
*/
cmd_msg_out_request::cmd_msg_out_request(MSNGR_CHATID_T ch_id, MSNGR_TIME_T t,
				 std::string m) noexcept
{
	m_is_stripped = false;
	m_is_dressed = false;
	m_cmd_val = new Poco::JSON::Object;
	m_cmd_val->set("chat_id", ch_id);
	m_cmd_val->set("time", t);
	m_cmd_val->set("msg_txt", m);
}

cmd_msg_out_request::cmd_msg_out_request(const MSNGR_USERID_T originator_user_id,
			const Poco::JSON::Object::Ptr cmd_val) noexcept
{
	m_is_stripped = false;
	m_is_dressed = false;
	m_cmd_val = cmd_val;
	m_cmd_val->set("author_id", originator_user_id);
}

//Virtual Method Overrides

void cmd_msg_out_request::dress() noexcept
{
	//verify that this is not stripped already as in that 
	//cas we need to recover
	assert(m_is_stripped == false);
	assert(m_is_dressed == false);
	m_is_dressed = true;
	dress_helper(command_category::msg_out_request);
}

void cmd_msg_out_request::strip() noexcept
{
	//verify that this is not dressed already as in that 
	//cas we need to strip more fields
	assert(m_is_dressed == false);
	assert(m_is_stripped == false);
	m_is_stripped = true;
	m_cmd_val->remove("chat_id");
}


command* cmd_msg_out_request::process() noexcept
{
	command* response = nullptr;
	MSNGR_CHATID_T chat_id = m_cmd_val->getValue<MSNGR_CHATID_T>("chat_id");
	std::cout << "chat id to find is:" << chat_id << std::endl;
	//find chat file by chat_id	
	//append chat file with the message
	//chat_file ch_f(chat_id)
	//stringify(sstr)...
	/*
	      //TO STRIP away before writing 
		- E.G.  cmd_cat, cmd_val->chat_id
	 / db writer
	*/

	//ch_f.append(sstr.str());
	//get participants of the chat
		//either from chat json 
		//or infer from chat_id naming convention
		//or in a separate file mapping jsons with participants -
		//like contact or chat-room list
	//user_id receiver_id
	//if(server.is_online(receiver_id))
		//return new cmd_msg_in_response()
		//or
		//msg_in = new cmd_msg_in_response()
		//server.send_to_user(user_id, msg_in.stringify())
		//command response = new cmd_cat_response()
		//or terminal command 
	//elif 
		//return cmd_msg_out_response (?) 

	//assert(cmd.///////get_cmd_cat = msg_out_request // 
		//BUT what about msg_out_response ?????? is it also a type??
	assert((std::is_same<MSNGR_TIME_T, std::string>::value));
			//ASSUMPTION: MSNGR_TIME_T is string, otherwise
			//additional pre-processing may be needed
	return response;
}


cmd_login_request::cmd_login_request(MSNGR_USERID_T user_id) noexcept{}
cmd_login_request::cmd_login_request(const Poco::JSON::Object::Ptr cmd_val)
	noexcept{}

void cmd_login_request::dress() noexcept {}
void cmd_login_request::strip() noexcept {}
command* cmd_login_request::process() noexcept {}

} // namespace commands
} //namespace messenger
