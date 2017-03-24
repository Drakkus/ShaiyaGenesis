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
#ifndef GENESIS_GAME_MODEL_ENTITY_PLAYER_PLAYER_H
#define GENESIS_GAME_MODEL_ENTITY_PLAYER_PLAYER_H

#include <genesis/common/networking/server/session/ServerSession.h>
#include <genesis/common/networking/packets/Packet.h>
#include <genesis/common/database/structs/game/GameCharacter.h>

#include <genesis/game/model/entity/player/Character.h>

/**
 * Represents a player's game account instance, which holds reference to the connection session,
 * and keeps track of the character that is currently in use
 */
namespace Genesis::Game::Model::Entity::Player {
	class Player {

		public:

			// The constructor for the player
			Player(unsigned int index, Genesis::Common::Networking::Server::Session::ServerSession* session) : session(session) {

				// Set the player id
				this->player_id = index;

				// Set the session index
				this->session->set_game_index(index);
			}

			// Forward the write packet function to the session
			void write(Genesis::Common::Networking::Packets::Packet* packet);

			// Get the faction for this player
			unsigned char get_faction();

			// Get the privilege level
			unsigned char get_privilege_level();

			// Get the max game mode
			unsigned char get_max_game_mode();
			
			unsigned int get_points();
			
			// Set the faction for this player
			void set_faction(unsigned char faction);

			// Set the privilege level for this player
			void set_privilege_level(unsigned char privilege_level);

			// Set the max game mode for this player
			void set_max_game_mode(unsigned char max_game_mode);

			// Gets the character instance for this player
			Genesis::Game::Model::Entity::Player::Character* get_character();
			
			// Set the player's character instance
			void set_character(Genesis::Game::Model::Entity::Player::Character* character);

			// Set the player's points
			void set_points(unsigned int points);
			
			// Gets the player index
			unsigned int get_index();
			
		private:

			// The session instance for this player
			Genesis::Common::Networking::Server::Session::ServerSession* session;

			// The character instance currently in use by this player
			Genesis::Game::Model::Entity::Player::Character* character;

			// The player id
			unsigned int player_id;

			// The faction of this player
			unsigned char faction;

			// The privilege level of this player
			unsigned char privilege_level;

			// The AP that the player has
			unsigned int points;

			// The maximum selectable game mode
			unsigned char max_game_mode;

			// Has the player selected a character
			bool selected_character = false;
	};
}
#endif