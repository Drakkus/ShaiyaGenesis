#include <genesis/database/io/IoServer.h>

#include <genesis/common/networking/server/GenesisServer.h>
#include <genesis/common/configuration/ConfigManager.h>
#include <genesis/common/networking/server/session/ServerSession.h>
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/packets/Opcodes.h>
#include <genesis/common/logging/Logger.h>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <iomanip>

// An alias for the name space
using namespace Genesis::Database::Io;

/**
 * Initialise the IoServer instance, and listen on a specified address and port.
 *
 * @param address
 *		The local address to listen on
 *
 * @param port
 *		The port to listen on
 *
 * @returns
 *		If the server was successfully initialised
 */
bool IoServer::initialise(unsigned short port) {
	
	// The io service to operate on
	boost::asio::io_service io_service;

	// The GenesisServer instance
	auto server = new Genesis::Common::Networking::Server::GenesisServer(io_service, port);

	// Define the network events
	server->on_connect(std::bind(&IoServer::on_connect, this, std::placeholders::_1));
	server->on_receive(std::bind(&IoServer::on_receive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	server->on_send(std::bind(&IoServer::on_send, this, std::placeholders::_1));
	server->on_terminate(std::bind(&IoServer::on_terminate, this, std::placeholders::_1));

	// Return if the server managed to successfully bind to a port specified
	return server->bind(port);
}

/**
 * Called whenever an on_connect event is received by the server.
 *
 * @param session
 *		The session instance
 */
void IoServer::on_connect(Genesis::Common::Networking::Server::Session::ServerSession* session) {

	// The list of allowed hosts
	auto hosts = config_manager->get_value_or_default<std::string>("AllowedHosts", "127.0.0.2");

	// A vector containing the allowed hosts
	std::vector<std::string> allowed_hosts;

	// Split the string
	boost::split(allowed_hosts, hosts, boost::is_any_of(";"));

	// If the host matches
	bool matches = false;

	// Loop through the hosts
	for (auto &&host : allowed_hosts) {
		if (session->get_remote_address() == host)
			matches = true;
	}

	// If the host doesn't match
	if (!matches) {
		genesis_logger->error(boost::str(boost::format("Connection denied from address: %s. Not whitelisted!") % session->get_remote_address().c_str()));
		session->close();
	}
}

/**
 * Called whenever an on_receive event is received by the server, which signifies
 * an incoming packet from an existing connection.
 */
void IoServer::on_receive(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned char* data, unsigned int bytes_read) {

	
}

/**
 * Called whenever an on_send event is received by the server, which signifies
 * an outgoing packet from an existing connection.
 */
void IoServer::on_send(char* name) {

}

/**
 * Called whenever an on_terminate event is received by the server, which signifies
 * an existing connection that has had it's connection terminated.
 */
void IoServer::on_terminate(Genesis::Common::Networking::Server::Session::ServerSession* session) {
	
}