#include <genesis/database/DatabaseServer.h>

#include <genesis/common/logging/Logger.h>
#include <genesis/common/configuration/ConfigManager.h>
#include <genesis/database/io/IoServer.h>

#include <thread>

/**
 * Initialise the database server
 */
void Genesis::Database::DatabaseServer::init() {

	// Inform the user that the database server is being initialised
	genesis_logger->info("Initialising database server...");

	// The database connector instance
	this->connector = new Genesis::Database::Connector::DatabaseConnector();

	// If the server could not connect to the database, throw an error
	if (!connector->connect()) {
		genesis_logger->error("Failed to connect to database!");
		exit(1);
	}

	// Inform the user that we successfully connected to the database
	genesis_logger->info("Successfully connected to the MySQL database!");

	// The io server instance
	this->io_server = new Genesis::Database::Io::IoServer();

	// The port for the io server to bind to
	auto server_port = config_manager->get_value_or_default<unsigned short>("DbServerPort", 30820);

	// The io_server thread
	std::thread thread(std::bind(&Genesis::Database::Io::IoServer::initialise, this->io_server, server_port));

	// Wait for the thread to finish, and join back to the main program thread
	thread.join();
}