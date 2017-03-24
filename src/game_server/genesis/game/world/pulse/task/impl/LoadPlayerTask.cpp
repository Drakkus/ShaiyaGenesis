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
#include "LoadPlayerTask.h"
#include "SendPlayerFactionTask.h"
#include "SendPlayerCharacterListTask.h"

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/Opcodes.h>
#include <genesis/common/packets/Opcodes.h>
#include <genesis/common/database/structs/game/GameLoadPlayerResponse.h>

#include <genesis/game/world/GameWorld.h>

#include <iostream>

/**
 * Begin loading the details for a player
 */
void Genesis::Game::World::Pulse::Task::Impl::LoadPlayerTask::execute() {

	// The client instance
	auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::GAME_USER_LOAD);

	// Write the player id
	bldr->write_int(player->get_index());

	// Write the server id
	bldr->write_byte(Genesis::Game::World::GameWorld::get_instance()->get_server_id());

	// The player instance
	auto &local_player = this->player;

	// Write the packet
	db_client->write(bldr->to_packet(), [local_player](unsigned char* data, unsigned int length) {

		// The response
		Genesis::Common::Database::Structs::Game::GameLoadPlayerResponse response;

		// Copy the data
		std::memcpy(&response, data, sizeof(response));

		// Set the player's data
		local_player->set_faction(response.faction);
		local_player->set_max_game_mode(response.max_char_mode);
		local_player->set_privilege_level(response.privilege_level);
		local_player->set_points(response.points);
		
		// Write the player's character list
		Genesis::Game::World::GameWorld::get_instance()->push_task(new Genesis::Game::World::Pulse::Task::Impl::SendPlayerCharacterListTask(local_player));

		// Write the player's faction
		Genesis::Game::World::GameWorld::get_instance()->push_task(new Genesis::Game::World::Pulse::Task::Impl::SendPlayerFactionTask(local_player));

	});

	// Delete the packet builder instance
	delete bldr;
}