#include "GenesisClient.h"
#include "../../logging/Logger.h"

bool Genesis::Common::Networking::Client::GenesisClient::connect(std::string address, unsigned short port) {

	// Attempt to catch any exceptions thrown
	try {

		// The port string
		std::string port_string = std::to_string(port);

		// The tcp resolver instance
		boost::asio::ip::tcp::resolver resolver(this->io_service);

		// The resolver query, to find the server to connect to
		boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), address, port_string);

		// The query iterator
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

		// Connect to the server
		boost::asio::connect(this->socket, iterator);

	// Catch an exception
	} catch (std::exception &e) {
		genesis_logger->error(e.what());
		return false;
	}

	// Return the state of the socket
	return this->socket.is_open();
}