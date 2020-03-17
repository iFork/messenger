/**
 * @file client_connection_handler.hpp
 * @author XCOM
 * @brief ClientConnection class header
*/

#ifndef CLIENT_CONNECTION_HANDLER_HPP
#define CLIENT_CONNECTION_HANDLER_HPP

//Includes project relates headers
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"

//Standard includes
#include <iostream>

//define values
#define SIZE 1024

using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactoryImpl;
using Poco::Net::StreamSocket;
using Poco::Exception;

class ClientConnection: public TCPServerConnection
{
public:
	/**
	 * @brief Def constructor
	 */
	ClientConnection(const StreamSocket& s): TCPServerConnection(s)
	{
	}

	/**
	 * @brief run function is calling when connection is handled
	 */
	void run()
	{
		StreamSocket& ss = socket();
		try
		{
			char buffer[SIZE];
			int n = ss.receiveBytes(&buffer, sizeof(buffer));
			while (n > 0)
			{
				std::cout << "Received " << n << " bytes:" << std::endl;
				std::cout << buffer << std::endl;
				n = ss.receiveBytes(buffer, SIZE);
			}
		}
		catch (Exception& exc)
		{
			std::cerr << "ClientConnection: " << exc.displayText() << std::endl;
		}
	}
};

typedef TCPServerConnectionFactoryImpl<ClientConnection> TCPFactory;

#endif // CLIENT_CONNECTION_HANDLER_HPP