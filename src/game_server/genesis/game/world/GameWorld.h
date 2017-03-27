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
#ifndef GENESIS_GAME_WORLD_GAMEWORLD_H
#define GENESIS_GAME_WORLD_GAMEWORLD_H

#include <genesis/game/model/entity/player/Player.h>
#include <genesis/game/io/IoServer.h>
#include <genesis/game/world/pulse/GamePulseHandler.h>
#include <genesis/game/command/CommandDispatcher.h>

#include <genesis/common/networking/client/GenesisClient.h>

#include <mutex>
#include <functional>

/**
 * The game world singleton, which is used to handle to game world, networking, and
 * scripting environment.
 */
namespace Genesis::Game::World {
	class GameWorld {

		public:

			// Gets the singleton instance for this game world
			static GameWorld* get_instance() {
				static GameWorld instance;
				return &instance;
			}

			// Initialise the game server
			void init(unsigned char server_id);

			// Load the player into the game world
			void load_player(Genesis::Game::Model::Entity::Player::Player* player);

			// Gets the server id
			unsigned char get_server_id() {
				return server_id;
			}
		
			// Gets the pulse handler for this game	
			void push_task(Genesis::Game::World::Pulse::Task::Task* task) {
				this->pulse_handler->offer(task);
			}

			// Gets the database client instance
			Genesis::Common::Networking::Client::GenesisClient* get_db_client() {
				return this->db_client;
			}
			
			// Gets the player index of an index
			Genesis::Game::Model::Entity::Player::Player* get_player_for_index(unsigned int index);
			
			// Delete the player instance
			void delete_player_for_index(unsigned int index);
			
			// Gets the command dispatcher instance
			Genesis::Game::Command::CommandDispatcher* get_command_dispatcher() {
				return this->command_dispatcher;
			}
			
		private:
			
			// The server id
			unsigned char server_id;
			
			// The map of indexes to player instance
			std::map<unsigned int, Genesis::Game::Model::Entity::Player::Player*> players;
			
			// The vector of loaded character instance
			std::vector<Genesis::Game::Model::Entity::Player::Character*> characters;

			// The GenesisClient instance
			Genesis::Common::Networking::Client::GenesisClient* db_client;

			// The IoServer instance
			Genesis::Game::Io::IoServer* io_server = new Genesis::Game::Io::IoServer();

			// The GamePulseHandler
			Genesis::Game::World::Pulse::GamePulseHandler* pulse_handler;

			// The command dispatcher instance
			Genesis::Game::Command::CommandDispatcher* command_dispatcher = new Genesis::Game::Command::CommandDispatcher();
	};
}
#endif