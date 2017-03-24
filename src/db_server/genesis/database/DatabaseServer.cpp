/*
* Copyright (C) 2017 Shaiya Genesis <http://www.shaiyagenesis.com/>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
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