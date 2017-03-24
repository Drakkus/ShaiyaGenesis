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
#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_LOADGAMECHARACTERDATAREQUESTHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_LOADGAMECHARACTERDATAREQUESTHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
#include <genesis/database/DatabaseServer.h>

#include <genesis/common/database/structs/game/GameHandshakeRequest.h>
#include <genesis/common/database/structs/game/CharacterLoadInfo.h>

#include <genesis/common/networking/packets/PacketBuilder.h>

#include <iostream>

namespace Genesis::Database::Io::Packets::Impl {
	class LoadGameCharacterDataRequestHandler : public PacketHandler {

		/**
		 * Handles the loading of character data
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
			std::auto_ptr<sql::Connection> connection(Genesis::Database::DatabaseServer::get_instance()->get_connector()->get_connection());
			
			// The prepared statement
			std::auto_ptr<sql::PreparedStatement> prepared(connection->prepareStatement("CALL genesis_gamedata.load_game_character(?, ?, ?)"));

			// The result set
			std::auto_ptr<sql::ResultSet> result;
			
			// Attempt to catch any errors
			try {

				// The user id and server id
				unsigned int user_id;
				unsigned int character_id;
				unsigned char server_id;

				// Populate the values
				std::memcpy(&user_id, data, sizeof(user_id));
				std::memcpy(&character_id, data + sizeof(user_id), sizeof(character_id));
				std::memcpy(&server_id, data + sizeof(user_id) + sizeof(character_id), sizeof(server_id));
				
				// Define the user id and server id
				prepared->setInt(1, user_id);
				prepared->setInt(2, character_id);
				prepared->setInt(3, server_id);

				// Execute the query
				result.reset(prepared->executeQuery());

				// While there is a result to be read
				if (result->next()) {
						
					// The character instance
					Genesis::Common::Database::Structs::Game::CharacterLoadInfo character;

					// Define the character details
					character.character_id = result->getInt("char_id");
					character.profession = result->getInt("class");
					character.race = result->getInt("race");
					character.mode = result->getInt("mode");
					character.level = result->getInt("level");
					character.hair = result->getInt("hair");
					character.face = result->getInt("face");
					character.height = result->getInt("height");
					character.gender = result->getInt("sex");
					character.strength = result->getInt("strength");
					character.dexterity = result->getInt("dexterity");
					character.resistance = result->getInt("resistance");
					character.intelligence = result->getInt("intelligence");
					character.wisdom = result->getInt("wisdom");
					character.luck = result->getInt("luck");
					character.current_hp = result->getInt("current_hp");
					character.current_mp = result->getInt("current_mp");
					character.current_sp = result->getInt("current_sp");
					character.stat_points = result->getInt("stat_points");
					character.skill_points = result->getInt("skill_points");
					character.gold = result->getInt("gold");
					character.kills = result->getInt("kill_count");
					character.deaths = result->getInt("death_count");
					character.victories = result->getInt("victory_count");
					character.defeats = result->getInt("defeat_count");

					// TODO: Guild ID
					character.guild_id = 0;

					// The position details
					character.map_id = result->getInt("map");
					character.direction = result->getInt("direction");
					character.position_x = (float) result->getDouble("position_x");
					character.position_y = (float) result->getDouble("position_y");
					character.position_height = result->getDouble("position_height");
					
					// The name of the character
					std::string character_name = result->getString("char_name");

					// Copy the name
					std::copy(character_name.begin(), character_name.begin() + (character_name.length() + 1), character.name);

					// The request byte array
					unsigned char char_array[sizeof(character)];

					// Populate the byte array
					std::memcpy(char_array, &character, sizeof(character));

					// Write a successful load response
					bldr->write_byte(0);

					// Write the character data
					bldr->write_bytes(char_array, sizeof(character));
				}

			} catch (sql::SQLException &e) {

				// Write a failed load response
				bldr->write_byte(1);

				// Log the error
				genesis_logger->error(e.what());
			}

			// Close the prepared statement
			prepared->close();

			// Write the packet
			session->write(bldr->to_packet());

			// Delete the packet builder instance
			delete bldr;
			
			// Return true
			return true;
		}
	};
}
#endif