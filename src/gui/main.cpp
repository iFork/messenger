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
#include "main_window.hpp"
#include "chat_box.hpp"

// Headers from third party libraries
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    main_window window;
    window.show();
    return app.exec();
}
