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
#ifndef GENESIS_AUTH_AUTHSERVER_H
#define GENESIS_AUTH_AUTHSERVER_H

#include <genesis/common/networking/client/GenesisClient.h>
#include <genesis/common/database/structs/auth/Server.h>

#include <vector>
#include <mutex>

// Forward declaration of the IoServer
namespace Genesis::Auth::Io { class IoServer; }

/**
 * The authentication server singleton, which is used to handle the networking, communication
 * and encryption generation.
 */
namespace Genesis::Auth {
	class AuthServer {

		public:

			// Gets the singleton instance for this auth server
			static AuthServer* get_instance() {
				static AuthServer instance;
				return &instance;
			}

			// Initialise the auth server
			void init();

			// Update the server list
			void update_server_list();

			// Gets the database client instance
			Genesis::Common::Networking::Client::GenesisClient* get_db_client() {
				return this->db_client;
			}

			// Gets the server list
			std::vector<Genesis::Common::Database::Structs::Auth::Server>* get_servers() {
				return &servers;
			}
			
			// Get the server list mutex
			std::mutex* get_list_mutex() {
				return &list_mutex;
			}
			
		private:

			// The server list mutex
			std::mutex list_mutex;

			// The server data
			std::vector<Genesis::Common::Database::Structs::Auth::Server> servers;

			// The IoServer instance
			Genesis::Auth::Io::IoServer* io_server;

			// The GenesisClient instance
			Genesis::Common::Networking::Client::GenesisClient* db_client;
	};
}
#endif