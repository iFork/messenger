#include "signup.hpp"
#include "client/client.hpp"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

signup::signup(QWidget* parent): QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_user_name = new QLineEdit("", this);
    m_user_name->setPlaceholderText("Username...");
    m_ok_button = new QPushButton("Signup", this);
    m_cancel_button = new QPushButton("Cancel", this);

    m_layout->addWidget(m_user_name);
    m_layout->addWidget(m_ok_button);
    m_layout->addWidget(m_cancel_button);
    connect(m_cancel_button, &QPushButton::clicked,[=](){
            emit changeStackedWidgetIndex(0);
    });
    connect(m_ok_button, &QPushButton::clicked, this, &signup::submit_form);
}

void signup::submit_form()
{
    QString user_name = m_user_name->text().trimmed();
    if (user_name.isEmpty()) 
    {
        QMessageBox::critical(this, "Error", "Username cannot be empty");
    } 
    else if (user_name.contains(QStringLiteral(" "))) 
    {
        QMessageBox::critical(this, "Error", "Username cannot contain space");        
    } 
    else 
    {
        client client_obj;
        client_obj.sign_up_helper(user_name.toStdString());
    }
}
