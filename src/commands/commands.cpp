
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
	m_cmd_cat = obj_p->getValue<int>("cmd_cat"); //using implicit conversion
	m_cmd_val = 
		obj_p->getObject("cmd_val"); 
}
//TODO: decide on: keeping duplicate code in the body of this func
//or what?
command_t::command_t(std::istream& cmd)
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
void command_t::stringify(std::stringstream& sstr)
{
	Poco::JSON::Object cmd;
	cmd.set("cmd_cat", m_cmd_cat.to_int());
	assert(m_cmd_val != nullptr);
	cmd.set("cmd_val", m_cmd_val);
	cmd.stringify(sstr);
};


//Generic processing, dispatcher Implementation
command_t command_t::process(MSNGR_USERID_T originator_user_id)
{
	command_t response;
	switch(m_cmd_cat.to_int()) {
		case (int) cmds_t::signup_request:
			response = signup_request(); //user_id is either 000 or irrrelevant
							//or change arg above to clinet id ??
			break;
		case (int) cmds_t::msg_out_request:
			response = process_msg_out_request(originator_user_id);
			break;
		//TODO: cases
	}
	return response;
}

//Specific processing, invoking model interfaces Implementation
command_t command_t::signup_request()
{

}

command_t command_t::process_msg_out_request(MSNGR_USERID_T originator_user_id)
{

	//msg_t msg(originator_user_id, m_cmd_val);
	assert((std::is_same<MSNGR_TIME_T, std::string>::value));
			//ASSUMPTION: MSNGR_TIME_T is string, otherwise
			//additional pre-processing may be needed
	//msg_out_t msg_out(m_cmd_val); //////////
	//or 
	//msg_out_t msg_out(this);
	//msg_t msg(originator_user_id, msg_out); ////////
	//TODO:
}

//MSG Structs Implementation
//C-tors Implementation
msg_out_t::msg_out_t(MSNGR_CHATID_T ch_id, MSNGR_TIME_T t, std::string m):
	chat_id(ch_id), time(t), msg_txt(m)	
{
}

msg_out_t::msg_out_t(Poco::JSON::Object::Ptr cmd_val):
	chat_id(cmd_val->getValue<MSNGR_CHATID_T>("chat_id")),  //chat_id
	msg_txt(cmd_val->getValue<std::string>("msg_txt"))	//msg_txt
{
	assert((std::is_same<MSNGR_TIME_T, std::string>::value));
			//ASSUMPTION: MSNGR_TIME_T is string, otherwise
			//additional pre-processing may be needed
	time = cmd_val->getValue<MSNGR_TIME_T>("time");	//time
}

msg_out_t::msg_out_t(const command_t& cmd) //:
	//chat_id(cmd.cmd_val()->getValue<MSNGR_CHATID_T>("chat_id")),  //chat_id
	//msg_txt(cmd.cmd_val()->getValue<std::string>("msg_txt"))	//msg_txt
{
	//TODO: doing
	//assert(cmd.///////get_cmd_cat = msg_out_request // 
		//BUT what about msg_out_response ?????? is it also a type??
	assert((std::is_same<MSNGR_TIME_T, std::string>::value));
			//ASSUMPTION: MSNGR_TIME_T is string, otherwise
			//additional pre-processing may be needed
	//time = cmd.cmd_val()->getValue<MSNGR_TIME_T>("time"),	//time
}

msg_t::msg_t(MSNGR_USERID_T au_id, 
			MSNGR_CHATID_T ch_id, 
			MSNGR_TIME_T t, 
			std::string m):
	author_id(au_id), chat_id(ch_id), time(t), msg_txt(m)	
{
}
msg_t::msg_t(MSNGR_USERID_T au_id, 
			msg_out_t msg_out):
	author_id(au_id), chat_id(msg_out.chat_id), time(msg_out.time), 
		msg_txt(msg_out.msg_txt)
{
}

msg_in_t::msg_in_t(MSNGR_USERID_T au_id, 
			MSNGR_CHATID_T ch_id, 
			MSNGR_TIME_T t, 
			std::string m):
	author_id(au_id), chat_id(ch_id), time(t), msg_txt(m)	
{
}
