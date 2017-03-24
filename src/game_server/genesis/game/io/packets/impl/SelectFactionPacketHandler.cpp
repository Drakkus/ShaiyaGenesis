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
#include "SelectFactionPacketHandler.h"

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/Opcodes.h>
#include <genesis/common/game/Constants.h>
#include <genesis/common/logging/Logger.h>

#include <genesis/game/world/GameWorld.h>
#include <genesis/game/world/pulse/task/impl/CheckAvailableNameTask.h>

#include <string>

// The packet handler implementation namespace
using namespace Genesis::Game::Io::Packets::Impl;

/**
 * Handles an incoming faction selection request
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
bool SelectFactionPacketHandler::handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned char* data) {

	// The faction chosen
	unsigned char faction = (data[0] & 0xFF);

	// Verify that the faction is valid
	if (faction != Genesis::Common::Game::Constants::FACTION_AOL && faction != Genesis::Common::Game::Constants::FACTION_UOF) {

		// Delete the session instance
		delete session;

		// Log the error
		genesis_logger->error("Player ID: %s attempts to select an invalid faction with the value of %s", {
			std::to_string(session->get_game_index()).c_str(), std::to_string(faction).c_str()});
		
		// Don't continue processing packets
		return false;
	}

	// The client instance
	auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();

	// The player instance
	auto player = Genesis::Game::World::GameWorld::get_instance()->get_player_for_index(session->get_game_index());

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::SELECT_FACTION);

	// Write the player's id
	bldr->write_int(player->get_index());

	// Write the faction
	bldr->write_byte(faction);

	// Write the server id
	bldr->write_byte(Genesis::Game::World::GameWorld::get_instance()->get_server_id());

	// Write the packet to the database server
	db_client->write(bldr->to_packet());
	
	// Delete the packet builder
	delete bldr;

	// Set the faction
	player->set_faction(faction);

	// Return true
	return true;
}