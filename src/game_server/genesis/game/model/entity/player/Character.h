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
			bool is_initialised();

		private:

			// The player instance that this character is associated with
			Genesis::Game::Model::Entity::Player::Player* player;

			// If the character instance is ready to enter the game world
			bool initialised = false;
	};
}
#endif