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
#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_SERVERLISTREQUESTHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_SERVERLISTREQUESTHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
#include <genesis/database/DatabaseServer.h>

#include <genesis/common/database/structs/auth/Server.h>

#include <genesis/common/networking/packets/PacketBuilder.h>

#include <iostream>

namespace Genesis::Database::Io::Packets::Impl {
	class ServerListRequestHandler : public PacketHandler {

		/**
		 * Handles a server list request from the authentication server
		 *
		 * @param session
		 *		The session instance
		 *
		 * @param length
		 *		The length of the packet
		 *
		 * @param opcode
		 *		The opcode of the incoming packet
		 *
		 * @param data
		 *		The packet data
		 */
		bool handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned int request_id, unsigned char* data) override {

			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

			// Write the request id
			bldr->write_int(request_id);

			// The MySQL connection
			auto connection = Genesis::Database::DatabaseServer::get_instance()->get_connector()->get_connection();

			// The statement and result instances
			auto statement = connection->createStatement();

			// Select the server data
			statement->execute("SELECT * FROM genesis_gamedata.world_status");

			// The result set
			std::auto_ptr<sql::ResultSet> result;

			// Fetch the result set
			result.reset(statement->getResultSet());

			// Write the number of servers
			bldr->write_byte(result->rowsCount());

			// Loop through the results
			while (result->next()) {

				// The server instance
				Genesis::Common::Database::Structs::Auth::Server server;

				// Define the server details
				server.server_id = (unsigned char) result->getInt("server_id");
				server.population = (unsigned short) result->getInt("population");
				server.status = (unsigned char) result->getInt("status");
				server.max_players = (unsigned short) result->getInt("max_players");
				server.client_version = (unsigned int) result->getInt("client_version");

				// The ip address and server name
				const char* ip_address = result->getString("ip_address").c_str();
				const char* server_name = result->getString("server_name").c_str();

				// Copy the server name and ip address
				std::copy(ip_address, ip_address + 15, server.ip_address);
				std::copy(server_name, server_name + 32, server.server_name);

				// The byte array
				unsigned char struct_array[sizeof(server)];
				memcpy(struct_array, &server, sizeof(server));

				// Write the server instance
				bldr->write_bytes(struct_array, sizeof(struct_array));
			}

			// Close the statement
			statement->close();
			
			// Delete the statement instance
			delete statement;

			// Delete the connection
			delete connection;
			
			// Write the packet
			session->write(bldr->to_packet());

			// Delete the packet builder
			delete bldr;

			// Return true
			return true;
		}
	};
}
#endif