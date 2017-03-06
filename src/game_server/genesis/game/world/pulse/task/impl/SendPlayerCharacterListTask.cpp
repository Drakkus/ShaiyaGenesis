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

// Use the task implementation namespace
using namespace Genesis::Game::World::Pulse::Task::Impl;

/**
 * Handle the sending of a player's character list
 */
void SendPlayerCharacterListTask::execute() {

	for (int i = 1; i < 5; i++) {

		// The packet builder instance
		auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::CHARACTER_LIST);

		// Write the character slot
		bldr->write_byte(i);

		// Write the character id
		bldr->write_int(0);

		// Write the packet
		player->write(bldr->to_packet());

		// Delete the packet builder
		delete bldr;
	}
	
	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::CHARACTER_LIST);

	// Write the character slot
	bldr->write_byte(0);

	// Write the character id
	bldr->write_int(1);

	// Don't know
	bldr->write_int(0);

	// The level
	bldr->write_short(80);

	// The race
	bldr->write_byte(0);

	// The mode
	bldr->write_byte(3);

	// The hair of the character
	bldr->write_byte(2);

	// The face
	bldr->write_byte(1);

	// The height
	bldr->write_byte(2);

	// The class
	bldr->write_byte(0);

	// The gender
	bldr->write_byte(1);

	// The map id
	bldr->write_short(42);

	// Write the stats
	bldr->write_short(111); // STR
	bldr->write_short(222); // DEX
	bldr->write_short(333); // REC
	bldr->write_short(444); // INT
	bldr->write_short(555); // WIS
	bldr->write_short(666); // LUC

	// Not sure
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(255);
	bldr->write_byte(255);
	bldr->write_byte(0);
	bldr->write_byte(0x11);
	bldr->write_byte(0x12);
	bldr->write_byte(0x14);
	bldr->write_byte(0x15);

	// Item types
	bldr->write_byte(6); // Weapon
	bldr->write_byte(19); // Shield
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(120); // Pet
	bldr->write_byte(0); // Costume
	bldr->write_byte(121); // Wings
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);

	bldr->write_byte(215); // Weapon
	bldr->write_byte(138); // Shield
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(1);
	bldr->write_byte(43); // Pet
	bldr->write_byte(0); // Costume
	bldr->write_byte(3); // Wings
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);
	bldr->write_byte(0);

	// Write 535 null bytes
	for (int i = 0; i < 535; i++) {
		bldr->write_byte(0);
	}

	// Write the character name
	bldr->write_bytes((unsigned char*) "Cups", 4);

	// Write the packet
	player->write(bldr->to_packet());

	// Delete the packet builder
	delete bldr;
}