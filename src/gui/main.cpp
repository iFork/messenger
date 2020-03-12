#include "login.hpp"
#include "chat_box.hpp"
#include <QApplication>
#include "commands/commands.hpp"
#include "client/client.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    ChatterBox chatterbox;
    QPalette pal = chatterbox.palette();
    pal.setColor(QPalette::Window, Qt::lightGray);
    chatterbox.setGeometry(380, 100, 600, 450);
    chatterbox.setPalette(pal);
    chatterbox.show();

    Login login;
    login.setGeometry(550, 250, 250, 100);
    login.setWindowTitle("Login");
    login.setPalette(pal);
    login.show();

    return app.exec();
}
