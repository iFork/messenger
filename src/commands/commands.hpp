#ifndef COMMANDS
#define COMMANDS

#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
//#include "Poco/JSON/JSONException.h"
//#include "Poco/Environment.h"
//#include "Poco/Path.h"
//#include "Poco/File.h"
//#include "Poco/FileStream.h"
//#include "Poco/StreamCopier.h"

//#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

#define MSNGR_TIME_T std::string
#define MSNGR_USERID_T int
#define MSNGR_CHATID_T int

//Command Category
class command_cat_t {
public:
	enum class cmd_cats_t {
		none = 0,
		signup_request,
		signup_response,
		login_request,
		login_response,
		add_contact_request,
		add_contact_response,
		msg_out_request,
		msg_out_response,
		file_out_request,
		file_out_response
	};
private:	
	cmd_cats_t m_cmd_cat;
public:
//C-tors
	command_cat_t();
	command_cat_t(const cmd_cats_t cmd_c);
	command_cat_t(const int cmd_c);
//Accessors
	cmd_cats_t get();
//Helpers
	std::string to_string();
	int to_int();
};

typedef command_cat_t::cmd_cats_t cmds_t;

//Forward declarations
struct msg_out_t;
struct msg_t;
struct msg_in_t;

class command_t {

private:
//Private Data Members
	command_cat_t m_cmd_cat;
	Poco::JSON::Object::Ptr m_cmd_val;
public:
//@section Special member functions
	command_t();
	/*
	@brief parsing string into command_t object
	*/
	command_t(const std::string& cmd);
	/*
	@brief parsing istream into command_t object
	*/
	command_t(std::istream& cmd); //parse doesnot like const istrm
	/*
	@brief 
	*/
	command_t(const command_cat_t cmd_cat, 
			const Poco::JSON::Object::Ptr cmd_val);
	/*
	@brief parsing msg_out_t into command_t object
	*/
	command_t(const msg_out_t& msg_out);
	/*
	@brief
	*/
			
//	~command_t() noexcept;

	command_t(const command_t& cmd);
//	command_t& operator=(command_t& cmd);

//@Section Accesssors
//need when msg_t-s  use cmd to construct msg
//TODO: add accessors for msg_t-s to use

//@section Helpers
	/*
	@brief write command obj into provided stringstream
	 */
	void stringify(std::stringstream& sstr);

//@section Generic processing, dispatcher
	//command_t process();
	command_t process(MSNGR_USERID_T originator_user_id);

//@section Specific processing, invoking model interfaces
	/*
	@brief process signup request per model,
	check availability of username, create user record
	@return command with response
	*/
	command_t signup_request();

	/*
	@brief terminal processing of signup response to 
	update view, calling view's methods, either
	gui.signup_success() or gui.signup.failure()
	@return null/empty command
	*/
	command_t signup_response();
	
	command_t login_request();
	
	command_t login_response();

	/*
	@brief process msg_out request, 
	create msg and update corresponding chat,
	check if members of the chat / recipinet is online,
	if true, send updates of the chat to the participants / recipient,
	@param originator_user_id - id of sender
	@return command with msg_out_response 
	*/
	command_t process_msg_out_request(MSNGR_USERID_T originator_user_id);


};


//TODO: may convert data members to private with accessor funcs ?
struct msg_out_t {
	
	MSNGR_CHATID_T chat_id;
	MSNGR_TIME_T time;
	std::string msg_txt;
//C-tor
	msg_out_t(MSNGR_CHATID_T ch_id, MSNGR_TIME_T t, std::string m);
	msg_out_t(const Poco::JSON::Object::Ptr cmd_val);
	//or cmd_t itself - to assert type ?
	msg_out_t(const command_t& cmd); //TODO: opt 1 of these ..?
};

struct msg_t {
	MSNGR_USERID_T author_id;
	MSNGR_CHATID_T chat_id;
	MSNGR_TIME_T time;
	std::string msg_txt;
//C-tor
	msg_t(MSNGR_USERID_T au_id, 
			MSNGR_CHATID_T ch_id, 
			MSNGR_TIME_T t, 
			std::string m);
	msg_t(MSNGR_USERID_T au_id, 
			msg_out_t msg_out);
};

struct msg_in_t {
//now - same as msg_t
	MSNGR_USERID_T author_id;
	MSNGR_CHATID_T chat_id; // now redundant as chat is ony 1-on-1
	MSNGR_TIME_T time;
	std::string msg_txt;
//C-tor
	msg_in_t(MSNGR_USERID_T au_id, 
			MSNGR_CHATID_T ch_id, 
			MSNGR_TIME_T t, 
			std::string m);
};

#endif //COMMANDS
