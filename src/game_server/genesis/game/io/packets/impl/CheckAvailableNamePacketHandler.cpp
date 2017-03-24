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
#include "CheckAvailableNamePacketHandler.h"

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/Opcodes.h>

#include <genesis/game/world/GameWorld.h>
#include <genesis/game/world/pulse/task/impl/CheckAvailableNameTask.h>

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
bool CheckAvailableNamePacketHandler::handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned char* data) {

	// The name array
	char character_name[15];

	// Copy the data
	std::memcpy(&character_name, data, sizeof(character_name));

	// Add a null terminator
	character_name[sizeof(character_name) - 1] = '\0';

	// The name
	std::string name(character_name);

	// The player instance
	auto player = Genesis::Game::World::GameWorld::get_instance()->get_player_for_index(session->get_game_index());

	// Push the task
	Genesis::Game::World::GameWorld::get_instance()->push_task(new Genesis::Game::World::Pulse::Task::Impl::CheckAvailableNameTask(player, name));

	// Return true
	return true;
}