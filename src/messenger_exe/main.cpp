/**
 * @file messenger_exe/main.cpp
 *
 * @author ITC students, 2020
 * E-mail: xxx@xxx.xxx
 * 134/1 Tsarav Aghbyur St.,
 * Yerevan, 0052, Armenia
 * Tel:  xxxxxx
 */

// includes from this project
#include "../parser/json_parser.hpp"
#include "gui/main_window.hpp"
#include "client/client.hpp"

// includes from QT libraries
#include <QApplication>

// includes from PoCo libraries
#include <Poco/Net/NetException.h>

int main(int argc, char* argv[])
{
	Poco::JSON::Object::Ptr json_object_value;
	messenger::parser::parsing_from_txt_to_json(json_object_value);
	// opens the chat window
	//
    QApplication app(argc, argv);
    main_window window;
    window.show();
	// creating client connection
	//
    try 
    {
      client(); 
    } catch(Poco::Net::NetException& e) {
        std::cout << e.what() << std::endl;
    }
    return app.exec();
}
