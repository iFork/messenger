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
 * @brief Definition of class chat_box
 * It displays the interface of the main window
 * with the logged in user's data (user name, messages)
 * It gives opportunity to send/receive  messages to/from other users.
 * There are many other options that can be implemented request later on.
 */

class chat_box: public QWidget
{
    Q_OBJECT
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
    public:
    /**
     * @brief constructor
     */
    chat_box(QWidget* parent = Q_NULLPTR);
    /**
     * @brief prevent copy constructor
     */
    chat_box(const chat_box&) = delete;
     /**
     * @brief prevent assignment operator
     */
    chat_box& operator=(const chat_box&) = delete;
    /**
     * @brief prevent move constructor
     */
    chat_box(const chat_box&&) = delete;
    /**
     * @brief prevent move assignment operator
     */
    chat_box& operator=(const chat_box&&) = delete;
    /**
     * @brief destructor
     */
    ~chat_box(){};
};

#endif // CHAT_BOX
