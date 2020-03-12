#ifndef CHATTERBOX_HPP
#define CHATTERBOX_HPP

#include <QWidget>

class QGridLayout;
class QMenuBar;
class QMenu;
class QTextEdit;
class QLineEdit;
class QPushButton;
class QLabel;

class ChatterBox: public QWidget
{
//    Q_OBJECT
    public:
        ChatterBox(QWidget* parent = 0);
		~ChatterBox(){}
		
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

#endif
