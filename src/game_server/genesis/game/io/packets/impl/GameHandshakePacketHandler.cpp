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
#include "GameHandshakePacketHandler.h"

#include <genesis/common/database/structs/game/GameHandshakeRequest.h>
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/Opcodes.h>
#include <genesis/common/logging/Logger.h>

#include <genesis/game/world/pulse/task/impl/LoadPlayerTask.h>
#include <genesis/game/world/GameWorld.h>

#include <string>

// The packet handler implementation namespace
using namespace Genesis::Game::Io::Packets::Impl;

/**
 * Handles an incoming game handshake request
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
bool GameHandshakePacketHandler::handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned char* data) {

	// Verify that the length is correct
	if (length != 20)
		return true;

	// The game handshake request structure
	Genesis::Common::Database::Structs::Game::GameHandshakeRequest handshake;

	// Copy the handshake data
	std::memcpy(&handshake, data, sizeof(handshake));

	// The client instance
	auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::USER_GAME_CONNECT);

	// Write the user id and identity keys
	bldr->write_int(handshake.user_id);
	bldr->write_bytes((unsigned char*) &handshake.identity_keys[0], sizeof(handshake.identity_keys));

	// This instance
	auto current = this;

	// Write the packet to the database server
	db_client->write(bldr->to_packet(), [current, opcode, session, handshake](unsigned char* data, unsigned int length) {

		// If the user id and session key pair is valid
		unsigned char result = (data[0] & 0xFF);

		// The packet builder instance
		auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

		// Write the result
		bldr->write_byte(result);

		// If the result is 0, we should create a player instance, and request to load it's data
		if (result == 0) {
			
			// Inform the user that the player has loaded
			genesis_logger->info("Accepted successful handshake from address: %s, with the user id of %d", {session->get_remote_address().c_str(), std::to_string(handshake.user_id).c_str()});
			
			// The player instance
			auto player = new Genesis::Game::Model::Entity::Player::Player(handshake.user_id, session);

			// Load the player
			Genesis::Game::World::GameWorld::get_instance()->load_player(player);
		}

		// Write the packet
		session->write(bldr->to_packet());

		// Delete the packet builder
		delete bldr;
	});

	// Delete the packet builder instance
	delete bldr;

	// Return true
	return true;
}