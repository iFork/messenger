#include "gui_sample_observer.hpp"

#include <iostream>

//Implementation of gui_signup_page_obs
//C-tor
gui_signup_page_obs::gui_signup_page_obs(std::string name) noexcept:
    m_name(name),
    m_signup_success_observer(this),
    m_signup_failure_observer(this)
{
}

//Observer member accessors
observer& gui_signup_page_obs::get_signup_success_observer() noexcept
{
    return m_signup_success_observer;
}

observer& gui_signup_page_obs::get_signup_failure_observer() noexcept
{
    return m_signup_failure_observer;
}

//Implementation of inner observers

//Implementation of gui_signup_page_obs::signup_success_observer
//C-tor
gui_signup_page_obs::signup_success_observer::
signup_success_observer(gui_signup_page_obs* parent):
   m_parent(parent) 
{
}
//Observer interface overrides
void gui_signup_page_obs::signup_success_observer::
update(subject* notifier, argument* arg) noexcept
{
    std::cout << "Update of signup_success_observer is called \n";
}

//Implementation of gui_signup_page_obs::signup_failure_observer
//C-tor
gui_signup_page_obs::signup_failure_observer::
signup_failure_observer(gui_signup_page_obs* parent):
   m_parent(parent) 
{
}
//Observer interface overrides
void gui_signup_page_obs::signup_failure_observer::
update(subject* notifier, argument* arg) noexcept
{
    std::cout << "Update of signup_failure_observer is called \n";
}
