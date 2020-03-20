#ifndef SIGNUP_HPP
#define SIGNUP_HPP

#include <QWidget>

class QLineEdit;
class QPushButton;
class QVBoxLayout;

class signup: public QWidget
{
Q_OBJECT
public:
    signup(QWidget* parent = 0);
    ~signup(){};
private:
    QVBoxLayout *m_layout;
    QLineEdit* m_user_name;
    QPushButton* m_cancel_button;
    QPushButton* m_ok_button;
signals:
    void changeStackedWidgetIndex(int);
private slots:
    void submit_form();
};

#endif // SIGNUP_HPP
