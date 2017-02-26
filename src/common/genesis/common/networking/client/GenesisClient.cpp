#include "GenesisClient.h"
#include "../../logging/Logger.h"

#include <thread>
#include <chrono>
#include <iostream>

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

		// The endpoint
		boost::asio::ip::tcp::resolver::iterator end;

		// The system error
		boost::system::error_code error = boost::asio::error::host_not_found;

		// Loop until no error occurs
		while (error && iterator != end) {
			this->socket.close();
			this->socket.connect(*iterator++, error);
		}
		
		// If we still have an error, return false
		if (error) {
			return false;
		}

		// Begin reading some data
		this->socket.async_read_some(boost::asio::buffer(this->data, MAX_PACKET_LENGTH), boost::bind(&Genesis::Common::Networking::Client::GenesisClient::handle_read, this, this->data, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

		// Run the io_service instance
		this->io_service.run();
		
		// Return if the socket is connected
		return this->socket.is_open();

	// Catch an exception
	} catch (std::exception &e) {
		genesis_logger->error(e.what());
	}

	// Return false if an error occurred
	return false;
}

void Genesis::Common::Networking::Client::GenesisClient::handle_read(unsigned char* data, const boost::system::error_code &error, unsigned int bytes_read) {
	
	// If an error occurred, close the connection
	if (error) {
		if (this->socket.is_open()) {
			this->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			this->socket.close();
		}

		// Log the error
		genesis_logger->error("Error occured in GenesisClient! Aborting process...");
		exit(1);
	}

	// Call the receive function
	this->receive_function(data, bytes_read);

	// Begin reading some data
	this->socket.async_read_some(boost::asio::buffer(this->data, MAX_PACKET_LENGTH), boost::bind(&Genesis::Common::Networking::Client::GenesisClient::handle_read, this, this->data, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}