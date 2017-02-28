#include "GenesisServer.h"
#include <iostream>
#include <boost/bind.hpp>
#include "session/ServerSession.h"

using namespace Genesis::Common::Networking::Server;

/**
 * Binds the GenesisServer instance to a specified port, and begin receiving incoming
 * network events.
 *
 * @param port
 *		The port to listen on
 *
 * @returns
 *		If the server successfully bound to a socket
 */
bool GenesisServer::bind(unsigned short port) {

	// Attempt to catch any exceptions thrown
	try {

		// Set the acceptor options
		this->acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));

		// Begin listening for incoming connections
		this->acceptor.listen();

		// Begin accepting incoming connections
		this->begin_accept();

		// Run the io_service instance
		this->io_service.run();

	// Catch a boost system error, if thrown.
	} catch (const boost::system::system_error& error) {
		return false;
	}

	// Return true if everything was successful
	return true;
}

/**
 * Begins accepting incoming connections.
 *
 * @param io_service
 *		The boost::asio::io_service instance to operate on
 *
 * @param acceptor
 *		The acceptor instance to use
 */
void GenesisServer::begin_accept() {

	// The session instance
	auto session = new Genesis::Common::Networking::Server::Session::ServerSession(io_service);

	// Begin accepting a connection
	this->acceptor.async_accept(session->get_socket(), boost::bind(&GenesisServer::handle_accept, this, session, boost::asio::placeholders::error));
}

/**
 * Handles the accepting of an incoming connection, and the session creation.
 *
 * @param session
 *		The session instance
 *
 * @param error
 *		The error code
 */
void GenesisServer::handle_accept(Genesis::Common::Networking::Server::Session::ServerSession *session, const boost::system::error_code &error) {

	// If an error occurred, delete the session
	if (error) delete session; else {

		// Call the connect function
		this->connect_function(session);

		// Begin reading incoming packets
		session->get_socket().async_read_some(boost::asio::buffer(session->get_buffer(), MAX_PACKET_LENGTH), boost::bind(&GenesisServer::handle_read, this, session, session->get_buffer(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

	// Begin accepting a new connection
	this->begin_accept();
}

/**
 * Handles a read event from a connected session
 *
 * @param session
 *		The session that is sending the data
 *
 * @param data
 *		The data received
 *
 * @param error
 *		The error code
 *
 * @param bytes_read
 *		The amount of bytes read
 */
void GenesisServer::handle_read(Genesis::Common::Networking::Server::Session::ServerSession* session, uint8_t* data, const boost::system::error_code &error, unsigned int bytes_read) {

	// If an error was thrown, terminate the session and discontinue
	if (error && bytes_read == 0) {
		this->terminate_function(session);
		return;
	}

	// Pass the data to the receive function
	this->receive_function(session, data, bytes_read);

	// Begin reading incoming packets
	session->get_socket().async_read_some(boost::asio::buffer(session->get_buffer(), MAX_PACKET_LENGTH), boost::bind(&GenesisServer::handle_read, this, session, session->get_buffer(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}