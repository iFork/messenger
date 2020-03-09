
#include "server.hpp"

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/SocketAddress.h"

#include <iostream>

int hello()
{
	std::cout << "Hi from server \n";
	return 0;
}

int main()
{
	hello();
	return 0;
}
