#include "subject.hpp"

//example classes inheriting subject interface in inner classes

class db_user_observable {
protected:
    //Dummy data members
    std::string m_user_id;
//private:
public:
    //Specific notifiers as *private* inner classes
    
    //Notifier: signup_success_notifier
    //forward declaring inner class for befriending
    class signup_success_notifier;
    friend class signup_success_notifier;
    class signup_success_notifier : public subject {
    private:
        //pointer to parrent class
        db_user_observable* m_parent;
        //some flag for beeing already notified
        
    public:
        //C-tor
        signup_success_notifier(db_user_observable* parent);
            //set inner flags to off/default
        //Subject interface overrides
        //void notify_observers(argument* arg) noexcept override;    
            //yet no need if we do not add specific internal 
            //checks to dispatch subject::notify_observers()
    };

    //Notifier: signup_failure_notifier
    //forward declaring inner class for befriending
    class signup_failure_notifier;
    friend class signup_failure_notifier;
    class signup_failure_notifier : public subject {
    private:
        //pointer to parrent class
        db_user_observable* m_parent;
        //some flag for beeing already notified
        
    public:
        //C-tor
        signup_failure_notifier(db_user_observable* parent);
            //set inner flags to off/default
        //Subject interface overrides
        //void notify_observers(argument* arg) noexcept override;    
            //yet no need if we do not add specific internal 
            //checks to dispatch subject::notify_observers()
    };

    //Notifier members
    signup_success_notifier m_signup_success_notifier;
    signup_failure_notifier m_signup_failure_notifier;

public:
    //Notifier accessors - to then get access to public methods of
    //private nested classes
    //signup_success_notifier& get_signup_success_notifier();
    //signup_failure_notifier& get_signup_failure_notifier();
        //no const

    //Special member functions
    //C-tor
    db_user_observable(const std::string user_id) noexcept;
        //init notifier members

    //Model updaters calling notifier.notify_observers
    void create_user(); //user_id, user_data
        //TODO:DISCUSS: 
        //only from client end there are observers, but from server end
        //there are no observers
        //BUT always notify, as function is same at both ends  ?
            //may consider double dipatching when db_handler will call
            //different create_user funcs depending whether input is response or request
    
    /*
    //DISCUSS: for failure at server end
            no observers
        for failure at client end
            if user_id availability is checked by command
            response comes with failure 
            Cannot register Observers with come-and-go subjects (commands)
        
            Alternative: use session persistant subjects/observables 
                e.g. DB
                BUT how DB will call failure notifiers 
                    have objects for each model element (db_user, db_chat, etc)
                    to register obeservers with their notifiers 
    */

	//void add_contact(std::string user_id);
		//TODO: 
		//will have several types of observers e.g.
		//success_notifier::notify_all_observers()
		// or failure_notifier::notify_all_observers();
};
