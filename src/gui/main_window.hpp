#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
class QStackedWidget;
class QPushButton;
class login;
class signup;

class main_window : public QMainWindow
{
Q_OBJECT
public:
    main_window(QWidget* parent = Q_NULLPTR);
    QSize sizeHint() const;
    ~main_window(){};
private:
    QStackedWidget* stack;
    login* m_login;
    signup* m_signup;
    QPushButton* m_login_button;
    QPushButton* m_signup_button;
private:
    void init_ui();
    void init_connection();
};


#endif // MAIN_WINDOW_Hs
