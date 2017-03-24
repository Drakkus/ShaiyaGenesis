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
#include "SendPlayerCharacterListTask.h"

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/packets/Opcodes.h>
#include <genesis/common/database/Opcodes.h>

#include <genesis/game/world/GameWorld.h>

#include <iostream>
#include <vector>
#include <algorithm>

// Use the task implementation namespace
using namespace Genesis::Game::World::Pulse::Task::Impl;

/**
 * Handle the sending of a player's character list
 */
void SendPlayerCharacterListTask::execute() {

	// The player instance
	auto &local_player = this->player;

	// The client instance
	auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::GET_CHARACTER_LIST_DATA);

	// Write the player id
	bldr->write_int(player->get_index());

	// Write the server id
	bldr->write_byte(Genesis::Game::World::GameWorld::get_instance()->get_server_id());

	// Write the packet to the database server
	db_client->write(bldr->to_packet(), [local_player](unsigned char* data, unsigned int length) {


		// The number of characters to read for this player
		unsigned char character_count = (data[0] & 0xFF);

		// The vector of slots
		std::vector<int> slots {0, 1, 2, 3, 4};

		// Loop through the characters
		for (int i = 0; i < character_count; i++) {

			// The character instance
			Genesis::Common::Database::Structs::Game::GameCharacter character;

			// Populate the character instance
			std::memcpy(&character, (data + 1 + (i * sizeof(character))), sizeof(character));

			// Remove the slot from the vector
			slots.erase(std::remove(slots.begin(), slots.end(), character.slot), slots.end());

			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::CHARACTER_LIST);

			// Write the slot
			bldr->write_byte(character.slot);

			// Write the character id
			bldr->write_int(character.character_id);

			// Unknown (Character creation time?)
			bldr->write_int(0);

			// Write the character's level
			bldr->write_short(character.level);

			// The race of the character
			bldr->write_byte(character.race);

			// The mode of the character
			bldr->write_byte(character.game_mode);

			// The hair of the character
			bldr->write_byte(character.hair);

			// The face of the character
			bldr->write_byte(character.face);

			// The height of the character
			bldr->write_byte(character.height);

			// The class of the character
			bldr->write_byte(character.profession);

			// The gender of the character
			bldr->write_byte(character.gender);

			// The map that the character is in
			bldr->write_short(character.map);

			// The stats of the character
			bldr->write_short(character.strength);
			bldr->write_short(character.dexterity);
			bldr->write_short(character.resistance);
			bldr->write_short(character.intelligence);
			bldr->write_short(character.wisdom);
			bldr->write_short(character.luck);

			// Unknown array
			for (int j = 0; j < 11; j++)
				bldr->write_byte(0);

			// The item types
			bldr->write_bytes((unsigned char*) character.item_types, sizeof(character.item_types));

			// The item type ids
			bldr->write_bytes((unsigned char*) character.item_type_ids, sizeof(character.item_type_ids));

			// Write 535 null bytes
			for (int j = 0; j < 535; j++)
				bldr->write_byte(0);

			// Write the character name
			bldr->write_bytes((unsigned char*) character.name, sizeof(character.name));

			// Write the character deletion flag
			bldr->write_byte(character.is_pending_deletion);

			// Write the character data
			local_player->write(bldr->to_packet());

			// Delete the packet builder
			delete bldr;

		}

		// Loop through the empty slots
		for (auto slot : slots) {

			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::CHARACTER_LIST);

			// Write the slot
			bldr->write_byte(slot);

			// Write the empty character id
			bldr->write_int(0);

			// Write the character data
			local_player->write(bldr->to_packet());

			// Delete the packet builder
			delete bldr;
		}
	});

	// Delete the packet builder
	delete bldr;
}