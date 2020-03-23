/**
 * @file chat_box.hpp
 *
 * @author ITC students 2020
 * E-mail: xxx@xxxxx.xxx
 * 134/1 Tsarav Aghbyur St.,
 * Yerevan, 0052, Armenia
 * Tel:  xxxxxx
 */

#ifndef CHAT_BOX_HPP
#define CHAT_BOX_HPP

// Headers from third party libraries
#include <QWidget>

// Forward declarations
class QGridLayout;
class QMenuBar;
class QMenu;
class QTextEdit;
class QLineEdit;
class QPushButton;
class QLabel;

/**
 *@brief Definition of class ChatterBox
 * It display the interface of the main window
 * with the logged in user's data (user name, messages)
 * It gives opportunity to send/receive  messages with the other user.
 * There are many other options that can be implemented request later on.
 */

class ChatBox: public QWidget
{
    Q_OBJECT
    public:
    //Constructor
    ChatBox(QWidget* parent = Q_NULLPTR);
    ///Destructor
    ~ChatBox(){};
    private:
        QGridLayout* m_glayout;
        QMenuBar* m_menu_bar;
        QMenu* m_file_menu;
        QMenu* m_view_menu;
        QMenu* m_options_menu;
        QMenu* m_help_menu;
        QTextEdit* m_chat_display;
        QLineEdit* m_message_line;
        QPushButton* m_send_button;
        QPushButton* m_new_group;
        QLabel* m_name;
        QLabel* m_voice;
        QLabel* m_video;
        QLabel* m_camera;
        QLabel* m_gallery;
        QLabel* m_attach;
        QLabel* m_smile;
};

#endif // CHAT_BOX
