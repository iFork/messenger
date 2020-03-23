/**
@file commands.hpp
This file is a part of the controller module of the app (in terms of MVC).
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

namespace messenger {
namespace commands {

typedef std::string MSNGR_TIME_T;
typedef std::string MSNGR_USERID_T;
typedef int MSNGR_CHATID_T;

/**
* Enum for command categories.
*/
enum class command_category {
	signup_request,
	signup_response,
	login_request,
	login_response,
	add_contact_request,
	add_contact_response,
	read_chat_room_request,
	read_chat_room_response, //is this necessary ?
	msg_out_request, /**< Outgoing message request.  */
	msg_out_response,
	msg_in_request,
	msg_in_response, //is this necessary
	file_out_request,
	file_out_response
	//terminal //no need for terminal category as it should
			// never reach factory
};


/**
* An abstract class with factory method to create appropriate
* derived types for each specific command category.
*/
class command {
protected:
	/**
	* JSON object pointer.
	*/
	Poco::JSON::Object::Ptr m_cmd_val;
	/**
	* A bool flag to indicate if object was stripped after construction or not.
	*/
	bool m_is_stripped;		
	/**
	* A bool flag to indicate if object was dressed after construction or not.
	*/
	bool m_is_dressed;
public:
//Static public methods
	/**
	* A static factory method to create objects of appropriate
	* type (which are derived from command class) and initialize 
	* them.
	*
	* Used at client side.
	* @param stringified_cmd is a string returned by the stringify
	* method of an object derived from command class.
	* It is a JSON conforming string which has "cmd_cat" key indicating
	* type of object to be created and "cmd_val" key which is used to
	* initialize the object.
	* @return a pointer of base class (command) where pointee is a
	* derived object and is initialized
	*/
	static command* response_factory(const std::string& stringified_cmd) noexcept;
	/**
	* A factory method to be used at server side when originator user_id is not part of
	* the data streamed but is inferred from the socket connection.
	* @param stringified_cmd is a string returned by the stringify
	* method of an object derived from command class.
	* It is a JSON conforming string which has "cmd_cat" key indicating
	* type of object to be created and "cmd_val" key which is used to
	* initialize the object.
	* @param originator_user_id, an id of the user who send the command
	*/
	static command* request_factory(const MSNGR_USERID_T originator_user_id, 
		const std::string& stringified_cmd) noexcept;

//Abstract methods
	/**
	* A pure virtual method to add metadata (to the m_cmd_val)
 	*/
	virtual void dress() = 0;
	/**
	* A pure virtual method to remove metadata (from m_cmd_val)
 	*/
	virtual void strip() = 0;

	/**
	* A pure virtual method to process command obj
	*/
	virtual command* process() noexcept = 0;

//Helpers

	/**
	* Write command obj into provided stringstream 
	*/
	virtual void stringify(std::stringstream& str) const noexcept; 
//TODO: pack for sending - pack(string) / dress + stringify
//TODO: unpack for model updating - unpack(string) / strip + stringify

protected:
//Protected Helpers
	inline void dress_helper(command_category cmd_cat) noexcept;

};

/**
* A class used for terminating response and request exchange between server and client
*/
class cmd_terminal : public command {

//Special member function not supported (yet)
	cmd_terminal(const cmd_terminal&) = delete;
	cmd_terminal(const cmd_terminal&&) = delete;
	cmd_terminal& operator=(const cmd_terminal&) = delete;
	cmd_terminal& operator=(const cmd_terminal&&) = delete;
public:
//C-tors
	/**
	* A c-tor for terminal command
	*/
	cmd_terminal() noexcept;


//Virtual method overrides

	/**
	* Overrides a method adding metadata.
 	*/
	void dress() noexcept override;
	/**
	* Overrides a method removing metadata.
 	*/
	void strip() noexcept override;

	/**
	* Overridden method to process command.
	* @return a nullptr
	*/
	command* process() noexcept override;

	/**
	* Overridden method to stringify command.
	* Sets stringstream to "".
	*/
	void stringify(std::stringstream& sstr) const noexcept override;
};

/**
* A class used for managing sign up requests from client
*/
class cmd_signup_request : public command {

//Special member function not supported (yet)
	cmd_signup_request(const cmd_signup_request&) = delete;
	cmd_signup_request(const cmd_signup_request&&) = delete;
	cmd_signup_request& operator=(const cmd_signup_request&) = delete;
	cmd_signup_request& operator=(const cmd_signup_request&&) = delete;
public:
//C-tors
	/**
	* A c-tor that gui uses to initialize command to be send
	*/
	cmd_signup_request(MSNGR_USERID_T requested_u_id) noexcept;

	/**
	* A c-tor that command factory uses to initialize command at server side,
	* @param cmd_val, a JSON object pointer 
	*/
	cmd_signup_request(const Poco::JSON::Object::Ptr cmd_val) noexcept;

//Virtual method overrides

	/**
	* Overrides a method adding metadata
 	*/
	void dress() noexcept override;
	/**
	* Overrides a method removing metadata
 	*/
	void strip() noexcept override;

	/**
	* Overridden method to process command, 
	* check if user_id is free to be taken,
	* if yes, create user file,
	* @return command with signup_response
	*/
	command* process() noexcept override;

};

/**
* A class used for managing responses to signup requests of server
*/
class cmd_signup_response : public command {

//Special member function not supported (yet)
	cmd_signup_response(const cmd_signup_response&) = delete;
	cmd_signup_response(const cmd_signup_response&&) = delete;
	cmd_signup_response& operator=(const cmd_signup_response&) = delete;
	cmd_signup_response& operator=(const cmd_signup_response&&) = delete;
public:
//C-tors
	/**
	* A c-tor that server uses to initialize command to be processed
	* @param status_code, an int, 0 if successful, 1 otherwise
	* @param user_id, string, if status_code is successful, it 
	* contains user_id successfully signed up with
	*/
	cmd_signup_response(const int status_code, 
			const std::string user_id = "" ) noexcept;

	/**
	* A c-tor that command factory uses to initialize command at client side,
	* @param cmd_val, a JSON object pointer 
	*/
	cmd_signup_response(const Poco::JSON::Object::Ptr cmd_val) noexcept;

//Virtual method overrides

	/**
	* Overrides a method adding metadata
 	*/
	void dress() noexcept override;
	/**
	* Overrides a method removing metadata
 	*/
	void strip() noexcept override;

	/**
	* Overridden method to process command at client side,
	* if successful, create create user file at client end,
	* @return a terminal command 
	*/
	command* process() noexcept override;

};

/**
* A class used for managing login requests from client
*/
class cmd_login_request : public command {

//Special member function not supported (yet)
	cmd_login_request(const cmd_login_request&) = delete;
	cmd_login_request(const cmd_login_request&&) = delete;
	cmd_login_request& operator=(const cmd_login_request&) = delete;
	cmd_login_request& operator=(const cmd_login_request&&) = delete;
public:
//C-tors
	/**
	* A c-tor that gui uses to initialize command to be send
	* @param user_id to log in
	*/
	cmd_login_request(MSNGR_USERID_T user_id) noexcept;

	/**
	* A c-tor that command factory uses to initialize command at server side,
	* @param cmd_val, a JSON object pointer 
	*/
	cmd_login_request(const Poco::JSON::Object::Ptr cmd_val) noexcept;

//Virtual method overrides
	/**
	* Overrides a method adding metadata
 	*/
	void dress() noexcept override;
	/**
	* Overrides a method removing metadata
 	*/
	void strip() noexcept override;

	/**
	* Overridden method to process command, 
	* check if user_id exists to log into,
	* if yes, read user file,
	* @return command with login_response
	*/
	command* process() noexcept override;

};

/**
* A class used for managing server's responses to login requests
*/
class cmd_login_response : public command {

//Special member function not supported (yet)
	cmd_login_response(const cmd_login_response&) = delete;
	cmd_login_response(const cmd_login_response&&) = delete;
	cmd_login_response& operator=(const cmd_login_response&) = delete;
	cmd_login_response& operator=(const cmd_login_response&&) = delete;
public:
//C-tors
	/**
	* A c-tor that server uses to initialize command to be processed
	* @param status_code, an int, 0 if successful, 1 otherwise
	* @param user_json, if status_code is successful, 
	* a JSON object pointer containing db entry for the logged in user.
	*/
	cmd_login_response(const int status_code, 
			Poco::JSON::Object::Ptr user_json = nullptr ) noexcept;

	/**
	* A c-tor that command factory uses to initialize command at client side,
	* @param cmd_val, a JSON object pointer 
	*/
	cmd_login_response(const Poco::JSON::Object::Ptr cmd_val) noexcept;

//Virtual method overrides
	/**
	* Overrides a method adding metadata
 	*/
	void dress() noexcept override;
	/**
	* Overrides a method removing metadata
 	*/
	void strip() noexcept override;

	/**
	* Overridden method to process command at client side,
	* if successful, overwrite user file at client end,
	* @return a terminal command 
	*/
	command* process() noexcept override;

};





/**
* A class used for managing message send requests from client
*/
class cmd_msg_out_request : public command {

//Special member function not supported (yet)
	cmd_msg_out_request(const cmd_msg_out_request&) = delete;
	cmd_msg_out_request(const cmd_msg_out_request&&) = delete;
	cmd_msg_out_request& operator=(const cmd_msg_out_request&) = delete;
	cmd_msg_out_request& operator=(const cmd_msg_out_request&&) = delete;
public:
//C-tors
	/**
	* A c-tor that gui uses to initialize command to be send
	*/
	cmd_msg_out_request(MSNGR_CHATID_T ch_id, MSNGR_TIME_T t,
				 std::string m) noexcept;

	/**
	* A c-tor that command factory uses to initialize command at server side,
	* @param cmd_val, a JSON object pointer 
	* @param originator_user_id, a user_id of the sender
	*/
	cmd_msg_out_request(const MSNGR_USERID_T originator_user_id,
				const Poco::JSON::Object::Ptr cmd_val) noexcept;

//Virtual method overrides
	/**
	* Overrides a method adding metadata
 	*/
	void dress() noexcept override;
	/**
	* Overrides a method removing metadata
 	*/
	void strip() noexcept override;

	/**
	* Overridden method to process msg_out_request, 
	* update corresponding chat,
	* check if members of the chat / recipient is online,
	* if true, send updates of the chat to the participants / recipient,
	* @return command with msg_out_response 
	*/
	command* process() noexcept override;
};

} // namespace commands
} //namespace messenger

#endif //COMMANDS
