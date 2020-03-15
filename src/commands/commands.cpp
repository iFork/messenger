
#include "commands.hpp"


//Command_cat implementation
//C-tor
command_cat_t::command_cat_t(): m_cmd_cat(cmds_t::none)
{
	//null/terminal command
}
command_cat_t::command_cat_t(cmds_t cmd_c): m_cmd_cat(cmd_c)
{
}
command_cat_t::command_cat_t(const int cmd_c)
{
	m_cmd_cat = static_cast<cmd_cats_t>(cmd_c);
}
//Accessors
cmds_t command_cat_t::get()
{
	return m_cmd_cat;
}
//Helper
std::string command_cat_t::to_string()
{
	std::string res;
	switch((int)m_cmd_cat){
		case (int)cmds_t::signup_request:
			res = "signup_request";
			break;
		//TODO: cases
	}
	return res;
}
int command_cat_t::to_int()
{
	return static_cast<int>(m_cmd_cat);
}


//Command_t Implementation
//C-tor
command_t::command_t()
{
	//null/terminal command
}

command_t::command_t(const std::string& cmd)
{
	//validate that cmd follows our API format and put in m_command
	// or assert here and validate externally ?-  static validate() func
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(cmd); //using default ParseHandler
	Poco::JSON::Object::Ptr obj_p = 
		result.extract<Poco::JSON::Object::Ptr>();
	m_cmd_cat = obj_p->getValue<int>("cmd_type"); //using implicit conversion
	Poco::JSON::Object::Ptr m_cmd_val = 
		obj_p->getObject("cmd_val"); 
}
command_t::command_t(const command_cat_t cmd_cat, 
			const Poco::JSON::Object::Ptr cmd_val)
{
	//m_command = "{" + R"("user_id":")" + user_id + 
	//create JSON using Poco and put in m_command
}

command_t::command_t(const msg_out_t& msg_out):
		m_cmd_cat(cmds_t::msg_out_request)
{
	//setting JSON obj fields
	m_cmd_val = new Poco::JSON::Object;
	m_cmd_val->set("chat_id", msg_out.chat_id);
	m_cmd_val->set("time", msg_out.time);
	m_cmd_val->set("msg_txt", msg_out.msg_txt);
}

//Helpers Implementation
std::string command_t::to_string()
{
	Poco::JSON::Object cmd;
	cmd.set("cmd_cat", m_cmd_cat.to_int());
	assert(m_cmd_val != nullptr);
	cmd.set("cmd_val", m_cmd_val);
};


//Generic processing, dispatcher Implementation
command_t command_t::process()
{
	command_t response;
	switch((int) m_cmd_cat.get()) {
		case (int) cmds_t::signup_request:
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

//MSG Structs Implementation
//msg_out_t Implementation
msg_out_t::msg_out_t(MSNGR_CHATID_T ch_id, MSNGR_TIME_T t, std::string m):
	chat_id(ch_id), time(t), msg_txt(m)	
{
}


msg_t::msg_t(MSNGR_USERID_T au_id, 
			MSNGR_CHATID_T ch_id, 
			MSNGR_TIME_T t, 
			std::string m):
	author_id(au_id), chat_id(ch_id), time(t), msg_txt(m)	
{
}

msg_in_t::msg_in_t(MSNGR_USERID_T au_id, 
			MSNGR_CHATID_T ch_id, 
			MSNGR_TIME_T t, 
			std::string m):
	author_id(au_id), chat_id(ch_id), time(t), msg_txt(m)	
{
}
