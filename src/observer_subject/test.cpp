
//#include "subject.hpp"
//#include "observer.hpp"

#include "gui_sample_observer.hpp"
#include "db_user_sample_observable.hpp"

class top {
public:
	//Client
    //client m_client;

	//Observers
	//gui elements
    gui_signup_page_obs m_signup_page;
	//contacts_area m_contacts_area;
	
	//Subjects
	//DB handlers or DB entries - whichever will own model updates
		//assuming model updates is owned by DB entry
	db_user_observable m_db_user;
		//or db_handler or db_user_handler
		

    //C-tor
    top(const std::string su_page_name, const std::string user_id) noexcept:
        m_signup_page(su_page_name),
        m_db_user(user_id)
    {
        //Registering observers with subjects
		//registering will allow as to call update() on all such observer upon notice
        m_db_user.m_signup_success_notifier.add_observer(
                m_signup_page.get_signup_success_observer());
        m_db_user.m_signup_failure_notifier.add_observer(
                m_signup_page.get_signup_failure_observer());
        //m_db_user->contacts_update_notifier.add_observer(m_contacts_area);
    }
	
};


int main()
{
    top app("Signup Page", "Boby");
    //Updating model which will notify signup_success_observer
    app.m_db_user.create_user();
    
    return 0;
}
