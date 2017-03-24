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
#ifndef GENESIS_GAME_MODEL_ENTITY_PLAYER_CHARACTER_H
#define GENESIS_GAME_MODEL_ENTITY_PLAYER_CHARACTER_H

#include <genesis/game/model/entity/Entity.h>

#include <genesis/common/networking/packets/Packet.h>

// Forward declaration of the player class
namespace Genesis::Game::Model::Entity::Player { class Player; }

/**
 * Represents a character instance than can interact with the game world
 */
namespace Genesis::Game::Model::Entity::Player {
	class Character : public Entity {

		public:

			/**
			 * The constructor for this {@code Character} instance.
			 *
			 * @param player
			 *		The player instance
			 */
			Character(Genesis::Game::Model::Entity::Player::Player* player, int character_id) : player(player), Entity(character_id) {}

			/**
			 * Writes a player to the player's session
			 *
			 * @param packet
			 * 		The packet instance
			 */
			void write(Genesis::Common::Networking::Packets::Packet* packet);

			// Checks if this character instance is initialised and ready
			bool is_initialised() const;

			// Setters and getters for the character's profession
			void set_profession(unsigned char profession);
			unsigned char get_profession() const;

			// Setters and getters for the character's race
			void set_race(unsigned char race);
			unsigned char get_race() const;

			// Setters and getters for the character's game mode
			void set_mode(unsigned char mode);
			unsigned char get_mode() const;

			// Setters and getters for the character's hair
			void set_hair(unsigned char hair);
			unsigned char get_hair() const;

			// Setters and getters for the character's face
			void set_face(unsigned char face);
			unsigned char get_face() const;

			// Setters and getters for the character's height
			void set_height(unsigned char height);
			unsigned char get_height() const;

			// Setters and getters for the character's gender
			void set_gender(unsigned char gender);
			unsigned char get_gender() const;

			// Setters and getters for the character's stat points
			void set_stat_points(unsigned short stat_points);
			unsigned short get_stat_points() const;

			// Setters and getters for the character's skill points
			void set_skill_points(unsigned short skill_points);
			unsigned short get_skill_points() const;

			// Setters and getters for the character's gold
			void set_gold(unsigned int gold);
			unsigned int get_gold() const;

			// Setters and getters for the character's kill count
			void set_kills(unsigned int kills);
			unsigned int get_kills() const;

			// Setters and getters for the character's death count
			void set_deaths(unsigned int deaths);
			unsigned int get_deaths() const;

			// Setters and getters for the character's victories
			void set_victories(unsigned int victories);
			unsigned int get_victories() const;

			// Setters and getters for the character's defeats
			void set_defeats(unsigned int defeats);
			unsigned int get_defeats() const;

			// Setters and getters for the character's guild id
			void set_guild_id(unsigned int guild_id);
			unsigned int get_guild_id() const;

			Genesis::Game::Model::Entity::Player::Player* get_player() const {
				return this->player;
			}
		private:

			// The player instance that this character is associated with
			Genesis::Game::Model::Entity::Player::Player* player;

			// If the character instance is ready to enter the game world
			bool initialised = false;

			// The class, race and mode
			unsigned char profession;
			unsigned char race;
			unsigned char mode;

			// The appearance info of the character
			unsigned char hair;
			unsigned char face;
			unsigned char height;
			unsigned char gender;

			// The stat and skill points of the character
			unsigned short stat_points;
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
	};
}
#endif