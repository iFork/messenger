
#include <string>

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
		send_msg_request,
		send_msg_response,
		send_file_request,
		send_file_response
	};
private:	
	cmd_cats_t m_cmd_cat;
public:
//C-tors
	command_cat_t();
	command_cat_t(cmd_cats_t cmd_c);
//Accessors
	cmd_cats_t get();
//Helpers
	std::string to_string();
};

typedef command_cat_t::cmd_cats_t cmd_t;

class command_t {

private:
	std::string m_user_ID;
	command_cat_t m_cmd_cat;
	std::string m_cmd_val;
public:
//@section Special member functions
	command_t();
	command_t(std::string user_ID, command_cat_t cmd_cat, std::string cmd_val);
	command_t(std::string cmd);

//	~command_t() noexcept;

	command_t(const command_t& cmd);
//	command_t& operator=(command_t& cmd);
//
	//@section Generic processing, dispatcher
	command_t process();

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


};
