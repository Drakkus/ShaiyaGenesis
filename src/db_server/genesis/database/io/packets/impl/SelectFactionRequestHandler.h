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
#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_SELECTFACTIONREQUESTHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_SELECTFACTIONREQUESTHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
#include <genesis/database/DatabaseServer.h>

#include <genesis/common/logging/Logger.h>

#include <iostream>
#include <string>

namespace Genesis::Database::Io::Packets::Impl {
	class SelectFactionRequestHandler : public PacketHandler {

		/**
		 * Handles the selection of a faction for the player
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

			// The player id and faction
			unsigned int player_id;
			unsigned char faction;
			unsigned char server_id;

			// Copy the player id, faction and server id
			std::memcpy(&player_id, data, sizeof(player_id));
			std::memcpy(&faction, data + sizeof(player_id), sizeof(faction));
			std::memcpy(&server_id, (data + sizeof(player_id) + sizeof(faction)), sizeof(server_id));

			// Attempt to catch any exceptions
			try {

				// The MySQL connection
				auto connection = Genesis::Database::DatabaseServer::get_instance()->get_connector()->get_connection();

				// The statement and result instances
				auto statement = connection->prepareStatement("UPDATE genesis_userdata.users_master SET faction = ? WHERE user_id = ?");
				auto delete_char_statement = connection->prepareStatement("UPDATE genesis_gamedata.characters SET is_deleted = 1, deletion_date = now() WHERE user_id = ? AND server_id = ?");

				// Define the faction
				statement->setInt(1, faction);

				// Define the user id
				statement->setInt(2, player_id);
				delete_char_statement->setInt(1, player_id);

				// Define the faction
				delete_char_statement->setInt(2, faction);
				
				// Execute the statement
				statement->execute();
				delete_char_statement->execute();

				// Close the statement
				statement->close();
				delete_char_statement->close();
				
				// Delete the statement instance
				delete statement;
				delete delete_char_statement;

				// Delete the connection
				delete connection;

			} catch (sql::SQLException &e) {
				
				// Log the exception
				genesis_logger->error(e.what());
			}

			// Return true
			return true;
		}
	};
}
#endif