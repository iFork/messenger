//TODO: move to separate lib/folder ??

#ifndef DB_ENTRY
#define DB_ENTRY

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
/**
* An abstract class specifying common interface for 
* db entries 
*/
class db_entry {
protected:
	/**
	* JSON object pointer with the db entry.
	*/
	Poco::JSON::Object::Ptr m_db_entry;
public:

//Helpers

	/**
	* Write db_entry obj into provided stringstream 
	*/
	virtual void stringify(std::stringstream& str) const noexcept; 
};

class db_user : public db_entry {

public:
	//C-tor
	db_user(std::string user_json);
	
	//Accessors
	//void set_f_name(std::string f_name);
	//void set_l_name(std::string l_name);

	void add_contact(MSNGR_USERID_T user_id);
	
	void remove_contact(MSNGR_USERID_T user_id);

	void add_chat(MSNGR_CHATID_T chat_id);

	void remove_chat(MSNGR_CHATID_T chat_id);
};

#endif //DB_ENTRY
