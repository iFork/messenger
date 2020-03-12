/**
 * @file /chat_box.hpp
 *
 * @author ITC students, 2020
 * E-mail: xxx@xxx.xxx
 * 134/1 Tsarav Aghbyur St.,
 * Yerevan, 0052, Armenia
 * Tel:  xxxxxx
 */

// Headers from this project
#include "chat_box.hpp"

// Forward declarations
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QtGui>
#include <QScrollArea>
#include <QFrame>

// it will be removed as soon as the users' list
// with add/remove option will be implemented
const int FRIENDS_COUNT = 30;

/**
 * ChatBox constructor that displays the interface of the main window
 * of the logged in user's data (user name, messages).
 * It gives opportunity to send/receive  messages with the other user.
 * There are many other options that can be implemented by request later on.
 */

ChatBox::ChatBox(QWidget* parent): QWidget(parent)
{
    m_glayout = new QGridLayout(this);
    m_menu_bar = new QMenuBar(this);
    m_file_menu = new QMenu("File");
    m_view_menu = new QMenu("View");
    m_options_menu = new QMenu("Options");
    m_help_menu = new QMenu("Help");

    m_file_menu->addAction("Sign in");
    m_file_menu->addAction("Sign up");
    m_file_menu->addAction("Log out");

    m_view_menu->addAction("Font");
    m_view_menu->addAction("Font colors");
    m_view_menu->addAction("Background colors");

    m_options_menu->addAction("Save");
    m_options_menu->addAction("Add friend");

    m_help_menu->addAction("About");
    m_menu_bar->addMenu(m_file_menu);
    m_menu_bar->addMenu(m_view_menu);
    m_menu_bar->addMenu(m_options_menu);
    m_menu_bar->addMenu(m_help_menu);

    m_name = new QLabel(this);
    m_name->setText("user/group name");
    m_name->setStyleSheet("border: 1px solid white;");

    m_video = new QLabel(this);
    m_video->setStyleSheet("image:url(src/res/img/video_camera.png);");
    m_video->setMinimumSize(10, 10);

    m_voice = new QLabel(this);
    m_voice->setStyleSheet("image:url(src/res/img/voice_call.png);");
    m_voice->setMinimumSize(10, 10);

    m_new_group = new QPushButton("New Group", this);

    m_camera = new QLabel(this);
    m_gallery = new QLabel(this);
    m_attach = new QLabel(this);
    m_smile = new QLabel(this);

    m_gallery->setStyleSheet("image:url(src/res/img/gallery.png);");
    m_gallery->setMinimumSize(10, 10);
    m_camera->setStyleSheet("image:url(src/res/img/camera.png);");
    m_camera->setMinimumSize(10, 10);
    m_attach->setStyleSheet("image:url(src/res/img/attach.png);");
    m_attach->setMinimumSize(10, 10);
    m_smile->setStyleSheet("image:url(src/res/img/smiley.png);");
    m_smile->setMinimumSize(10, 10);

    QScrollArea* scroll_area = new QScrollArea(this);
    QFrame* frame = new QFrame();
    QVBoxLayout* layout = new QVBoxLayout(frame);
    scroll_area->setWidget(frame);
    scroll_area->setWidgetResizable(true);
    for (int i = 1; i < FRIENDS_COUNT; i++) {
        // every 4th friend show in yellow (online)
        if (i % 4) {
            QLabel* offline_label = new QLabel("", this);
            offline_label->setText("USER " + QString::number(i));
            offline_label->setStyleSheet("border: 2px solid gray;\
                                          border-radius: 10px;\
                                          background: white;\
                                          color: gray");
            layout->addWidget(offline_label);
        } else {
            QLabel* online_label  = new QLabel("", this);
            online_label->setText("USER " + QString::number(i) + "*");
            online_label->setStyleSheet("border: 2px solid gray;\
                                         border-radius: 10px;\
                                         background: gray;\
                                         color: white");
            layout->addWidget(online_label);
        }
    }
    m_chat_display = new QTextEdit("", this);
    m_chat_display->setReadOnly(true);
    m_chat_display->setPlaceholderText("Display group conversation...");
    m_message_line = new QLineEdit("", this);
    m_message_line->setPlaceholderText("Enter your message...");
    m_send_button = new QPushButton(">>", this);
    m_send_button->setStyleSheet("border-radius: 10px;\
                                  border: 2px solid gray;\
                                  background: gray;\
                                  color: white");
    //elements have been positioned using grid layout
    m_glayout->addWidget(m_menu_bar, 0, 0);
    m_glayout->addWidget(scroll_area, 1, 0, 13, 3);
    m_glayout->addWidget(m_name, 1, 3, 1, 2);
    m_glayout->addWidget(m_voice, 1, 10, 1, 1);
    m_glayout->addWidget(m_video, 1, 11, 1, 1);
    m_glayout->addWidget(m_chat_display, 2, 3, 20, 9);
    m_glayout->addWidget(m_new_group, 23, 0, 1, 3);
    m_glayout->addWidget(m_camera, 23, 3, 1, 1);
    m_glayout->addWidget(m_gallery, 23, 4, 1, 1);
    m_glayout->addWidget(m_attach, 23, 5, 1, 1);
    m_glayout->addWidget(m_smile, 23, 6, 1, 1);
    m_glayout->addWidget(m_message_line, 23, 7, 1, 4);
    m_glayout->addWidget(m_send_button, 23, 11, 1, 1);
}
