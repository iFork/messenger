#include "server.hpp"


#include "Poco/Net/NetException.h"

#include <iostream>

int main() {
    try {
        Server(); 
    } catch(Poco::Net::NetException& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
