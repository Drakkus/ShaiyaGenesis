#ifndef GENESIS_GAME_MODEL_ENTITY_PLAYER_PLAYER_H
#define GENESIS_GAME_MODEL_ENTITY_PLAYER_PLAYER_H

#include <genesis/common/networking/server/session/ServerSession.h>
#include <genesis/common/networking/packets/Packet.h>

#include <genesis/game/model/entity/Entity.h>

namespace Genesis::Game::Model::Entity::Player {
	class Player : public Entity {

		public:

			// The constructor for the player
			Player(unsigned int index, Genesis::Common::Networking::Server::Session::ServerSession* session) : session(session), Entity(index) {}
	
			// Forward the write packet function to the session
			void write(Genesis::Common::Networking::Packets::Packet* packet) {
				this->session->write(packet);
			}

		private:

			// The session instance for this player
			Genesis::Common::Networking::Server::Session::ServerSession* session;
	};
}
#endif