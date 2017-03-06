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
#ifndef GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_GAME_GAMECHARACTER_H
#define GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_GAME_GAMECHARACTER_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::Structs::Game {

	// Represents a character
	struct GameCharacter {

		// The character id
		unsigned int character_id;

		// Not sure
		unsigned int unknown;

		// THe level of the character
		unsigned short level;

		// The race of the character
		unsigned char race;

		// The mode of the character
		unsigned char game_mode;

		// The face of the character
		unsigned char face;

		// The height of the character
		unsigned char height;

		// The class of the character
		unsigned char profession;

		// The gender of the character
		unsigned char gender;

		// The map id
		unsigned short map;

		// The stats
		unsigned short strength;
		unsigned short dexterity;
		unsigned short resistance;
		unsigned short intelligence;
		unsigned short wisdom;
		unsigned short luck;

		// Unknown array
		unsigned char unknown_array[12];
		
		// The item types
		unsigned char item_types[18];

		// The item type ids
		unsigned char item_type_ids[18];

		// A series of null bytes
		unsigned char null_bytes[535];

		// The name of the character
		unsigned char name[32];
	};

}
#endif