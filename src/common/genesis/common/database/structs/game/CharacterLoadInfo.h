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
#ifndef GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_GAME_CHARACTERLOADINFO_H
#define GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_GAME_CHARACTERLOADINFO_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::Structs::Game {

	// The character's info information
	struct CharacterLoadInfo {

		// The character name
		char name[32];

		// The character id
		unsigned int character_id;

		// The class, race and mode
		unsigned char profession;
		unsigned char race;
		unsigned char mode;

		// The level of the character
		unsigned short level;

		// The appearance info of the character
		unsigned char hair;
		unsigned char face;
		unsigned char height;
		unsigned char gender;

		// The base stats
		unsigned int strength;
		unsigned int dexterity;
		unsigned int resistance;
		unsigned int intelligence;
		unsigned int wisdom;
		unsigned int luck;

		// The current HP/MP/SP
		unsigned int current_hp;
		unsigned int current_mp;
		unsigned int current_sp;

		// The stat points
		unsigned short stat_points;

		// The skill points
		unsigned short skill_points;

		// The character's gold
		unsigned int gold;

		// The kills, deaths, victories and defeats
		unsigned int kills;
		unsigned int deaths;
		unsigned int victories;
		unsigned int defeats;

		// The guild id
		unsigned int guild_id;

		// The current map id
		unsigned short map_id;

		// The coordinates
		unsigned char direction;
		float position_x;
		float position_y;
		float position_height;
	};

}
#endif