#include "db_entry.hpp"

//Implementation of db_entry
//Helper Implementation
void db_entry::stringify(std::stringstream& sstr) const noexcept
{
	m_db_entry->stringify(sstr);
}

//Implementation of db_user
//TODO: check Doxygen inclusion
/**
* @class db_user
* @var m_db_entry
* JSON format for m_db_entry is:
* {"user_id:"", "f_name":"", "l_name":"",
* "contacts":[""], "chats":[""] }
*/
db_user::db_user(std::string user_json)
{

	//validate that user_json follows our API format and put in m_command
	// or assert here and validate externally ?-  static validate() func
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(user_json); //using default ParseHandler
	m_db_entry = result.extract<Poco::JSON::Object::Ptr>();
}


void db_user::add_contact(MSNGR_USERID_T user_id)
{
	Poco::JSON::Array::Ptr contacts = m_db_entry->getArray("contacts");
//TODO:	
}

void db_user::remove_contact(MSNGR_USERID_T user_id)
{
//TODO:
}
