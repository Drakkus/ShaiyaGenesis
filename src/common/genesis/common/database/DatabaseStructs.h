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
#ifndef GENESIS_COMMON_DATABASE_DATABASESTRUCTS_H
#define GENESIS_COMMON_DATABASE_DATABASESTRUCTS_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::DatabaseStructs {
	
	// Represents an authentication request to a game server
	struct Game_AuthRequest {

		// The user id
		unsigned int user_id;

		// The identity keys of the user
		unsigned char identity_keys[16];

		// The ip address of the user requesting authentication (IPV4)
		unsigned char ip_address[15];
	};

	// Represents the loaded details of a GameCharacter
	struct Game_GameCharacter {

		// The id of the character
		unsigned int char_id;

		// The name of the character
		unsigned char character[32];

		// The race of the character
		unsigned char char_race;

		// The class of the character
		unsigned char char_class;

		// The sex of the character
		unsigned char char_sex;
	};

	// Represents the response to an {@code Game_AuthRequest}
	struct Game_AuthResponse {

		// The name of the user
		unsigned char username[19];

		// The privilege level of the user
		unsigned char privilege_level;

		// The characters of this account
		Game_GameCharacter game_chars[5];
	};
}
#endif