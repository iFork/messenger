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
#include "login.hpp"
#include "chat_box.hpp"

// Headers from third party libraries
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // main window
    ChatBox chatbox;
    QPalette pal = chatbox.palette();
    pal.setColor(QPalette::Window, Qt::lightGray);
    chatbox.setGeometry(380, 100, 600, 450);
    chatbox.setPalette(pal);
    chatbox.show();

    // login window that will be included
    // into main window later on
    Login login;
    login.setGeometry(550, 250, 250, 100);
    login.setWindowTitle("Login");
    login.setPalette(pal);
    login.show();

    return app.exec();
}
