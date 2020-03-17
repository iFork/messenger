#include "client.hpp"

#include "Poco/Net/NetException.h"

#include <iostream>

int main() {
    
    try {
        Client(); 
    } catch(Poco::Net::NetException& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}

