#include "db_user_sample_observable.hpp"

#include <iostream>

//Implementation of db_user_observable
//C-tor
db_user_observable::db_user_observable(const std::string user_id) noexcept:
    m_user_id(user_id),
    m_signup_success_notifier(this),
    m_signup_failure_notifier(this) 
{
    std::cout << "C-tor of db_user_observable \n";
}

//Model updaters calling notifiers
void db_user_observable::create_user() //user_id, user_data
{
    //assuming create user is successful
    std::cout << "Create_user calls signup_success_notifier.notify_observers\n";
    m_signup_success_notifier.notify_observers();
    //assuming create user fails and 
    //this handled by this db_entry class and branching
    //is not in command- command passess failure cmd ..
    //or maybe calls bd_user.init(success=false)
    std::cout << "Create_user calls signup_failure_notifier.notify_observers\n";
    m_signup_failure_notifier.notify_observers();
}

//Implementation of inner notifiers 
//Implementation of db_user_observable::signup_success_notifier
//C-tor
db_user_observable::signup_success_notifier::
signup_success_notifier(db_user_observable* parent):
    m_parent(parent)
{
}
//Notifier accessors
//db_user_observable::signup_success_notifier& db_user_observable::
//get_signup_success_notifier() 
//{
//    return m_signup_success_notifier;
//}

//Implementation of db_user_observable::signup_failure_notifier
//C-tor
db_user_observable::signup_failure_notifier::
signup_failure_notifier(db_user_observable* parent):
    m_parent(parent)
{
}
//Notifier accessors
//db_user_observable::signup_failure_notifier& db_user_observable::
//get_signup_failure_notifier()
//{
//    return m_signup_failure_notifier;
//}
