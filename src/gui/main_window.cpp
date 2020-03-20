#include "main_window.hpp"
#include "login.hpp"
#include "signup.hpp"

#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>

main_window::main_window(QWidget* parent): QMainWindow(parent)
{
   
    init_ui();
    init_connection();
}

void main_window::init_ui()
{
    stack = new QStackedWidget(this);
    m_login = new login(stack);
    m_signup = new signup(stack);

    QWidget* window = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    m_login_button = new QPushButton("Login", this);
    m_signup_button = new QPushButton("Signup", this);
    layout->addWidget(m_login_button);
    layout->addWidget(m_signup_button);
    window->setLayout(layout);
    stack->addWidget(window);
    stack->addWidget(m_login);
    stack->addWidget(m_signup);

    setWindowTitle("Messenger");
    move(550, 250);
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::lightGray);
    setPalette(palette);
  
    setCentralWidget(stack);
}

void main_window::init_connection()
{
    connect(m_login_button, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(1);
    });
    connect(m_login, &login::changeStackedWidgetIndex, 
            stack, &QStackedWidget::setCurrentIndex);
    connect(m_signup_button, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(2);
    });
    connect(m_signup, &signup::changeStackedWidgetIndex, 
            stack, &QStackedWidget::setCurrentIndex);
}

QSize main_window::sizeHint() const
{
    return QSize(250, 100);
}