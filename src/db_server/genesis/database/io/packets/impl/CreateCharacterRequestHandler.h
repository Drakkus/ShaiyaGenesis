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
#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_CREATECHARACTERREQUESTHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_CREATECHARACTERREQUESTHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
#include <genesis/database/DatabaseServer.h>

#include <genesis/common/database/structs/game/CreateCharacterRequest.h>
#include <genesis/common/networking/packets/PacketBuilder.h>

#include <iostream>

namespace Genesis::Database::Io::Packets::Impl {
	class CreateCharacterRequestHandler : public PacketHandler {

		/**
		 * Handles the creation of a character
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

			// The creation request
			Genesis::Common::Database::Structs::Game::CreateCharacterRequest request;

			// The server id
			unsigned char server_id = data[0] & 0xFF;

			// The player id
			unsigned int player_id = ((data[1] & 0xFF) + ((data[2] & 0xFF) << 8) + ((data[3] & 0xFF) << 16) + ((data[4] & 0xFF) << 24));

			// Copy the data into the request instance
			std::memcpy(&request, data + 5, sizeof(request));

			// The MySQL connection
			auto connection = Genesis::Database::DatabaseServer::get_instance()->get_connector()->get_connection();

			// The statement and result instances
			auto statement = connection->createStatement();
			
			// The prepared statement
			std::auto_ptr<sql::PreparedStatement> prepared;

			// The result set
			std::auto_ptr<sql::ResultSet> result;

			// Reset the prepared statement
			prepared.reset(connection->prepareStatement("CALL genesis_gamedata.create_character(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, @result)"));

			// The character name
			std::string character_name((char*) request.name);

			// Define the procedure details
			prepared->setInt(1, server_id);
			prepared->setInt(2, player_id);
			prepared->setString(3, sql::SQLString(character_name));
			prepared->setInt(4, request.race);
			prepared->setInt(5, request.mode);
			prepared->setInt(6, request.profession);
			prepared->setInt(7, request.hair);
			prepared->setInt(8, request.face);
			prepared->setInt(9, request.height);
			prepared->setInt(10, request.gender);

			// Execute the prepared statement
			prepared->execute();

			// Retrieve the results
			result.reset(statement->executeQuery("SELECT @result as $result"));

			// Loop through the results
			if (result->next()) {
				
				// The auth response stucture
				Genesis::Common::Database::Structs::Auth::AuthResponse auth_response;

				// The packet builder instance
				auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

				// Write the request id
				bldr->write_int(request_id);

				// Write the result
				bldr->write_byte((unsigned char) result->getInt("$result"));

				// Write the packet
				session->write(bldr->to_packet());

				// Delete the packet builder
				delete bldr;
			}

			// Close the statement
			statement->close();

			// Delete the statement
			delete statement;

			// Delete the connection
			delete connection;

			// Return true
			return true;
		}
	};
}
#endif