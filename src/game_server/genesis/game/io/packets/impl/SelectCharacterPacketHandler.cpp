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
#include "SelectCharacterPacketHandler.h"

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/packets/Opcodes.h>
#include <genesis/common/database/Opcodes.h>

#include <genesis/game/world/GameWorld.h>
#include <genesis/game/world/pulse/task/impl/LoadCharacterGameWorldTask.h>

#include <string>

// The packet handler implementation namespace
using namespace Genesis::Game::Io::Packets::Impl;

/**
 * Handles an incoming request to enter the game world with a character
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
bool SelectCharacterPacketHandler::handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned char* data) {

	// If the length is not valid
	if (length != 4)
		return true;

	// The character id
	unsigned int character_id;

	// Copy the character id
	std::memcpy(&character_id, data, sizeof(character_id));

	// The client instance
	auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();

	// The player instance
	auto player = Genesis::Game::World::GameWorld::get_instance()->get_player_for_index(session->get_game_index());

	// Push the task to the worker
	Genesis::Game::World::GameWorld::get_instance()->push_task(new Genesis::Game::World::Pulse::Task::Impl::LoadCharacterGameWorldTask(player, character_id));
	
	// Return true
	return true;
}