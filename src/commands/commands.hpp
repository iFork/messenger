/*
@file commands.hpp
This file ss a part of the controller module of the app (in terms of MVC).
*/

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

/*
#define std::string MSNGR_TIME_T 
#define MSNGR_USERID_T int
#define MSNGR_CHATID_T int
*/

typedef std::string MSNGR_TIME_T;
typedef int MSNGR_USERID_T;
typedef int MSNGR_CHATID_T;

/*
@class command_category
@brief Enum for command categories
*/
enum class command_category {
	//none = 0, 
		//may serve as a default value ?
		//null/terminal command
	signup_request,
	signup_response,
	login_request,
	login_response,
	add_contact_request,
	add_contact_response,
	read_chat_room_request,
	read_chat_room_response, //is this necessary ?
	msg_out_request,
	msg_out_response,
	msg_in_request,
	msg_in_response, //is this necessary
	file_out_request,
	file_out_response
};


/*
@class command
@brief This is an abstract class with factory method to create appropriate
derived types per each specific command category.
*/
class command {
protected:
	/*
	@var m_cmd_val
	m_cmd_val a Poco::JSON::Object::Ptr 
	*/
	Poco::JSON::Object::Ptr m_cmd_val;
		
public:
//@section Static public methods
	/*
	@brief static factory method to create objects of appropriate
	type (which are derived from command class) and initialize 
	them.
	@param stringified_cmd is a string returned by the dressed_stringify
	method of an object derived from command class.
	It is a JSON conforming string which has "cmd_cat" key indicating
	type of object to be created and "cmd_val" key which is used to
	initialize the object.
	@return a pointer of base class (command) where pointee is a
	derived object and is initialized
	*/
	static command* create(const std::string& stringified_cmd);
	/*
	@brief factory method to be used at server side when originator user_id is not part of
	the data streamed but is inferred from the socket connection.
	*/
	static command* create(const MSNGR_USERID_T originator_user_id, 
		const std::string& stringified_cmd);

	/*
	static factory method to create objects of appropriate
	type (which are derived from command class)
	param cmd_cat is of command_category type and indicates specific
	derived type to be created
	return a pointer of base class (command) where pointee is a
	derived object as indicating by cmd_cat argument
	*/
	//static command* create(const command_category cmd_cat);
		//Depricate - as itialization of the resultant objects 
		//is out of the scope of this class and we have no uniform way
		//for virtual setters

//@section Abstract methods
	/*
	@brief write command obj into provided stringstream, a pure virtual function,
	packed with the metadata
	 */
	virtual void dressed_stringify(std::stringstream& str) = 0;
	/*
	@brief write command obj into provided stringstream, a pure virtual function,
	stripped from metadata
	 */
	virtual void stripped_stringify(std::stringstream& str) = 0;
	/*
	@brief process command obj, a pure virtual function
	 */
	virtual command* process() = 0;
	
protected:
//Helpers
	inline void dressed_stringify_helper(std::stringstream& sstr, command_category cmd_cat);
};


class cmd_msg_out_request : public command {

//Special member function not supported (yet)
	cmd_msg_out_request(const cmd_msg_out_request&) = delete;
	cmd_msg_out_request& operator=(const cmd_msg_out_request&) = delete;
public:
//@section C-tors

	/*
	@brief c-tor that gui uses to initialize command to be send
	*/
	cmd_msg_out_request(MSNGR_CHATID_T ch_id, MSNGR_TIME_T t,
				 std::string m) noexcept;

	/*
	@brief c-tor that command factory uses to initialize command at server side,
	@param cmd_val, a JSON object pointer 
	@param originator_user_id, a user_id of the sender
	*/
	cmd_msg_out_request(const MSNGR_USERID_T originator_user_id,
				const Poco::JSON::Object::Ptr cmd_val) noexcept;

//@section Virtual method overrides

	/*
	@brief write msg_out_request into provided string with metadata
 	*/
	void dressed_stringify(std::stringstream& str) noexcept override;

	/*
	@brief write msg_out_request into provided string without metadata
 	*/
	virtual void stripped_stringify(std::stringstream& str) noexcept override;

	/*
	@brief process msg_out_request, 
	update corresponding chat,
	check if members of the chat / recipinet is online,
	if true, send updates of the chat to the participants / recipient,
	@return command with msg_out_response 
	*/
	command* process() noexcept override;


//@section Initializers of JSON object (m_cmd_val inherited)
/*
	void set_chat_id();
	void set_time();
	void set_msg_txt();
*/
};

////////////// command leftovers


//@section Specific processing, invoking model interfaces
	/*
	@brief process signup request per model,
	check availability of username, create user record
	@return command with response
	*/
//	command_t signup_request();

	/*
	@brief terminal processing of signup response to 
	update view, calling view's methods, either
	gui.signup_success() or gui.signup.failure()
	@return null/empty command
	*/
//	command_t signup_response();
	
//	command_t login_request();
	
//	command_t login_response();




//TODO: DISSIMINATE
//private:
	//Special member function not supported (yet)
//@section Special member functions




#endif //COMMANDS
