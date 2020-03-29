
#include "subject.hpp"
#include "observer.hpp" 
    //as in subject.notify.. we call observer's method
#include <iostream>

//Implementation of subject

void subject::add_observer(observer& obs) noexcept
{
    m_observers.insert(&obs);     
}

void subject::remove_observer(observer& obs) noexcept
{
    m_observers.erase(&obs);
        //Q: does algoritm dereference pointer to find the match?
}

void subject::remove_observers() noexcept
{
    m_observers.clear();
}

void subject::notify_observers(argument* arg) noexcept
{
    std::set<observer*>::iterator it;
    for(it = m_observers.begin(); it != m_observers.end(); it++) {
        (*it)->update(this, arg);
    }
}

