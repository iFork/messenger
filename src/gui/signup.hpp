#ifndef SIGNUP_HPP
#define SIGNUP_HPP

// includes from QT library
#include <QWidget>
#include <string>

// forward declarations from QT library
class QLineEdit;
class QPushButton;
class QVBoxLayout;

class signup: public QWidget
{
Q_OBJECT
public:
    signup(QWidget* parent = Q_NULLPTR);
    ~signup(){};
    void handle_submit_success();
    void handle_submit_fail(const std::string& error_message);
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
