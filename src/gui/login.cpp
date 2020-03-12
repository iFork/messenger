#include "login.hpp"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

Login::Login(QWidget* parent): QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_user_name = new QLineEdit("", this);
    m_user_name->setPlaceholderText("Enter username...");
    m_ok_button = new QPushButton("OK", this);
    m_cancel_button = new QPushButton("Cancel", this);

    m_layout->addWidget(m_user_name);
    m_layout->addWidget(m_ok_button);
    m_layout->addWidget(m_cancel_button);
}
