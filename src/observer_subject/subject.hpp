
#include <string>
#include <set>

class observer;
class argument {};

class subject {

protected:
	//Protected data members
	std::set<observer*> m_observers;
    //bool changed;

public:
	//Special member functions
    subject() = default;
    subject(const subject&) = delete;
    subject& operator=(const subject&) = delete;
    subject(const subject&&) = delete;
    subject& operator=(const subject&&) = delete;
	virtual ~subject() = default;


	//Interface
    void add_observer(observer& obs) noexcept;
        //non-const value-type in a set
	void remove_observer(observer& obs) noexcept;
	void remove_observers() noexcept;
    //TODO: add members for change flags


    /**
    * Notifyes the whole set of registered obeservers 
    */
	void notify_observers(argument* arg = nullptr) noexcept;
};

