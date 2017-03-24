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
#include "CheckAvailableNameTask.h"

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/Opcodes.h>
#include <genesis/common/packets/Opcodes.h>

#include <genesis/game/world/GameWorld.h>

#include <iostream>

/**
 * Begin processing the checking of an available character name
 */
void Genesis::Game::World::Pulse::Task::Impl::CheckAvailableNameTask::execute() {
	
	// The local player
	auto &local_player = this->player;

	// The client instance
	auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::CHECK_AVAILABLE_NAME);

	// Write the name
	bldr->write_bytes((unsigned char*) name.c_str(), name.length());

	// Write the packet to the database server
	db_client->write(bldr->to_packet(), [local_player](unsigned char* data, unsigned int length) {

		// The packet builder instance to write to the player
		auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::AVAILABLE_CHARACTER_NAME);

		// Write the result to the player
		bldr->write_byte(data[0]);

		// Write the packet to the player
		local_player->write(bldr->to_packet());

		// Delete the packet builder
		delete bldr;
		
	});

	// Delete the packet builder instance
	delete bldr;
}