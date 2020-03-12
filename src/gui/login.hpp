#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QWidget>

class QLineEdit;
class QPushButton;
class QVBoxLayout;

class Login: public QWidget
{
//    Q_OBJECT
    public:
        Login(QWidget* parent = 0);
        ~Login(){};
    private:
        QVBoxLayout *m_layout;
        QLineEdit* m_user_name;
        QPushButton* m_cancel_button;
        QPushButton* m_ok_button;
};

#endif
