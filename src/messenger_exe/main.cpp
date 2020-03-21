/**
 * @file /main.cpp
 *
 * @author ITC students, 2020
 * E-mail: xxx@xxx.xxx
 * 134/1 Tsarav Aghbyur St.,
 * Yerevan, 0052, Armenia
 * Tel:  xxxxxx
 */

// Headers from this project
#include "../gui/main_window.hpp"
#include "../gui/chat_box.hpp"
#include "../gui/login.hpp"
#include "../gui/signup.hpp"
#include "../client/client.hpp"

// Headers from third party libraries
#include <QWidget>
#include <QMainWindow>
#include <QApplication>

#include "Poco/Net/NetException.h"

#include <iostream>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    main_window window;
    window.show();
    try 
    {
      client(); 
    } catch(Poco::Net::NetException& e) 
    {
        std::cout << e.what() << std::endl;
    }
    return app.exec();
}
