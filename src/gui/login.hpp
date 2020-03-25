#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QWidget>
#include <string>

class QLineEdit;
class QPushButton;
class QVBoxLayout;

class login: public QWidget
{
Q_OBJECT
public:
    login(QWidget* parent = Q_NULLPTR);
    ~login(){};
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

#endif // LOGIN_HPP
