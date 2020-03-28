#include "observer.hpp"

//example classes inheriting subject interface in inner classes

class gui_signup_page_obs {
protected:
    //Dummy data members
    std::string m_name;

private:

    //Specific observers as *private* inner classes

    //Observer: signup_success_observer
    //forward declaring inner class for befriending
    class signup_success_observer;
    friend class signup_success_observer;
    class signup_success_observer : public observer {
    private:
        //pointer to parrent class
        gui_signup_page_obs* m_parent;
    public:
        //C-tor
        signup_success_observer(gui_signup_page_obs* parent);
        //Observer interface overrides
        void update(subject* notifier, argument* arg) noexcept override;
    };

    //Observer: signup_failure_observer
    //forward declaring inner class for befriending
    class signup_failure_observer;
    friend class signup_failure_observer;
    class signup_failure_observer : public observer {
    private:
        //pointer to parrent class
        gui_signup_page_obs* m_parent;
    public:
        //C-tor
        signup_failure_observer(gui_signup_page_obs* parent);
        //Observer interface overrides
        void update(subject* notifier, argument* arg) noexcept override;
    };

    //Private observer members
    signup_success_observer m_signup_success_observer;
    signup_failure_observer m_signup_failure_observer;

public:
    //Observer member accessors
    observer& get_signup_success_observer() noexcept;
    observer& get_signup_failure_observer() noexcept;

    //Special member functions
    //C-tor
    gui_signup_page_obs(std::string name) noexcept; 

};
