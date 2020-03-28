#include <string>

class subject;
class argument;

class observer {
protected:
	//Protected data members
        //internal flags ?
public:
	//Special member functions
    observer() = default;
    observer(const observer&) = delete;
    observer& operator=(const observer&) = delete;
    observer(const observer&&) = delete;
    observer& operator=(const observer&&) = delete;
	virtual ~observer() = default;

	//Interface
	virtual void update(subject* notifier, argument* arg) noexcept = 0;	
};


