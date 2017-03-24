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
#include <genesis/auth/AuthServer.h>
#include <genesis/auth/io/IoServer.h>

#include <genesis/common/logging/Logger.h>
#include <genesis/common/configuration/ConfigManager.h>

#include <thread>
#include <chrono>

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
	this->db_client = new Genesis::Common::Networking::Client::GenesisClient(io_service);

	// The database server connection thread
	std::thread dbserver_thread(std::bind(&Genesis::Common::Networking::Client::GenesisClient::connect, this->db_client, dbserver_address, dbserver_port));

	// Inform the user that we connected to the database server
	genesis_logger->info("Successfully connected to the database server!");

	// The server list update thread
	std::thread list_thread(std::bind(&Genesis::Auth::AuthServer::update_server_list, this));

	// The port for the io server to bind to
	auto server_port = config_manager->get_value_or_default<unsigned short>("AuthServerPort", 30800);

	// The io_server thread
	std::thread thread(std::bind(&Genesis::Auth::Io::IoServer::initialise, this->io_server, server_port));

	// Wait for the update list thread to finish
	list_thread.join();
	
	// Wait for the database connection to finish
	dbserver_thread.join();

	// Wait for the thread to finish, and join back to the main program thread
	thread.join();
}

void Genesis::Auth::AuthServer::update_server_list() {

	// The server update delay
	int update_delay = config_manager->get_value_or_default<unsigned int>("WorldStatusUpdateDelay", 30);

	// Wait 2 seconds to connect to the database server
	std::this_thread::sleep_for(std::chrono::seconds(2));

	// Loop and update the server list every 30s
	while (true) {

		// The packet builder instance, to load the server list data
		auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(2);

		// Write the packet
		db_client->write(bldr->to_packet(), [&](unsigned char* data, unsigned int length) {
		
			// The number of servers to choose from
			unsigned char server_count = (data[0] & 0xFF);

			// Lock the server list mutex
			this->list_mutex.lock();

			// Clear the server list vector
			this->servers.clear();

			// Loop through the servers
			for (int i = 0; i < server_count; i++) {

				// The server stucture
				Genesis::Common::Database::Structs::Auth::Server server;

				// Copy the data
				memcpy(&server, (data + 1 + (i * sizeof(server))), sizeof(server));

				// Define the server
				this->servers.push_back(server);	
			}

			// Unlock the mutex
			this->list_mutex.unlock();
		});

		// Delete the packet builder instance
		delete bldr;

		// Wait the update delay
		std::this_thread::sleep_for(std::chrono::seconds(update_delay));
	}

}