#include <genesis/auth/AuthServer.h>
#include <genesis/auth/io/IoServer.h>

#include <genesis/common/logging/Logger.h>
#include <genesis/common/configuration/ConfigManager.h>
#include <genesis/common/networking/client/GenesisClient.h>

#include <thread>

/**
 * Initialise the authentication server
 */
void Genesis::Auth::AuthServer::init() {

	// Inform the user that the authentication server is being initialised
	genesis_logger->info("Initialising authentication server...");

	// The io server instance
	this->io_server = new Genesis::Auth::Io::IoServer();

	// The address and port of the database server
	auto dbserver_address = config_manager->get_value_or_default<std::string>("DbServerAddress", "127.0.0.1");
	auto dbserver_port = config_manager->get_value_or_default<unsigned short>("DbServerPort", 30820);

	// The io service to operate on
	boost::asio::io_service io_service;

	// The client instance
	auto client = new Genesis::Common::Networking::Client::GenesisClient(io_service);

	// Connect to the db server
	if (!client->connect(dbserver_address, dbserver_port)) {
		genesis_logger->error("Failed to connect to database server!");
		exit(1);
	}
	genesis_logger->info("Connected to database server");
	
	// The port for the io server to bind to
	auto server_port = config_manager->get_value_or_default<unsigned short>("AuthServerPort", 30800);

	// The io_server thread
	std::thread thread(std::bind(&Genesis::Auth::Io::IoServer::initialise, this->io_server, server_port));

	// Wait for the thread to finish, and join back to the main program thread
	thread.join();
}