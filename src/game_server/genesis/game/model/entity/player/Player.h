#ifndef GENESIS_GAME_MODEL_ENTITY_PLAYER_PLAYER_H
#define GENESIS_GAME_MODEL_ENTITY_PLAYER_PLAYER_H

#include <genesis/common/networking/server/session/ServerSession.h>
#include <genesis/common/networking/packets/Packet.h>

#include <genesis/game/model/entity/Entity.h>

#include <iostream>

namespace Genesis::Game::Model::Entity::Player {
	class Player : public Entity {

		public:

			// The constructor for the player
			Player(unsigned int index, Genesis::Common::Networking::Server::Session::ServerSession* session) : session(session), Entity(index) {

				// Set the session index
				this->session->set_game_index(index);
			}

			// Forward the write packet function to the session
			void write(Genesis::Common::Networking::Packets::Packet* packet) {
				this->session->write(packet);
			}

			// Get the faction for this player
			unsigned char get_faction() {
				return this->faction;
			}

			// Get the privilege level
			unsigned char get_privilege_level() {
				return this->privilege_level;
			}

			// Get the max game mode
			unsigned char get_max_game_mode() {
				return this->max_game_mode;
			}
			
			// Set the faction for this player
			void set_faction(unsigned char faction) {
				this->faction = faction;
			}

			// Set the privilege level for this player
			void set_privilege_level(unsigned char privilege_level) {
				this->privilege_level = privilege_level;
			}

			// Set the max game mode for this player
			void set_max_game_mode(unsigned char max_game_mode) {
				this->max_game_mode = max_game_mode;
			}

		private:

			// The session instance for this player
			Genesis::Common::Networking::Server::Session::ServerSession* session;

			// The faction of this player
			unsigned char faction;

			// The privilege level of this player
			unsigned char privilege_level;

			// The maximum selectable game mode
			unsigned char max_game_mode;

	};
}
#endif