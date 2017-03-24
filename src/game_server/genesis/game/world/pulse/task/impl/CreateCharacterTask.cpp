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
#include "CreateCharacterTask.h"
#include "SendPlayerCharacterListTask.h"

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/Opcodes.h>
#include <genesis/common/packets/Opcodes.h>

#include <genesis/game/world/GameWorld.h>

#include <iostream>

/**
 * Begin processing the checking of a character creation request
 */
void Genesis::Game::World::Pulse::Task::Impl::CreateCharacterTask::execute() {

	// The local player
	auto &local_player = this->player;
	auto local_request = *request;
	
	// The client instance
	auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::CREATE_CHARACTER);

	// The request byte array
	unsigned char request_array[sizeof(local_request)];

	// Populate the byte array
	std::memcpy(request_array, &local_request, sizeof(local_request));

	// Write the server id
	bldr->write_byte(Genesis::Game::World::GameWorld::get_instance()->get_server_id());

	// Write the player id
	bldr->write_int(player->get_index());
	
	// Write the data to the database server
	bldr->write_bytes(request_array, sizeof(local_request));

	// Write the request to the database server
	db_client->write(bldr->to_packet(), [local_player, local_request](unsigned char* data, unsigned int length) {

		// Write the player's character list
		Genesis::Game::World::GameWorld::get_instance()->push_task(new Genesis::Game::World::Pulse::Task::Impl::SendPlayerCharacterListTask(local_player));

		// The packet builder instance
		auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::CREATE_CHARACTER);

		// Write the response (if the response from the database server is -1, then character creation failed)
		// So we send the value 2 to show an error
		bldr->write_byte((data[0] & 0xFF) == -1 ? 2 : 0);

		// Write the packet to the client
		local_player->write(bldr->to_packet());

		// Delete the packet builder
		delete bldr;
	});

	// Delete the packet builder instance
	delete bldr;

	// Delete the creation request
	delete this->request;
}