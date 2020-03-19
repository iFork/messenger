
#include "commands.hpp"

#include <cassert>

/*
TODO-MIGRATAE to command
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
*/

//Command Implementation
//Static Methods Implementation
command* command::create(const std::string& stringified_cmd)
{

}

command* command::create(const MSNGR_USERID_T originator_user_id, 
		const std::string& stringified_cmd)
{
	//validate that cmd follows our API format and put in m_command
	// or assert here and validate externally ?-  static validate() func
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(stringified_cmd); //using default ParseHandler
	Poco::JSON::Object::Ptr obj_p = 
		result.extract<Poco::JSON::Object::Ptr>();
 	int cmd_cat = obj_p->getValue<int>("cmd_cat"); 
	Poco::JSON::Object::Ptr cmd_val = 
		obj_p->getObject("cmd_val"); 
	command* cmd = nullptr;
	switch (cmd_cat) {
		case static_cast<int>(command_category::msg_out_request):
			cmd = new cmd_msg_out_request(originator_user_id, 
					cmd_val);
			break;
	}
	return cmd;
}

//Helper Implementation
inline void command::dressed_stringify_helper(std::stringstream& sstr, command_category cmd_cat)
{
	Poco::JSON::Object cmd;
	cmd.set("cmd_cat", static_cast<int>(cmd_cat));
	assert(m_cmd_val != nullptr);
	cmd.set("cmd_val", m_cmd_val);
	cmd.stringify(sstr);
}

//cmd_msg_out_request Implementation
//C-tors
cmd_msg_out_request::cmd_msg_out_request(MSNGR_CHATID_T ch_id, MSNGR_TIME_T t,
				 std::string m) noexcept
{
	m_cmd_val = new Poco::JSON::Object;
	m_cmd_val->set("chat_id", ch_id);
	m_cmd_val->set("time", t);
	m_cmd_val->set("msg_txt", m);
}

cmd_msg_out_request::cmd_msg_out_request(const MSNGR_USERID_T originator_user_id,
			const Poco::JSON::Object::Ptr cmd_val) noexcept
{
	m_cmd_val = cmd_val;
	m_cmd_val->set("author_id", originator_user_id);
}

//Virtual Method Overrides
void cmd_msg_out_request::dressed_stringify(std::stringstream& sstr) noexcept
{
	dressed_stringify_helper(sstr, command_category::msg_out_request);

}

void cmd_msg_out_request::stripped_stringify(std::stringstream& sstr) noexcept
{
	//TODO: remove keys
//	Poco::JSON::Object::Ptr tempo = new Poco::JSON::Object;
//	m_cmd_val->set("chat_id", ch_id);
//	m_cmd_val->set("time", t);
//	m_cmd_val->set("msg_txt", m);
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
	TODO:ADD and RENAME  Stringify methods : 
	 this stringiofyer should strip away meta-data, cmd category 
	have strip_/stringify_strip or bare_stringify or pack_string
// {"author_id":1,"chat_id":12,"msg_txt":"Hello msg out request","time":"12:30"}
	 strip downed version for saving / storing 
	      //TO STRIP away before writing - E.G.  cmd_cat, cmd_val->chat_id
	So this cannot be universal function for all subtypes but each subtype
	must/can (?) OVERRIDE it before passing to model-updater (?) 
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
		//or terminal command - new cmd_respondse(none)
	//elif 
		//return cmd_msg_out_response (?) 

	//assert(cmd.///////get_cmd_cat = msg_out_request // 
		//BUT what about msg_out_response ?????? is it also a type??
	assert((std::is_same<MSNGR_TIME_T, std::string>::value));
			//ASSUMPTION: MSNGR_TIME_T is string, otherwise
			//additional pre-processing may be needed
}

///TODO cont' types
class cmd_login_request : public command {


};



