/**
 * @file client_connection_handler.hpp
 * @author XCOM
 * @brief ClientConnection class header
*/

#ifndef CLIENT_CONNECTION_HANDLER_HPP
#define CLIENT_CONNECTION_HANDLER_HPP

//3rd Party Includes
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/TCPServerConnectionFactory.h>

//Standard includes
#include <iostream>

//define values
#define SIZE 1024

using Poco::Net::TCPServerConnectionFactoryImpl;

class client_connection: public Poco::Net::TCPServerConnection
{
public:
	using TCPServerConnection = Poco::Net::TCPServerConnection;	
	using StreamSocket = Poco::Net::StreamSocket;
	using Exception = Poco::Exception;

public:
	/**
	 * @brief Def constructor
	 * @param socket not NULL
	 */
	client_connection(const StreamSocket& socket): TCPServerConnection(socket)
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

typedef TCPServerConnectionFactoryImpl<client_connection> TCPFactory;

#endif // CLIENT_CONNECTION_HANDLER_HPP