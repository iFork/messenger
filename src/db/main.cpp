#include "db.hpp"
#include "db_entry.hpp"

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
	std::string user_file;
    user_file.append(user_name).append(".json");
	root->set("user_id", user_id);
	root->set("user_file", user_file);
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
	std::string chat_file;
    chat_file.append(chat_id).append(".json");
	root->set("chat_id", chat_id);
	root->set("chat_file", chat_file);
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
	user_json->stringify(str, 4);
	std::cout << str.str() << "\n";
	std::string user_data = str.str();
	return user_data;
}

void test_add_contact(const std::string& file_name)
{
	messenger::database db;
	messenger::db_user db_user_obj(db.read_user_data(file_name));
	assert(db_user_obj.add_contact("0002") == 0);
	assert(db_user_obj.add_contact("0003") == 0);
	assert(db_user_obj.add_contact("0002") == -1);
}

void test_search_contact(const std::string& file_name)
{
	messenger::database db;
	messenger::db_user db_user_obj(db.read_user_data(file_name));
	assert(db_user_obj.search_contact("0002") == 1);
	assert(db_user_obj.search_contact("0003") == 1);
	assert(db_user_obj.search_contact("0005") == 0);
}

void test_remove_contact(const std::string& file_name)
{
	messenger::database db;
	messenger::db_user db_user_obj(db.read_user_data(file_name));
	assert(db_user_obj.remove_contact("0002") == 0);
	assert(db_user_obj.remove_contact("0005") == -1);
	assert(db_user_obj.remove_contact("0002") == -1);
}

void test_add_chat(const std::string& file_name)
{
	messenger::database db;
	messenger::db_user db_user_obj(db.read_user_data(file_name));
	assert(db_user_obj.add_chat("chat_0001_0002") == 0);
	assert(db_user_obj.add_chat("chat_0001_0003") == 0);
	assert(db_user_obj.add_chat("chat_0001_0002") == -1);
}

void test_search_chat(const std::string& file_name)
{
	messenger::database db;
	messenger::db_user db_user_obj(db.read_user_data(file_name));
	assert(db_user_obj.search_chat("chat_0001_0002") == 1);
	assert(db_user_obj.search_chat("chat_0001_0003") == 1);
	assert(db_user_obj.search_chat("chat_0001_0005") == 0);
}

void test_remove_chat(const std::string& file_name)
{
	messenger::database db;
	messenger::db_user db_user_obj(db.read_user_data(file_name));
	assert(db_user_obj.remove_chat("chat_0001_0002") == 0);
	assert(db_user_obj.remove_chat("chat_0001_0005") == -1);
	assert(db_user_obj.remove_chat("chat_0001_0002") == -1);
}

void test_add_participant(const std::string& file_name)
{
	messenger::database db;
	messenger::db_chat db_chat_obj(db.read_user_data(file_name));
	assert(db_chat_obj.add_participant("0001") == 0);
	assert(db_chat_obj.add_participant("0002") == 0);
	assert(db_chat_obj.add_participant("0002") == -1);
}

void test_search_participant(const std::string& file_name)
{
	messenger::database db;
	messenger::db_chat db_chat_obj(db.read_user_data(file_name));
	assert(db_chat_obj.search_participant("0001") == 1);
	assert(db_chat_obj.search_participant("0002") == 1);
	assert(db_chat_obj.search_participant("0005") == 0);
}

void test_remove_participant(const std::string& file_name)
{
	messenger::database db;
	messenger::db_chat db_chat_obj(db.read_user_data(file_name));
	assert(db_chat_obj.remove_participant("0001") == 0);
	assert(db_chat_obj.remove_participant("0003") == -1);
	assert(db_chat_obj.remove_participant("0001") == -1);
}

void test_add_message(const std::string& file_name)
{
	Poco::JSON::Object::Ptr msg_json1 = create_msg_json("01", "0002", "12:30", "Hello. How are you?");
	std::string msg1 = stringify(msg_json1);
	Poco::JSON::Object::Ptr msg_json2 = create_msg_json("02", "0001", "12:50", "Hello. Good!");
	std:: string msg2 = stringify(msg_json2);
	Poco::JSON::Object::Ptr msg_json3 = create_msg_json("03", "0011", "12:00", "Hello.");
	std:: string msg3 = stringify(msg_json3);

	messenger::database db;
	messenger::db_chat db_chat_obj(db.read_user_data(file_name));
	assert(db_chat_obj.add_message(msg1) == 0);
	assert(db_chat_obj.add_message(msg2) == 0);
	assert(db_chat_obj.add_message(msg3) == 0);
	assert(db_chat_obj.add_message(msg1) == -1);
}

void test_search_message(const std::string& file_name)
{
	Poco::JSON::Object::Ptr msg_json1 = create_msg_json("01", "0002", "12:30", "Hello. How are you?");
	std::string msg1 = stringify(msg_json1);
	Poco::JSON::Object::Ptr msg_json2 = create_msg_json("02", "0001", "12:50", "Hello. Good!");
	std:: string msg2 = stringify(msg_json2);
	Poco::JSON::Object::Ptr msg_json3 = create_msg_json("03", "0005", "12:59", "Hello. Good!");
	std:: string msg3 = stringify(msg_json3);

	messenger::database db;
	messenger::db_chat db_chat_obj(db.read_user_data(file_name));
	assert(db_chat_obj.search_message("01") == 0);
	assert(db_chat_obj.search_message("02") == 1);
	assert(db_chat_obj.search_message("05") == -1);
}

void test_remove_message(const std::string& file_name)
{
	Poco::JSON::Object::Ptr msg_json1 = create_msg_json("01", "0002", "12:30", "Hello. How are you?");
	std::string msg1 = stringify(msg_json1);
	Poco::JSON::Object::Ptr msg_json3 = create_msg_json("03", "0005", "12:59", "Hello. Good!");
	std:: string msg3 = stringify(msg_json3);
	
	messenger::database db;
	messenger::db_chat db_chat_obj(db.read_user_data(file_name));
	assert(db_chat_obj.remove_message(msg1) == 0);
	assert(db_chat_obj.remove_message(msg3) == 0);
	assert(db_chat_obj.remove_message(msg1) == -1);
}

int main()
{
	Poco::JSON::Object::Ptr user_json = create_user_json("0001", "Anna");
	
	std::string file_name = user_json->getValue<std::string>("user_file");
	std::string user = stringify(user_json);
	
	messenger::database db;
	//test create user 
	db.create_user(file_name, user);

	//test read user data
	std::string user_info = db.read_user_data(file_name);
	std::cout << "Before user update:	" << user_info << "\n";

	test_add_contact(file_name);
	test_search_contact(file_name);
	test_remove_contact(file_name);
	test_add_chat(file_name);
	test_search_chat(file_name);
	test_remove_chat(file_name);
	user_info = db.read_user_data(file_name);
	std::cout << "After update chats list:	" << user_info << "\n";


	//chat_id empty string ?????
/*
	Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(user); //using default ParseHandler
    Poco::JSON::Object::Ptr obj = result.extract<Poco::JSON::Object::Ptr>();
   	assert(obj);
	Poco::JSON::Array::Ptr chats = obj->getArray("chats");
    assert(chats);

	std::string chat_id;
	for (int i = 0; i < chats->size(); ++i) {
		chat_id = chats->get(i).convert<std::string>();
	}
	std::cout << "chat_id:		" << chat_id << "\n";
*/

	Poco::JSON::Object::Ptr chat_json = create_chat_json("chat_0001_0002");
	file_name = chat_json->getValue<std::string>("chat_file");
	std::string chat = stringify(chat_json);
	//test create chat 
	db.create_user(file_name, chat);

	//test read user data
	std::string chat_info = db.read_user_data(file_name);
	std::cout << "Before chat update:	" << chat_info << "\n";

	test_add_participant(file_name);
	test_search_participant(file_name);
	test_remove_participant(file_name);
	user_info = db.read_user_data(file_name);
	std::cout << "After update participants list:	" << user_info << "\n";

	
	//test read user data
	chat_info = db.read_user_data(file_name);
	std::cout << "Before chat update:	" << chat_info << "\n";

	test_add_message(file_name);
	test_search_message(file_name);
	test_remove_message(file_name);
	user_info = db.read_user_data(file_name);
	std::cout << "After update message list:	" << user_info << "\n";

	return 0;
}
