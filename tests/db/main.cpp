#include "user_db_handler.hpp"
#include "chat_db_handler.hpp"
#include "db_entry.hpp"
#include "db_user.hpp"
#include "db_chat.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

#include <Poco/JSON/Object.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/ParseHandler.h>

Poco::JSON::Object::Ptr create_user_json(const std::string& user_id, const std::string& user_name)
{
	Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
	root->set("user_id", user_id);
	root->set("first_name", user_name);
	root->set("last_name", user_name);
	Poco::JSON::Array contacts = Poco::JSON::Array();
	Poco::JSON::Array chats = Poco::JSON::Array();
	root->set("contacts", contacts);
	root->set("chats", chats);
	return root;
}

Poco::JSON::Object::Ptr create_chat_json(const std::string& chat_id)
{
	Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
	root->set("chat_id", chat_id);
	Poco::JSON::Array participants = Poco::JSON::Array();
	Poco::JSON::Array messages = Poco::JSON::Array();
	root->set("participants", participants);
	root->set("messages", messages);
	return root;
}

Poco::JSON::Object::Ptr create_msg_json(const std::string& msg_id, const std::string& author_id, const std::string& time, const std::string text)
{
	Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
	root->set("msg_id", msg_id);
	root->set("author_id", author_id);
	root->set("time", time);
	root->set("text", text);
	return root;
}

std::string stringify(Poco::JSON::Object::Ptr user_json)
{
	std::stringstream str;
	assert(user_json);
	user_json->stringify(str, 4);
	std::string user_data = str.str();
	return user_data;
}

void test_add_contact(const std::string& user_id)
{
	messenger::database::user_database_handler db;
	messenger::database::database_user db_user_obj(db.read_user_data(user_id));
	assert(db_user_obj.add_contact("Ani") == 0);
	assert(db_user_obj.add_contact("Anna") == 0);
	assert(db_user_obj.add_contact("Lilit") == -1);
}

void test_search_contact(const std::string& user_id)
{
	messenger::database::user_database_handler db;
	messenger::database::database_user db_user_obj(db.read_user_data(user_id));
	assert(db_user_obj.search_contact("Ani") == 1);
	assert(db_user_obj.search_contact("Anna") == 1);
	assert(db_user_obj.search_contact("0005") == 0);
}

void test_remove_contact(const std::string& user_id)
{
	messenger::database::user_database_handler db;
	messenger::database::database_user db_user_obj(db.read_user_data(user_id));
	assert(db_user_obj.remove_contact("Ani") == 0);
	assert(db_user_obj.remove_contact("0005") == -1);
	assert(db_user_obj.remove_contact("0002") == -1);
}

void test_add_chat(const std::string& user_id)
{
	messenger::database::user_database_handler db;
	messenger::database::database_user db_user_obj(db.read_user_data(user_id));
	assert(db_user_obj.add_chat("An_Lilit") == 0);
	assert(db_user_obj.add_chat("An_Vik") == 0);
	assert(db_user_obj.add_chat("Lilit_An") == -1);
}

void test_search_chat(const std::string& user_id)
{
	messenger::database::user_database_handler db;
	messenger::database::database_user db_user_obj(db.read_user_data(user_id));
	assert(db_user_obj.search_chat("Lilit_Anna") == 1);
	assert(db_user_obj.search_chat("An_Lilit") == 1);
	assert(db_user_obj.search_chat("Ani_Lilit") == 0);
}

void test_remove_chat(const std::string& user_id)
{
	messenger::database::user_database_handler db;
	messenger::database::database_user db_user_obj(db.read_user_data(user_id));
	assert(db_user_obj.remove_chat("An_Lilit") == 0);
	assert(db_user_obj.remove_chat("Lilit_An") == -1);
	assert(db_user_obj.remove_chat("Ani_Lilit") == -1);
}

void test_add_participant(const std::string& chat_id)
{
	messenger::database::chat_database_handler db;
	messenger::database::database_chat db_chat_obj(db.read_chat_data(chat_id));
	assert(db_chat_obj.add_participant("Ani") == 0);
	assert(db_chat_obj.add_participant("Anna") == 0);
	assert(db_chat_obj.add_participant("Vika") == -1);
}

void test_search_participant(const std::string& chat_id)
{
	messenger::database::chat_database_handler db;
	messenger::database::database_chat db_chat_obj(db.read_chat_data(chat_id));
	assert(db_chat_obj.search_participant("Ani") == 1);
	assert(db_chat_obj.search_participant("Anna") == 1);
	assert(db_chat_obj.search_participant("Lilit") == 0);
}

void test_remove_participant(const std::string& chat_id)
{
	messenger::database::chat_database_handler db;
	messenger::database::database_chat db_chat_obj(db.read_chat_data(chat_id));
	assert(db_chat_obj.remove_participant("Ani") == 0);
	assert(db_chat_obj.remove_participant("Lilit") == -1);
	assert(db_chat_obj.remove_participant("Vika") == -1);
}

void test_add_message(const std::string& chat_id)
{
	Poco::JSON::Object::Ptr msg_json1 = create_msg_json("01", "0002", "12:30", "Hello. How are you?");
	std::string msg1 = stringify(msg_json1);
	Poco::JSON::Object::Ptr msg_json2 = create_msg_json("02", "0001", "12:50", "Hello. Good!");
	std:: string msg2 = stringify(msg_json2);
	Poco::JSON::Object::Ptr msg_json3 = create_msg_json("03", "0011", "12:00", "Hello.");
	std:: string msg3 = stringify(msg_json3);

	messenger::database::chat_database_handler db;
	messenger::database::database_chat db_chat_obj(db.read_chat_data(chat_id));
	assert(db_chat_obj.add_message("01", msg1) == 0);
	assert(db_chat_obj.add_message("02", msg2) == 0);
	assert(db_chat_obj.add_message("03", msg3) == 0);
	assert(db_chat_obj.add_message("01", msg1) == -1);
}

void test_search_message(const std::string& chat_id)
{
	Poco::JSON::Object::Ptr msg_json1 = create_msg_json("01", "0002", "12:30", "Hello. How are you?");
	std::string msg1 = stringify(msg_json1);
	Poco::JSON::Object::Ptr msg_json2 = create_msg_json("02", "0001", "12:50", "Hello. Good!");
	std:: string msg2 = stringify(msg_json2);
	Poco::JSON::Object::Ptr msg_json3 = create_msg_json("03", "0005", "12:59", "Hello. Good!");
	std:: string msg3 = stringify(msg_json3);

	messenger::database::chat_database_handler db;
	messenger::database::database_chat db_chat_obj(db.read_chat_data(chat_id));
	assert(db_chat_obj.search_message("01") == 0);
	assert(db_chat_obj.search_message("02") == 1);
	assert(db_chat_obj.search_message("05") == -1);
}

void test_remove_message(const std::string& chat_id)
{
	Poco::JSON::Object::Ptr msg_json1 = create_msg_json("01", "0002", "12:30", "Hello. How are you?");
	std::string msg1 = stringify(msg_json1);
	Poco::JSON::Object::Ptr msg_json3 = create_msg_json("03", "0005", "12:59", "Hello. Good!");
	std:: string msg3 = stringify(msg_json3);
	
	messenger::database::chat_database_handler db;
	messenger::database::database_chat db_chat_obj(db.read_chat_data(chat_id));
	assert(db_chat_obj.remove_message("01", msg1) == 0);
	assert(db_chat_obj.remove_message("03", msg3) == 0);
	assert(db_chat_obj.remove_message("01", msg1) == -1);
}

int main()
{
	Poco::JSON::Object::Ptr user_json = create_user_json("Anna", "Anna");
	std::string user_id = user_json->getValue<std::string>("user_id");
	std::string user = stringify(user_json);

	//test create user 
	messenger::database::user_database_handler db_user;
	db_user.create_user(user_id, user);

	user_json = create_user_json("Ani", "Ani");
	user_id = user_json->getValue<std::string>("user_id");
	user = stringify(user_json);
	db_user.create_user(user_id, user);

	user_json = create_user_json("Lilit", "Lilit");
	user_id = user_json->getValue<std::string>("user_id");
	user = stringify(user_json);
	db_user.create_user(user_id, user);

	test_add_contact(user_id);
	test_search_contact(user_id);
	test_remove_contact(user_id);
	test_add_chat(user_id);
	test_search_chat(user_id);
	test_remove_chat(user_id);

	Poco::JSON::Object::Ptr chat_json = create_chat_json("Ani_Anna");
	std::string chat_id = chat_json->getValue<std::string>("chat_id");
	std::string chat = stringify(chat_json);
	//test create chat 
	messenger::database::chat_database_handler db_chat;
	db_chat.create_chat(chat_id, chat);

	test_add_participant(chat_id);
	test_search_participant(chat_id);
	test_remove_participant(chat_id);
	test_add_message(chat_id);
	test_search_message(chat_id);
	test_remove_message(chat_id);

	return 0;
}
