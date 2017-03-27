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
#include <genesis/game/world/GameWorld.h>
#include <genesis/game/world/pulse/task/Task.h>
#include <genesis/game/world/pulse/task/impl/LoadPlayerTask.h>
#include <genesis/game/scripting/LuaScriptingEnvironment.h>

#include <genesis/common/logging/Logger.h>
#include <genesis/common/configuration/ConfigManager.h>
#include <genesis/common/database/Opcodes.h>

#include <thread>
#include <chrono>
#include <iostream>

// Use the world namespace
using namespace Genesis::Game::World;

/**
 * Initialise the game world
 */
void GameWorld::init(unsigned char server_id) {

	// Inform the user that the scripting environment is loading
	genesis_logger->info("Initialising Lua scripting environment...");

	// Initialise the scripting environment
	scripting_env->init();

	// Inform the user that the game server is being initialised
	genesis_logger->info("Initialising game world...");

	// Set the server id
	this->server_id = server_id;

	// The address and port of the database server
	auto dbserver_address = config_manager->get_value_or_default<std::string>("DbServerAddress", "127.0.0.1");
	auto dbserver_port = config_manager->get_value_or_default<unsigned short>("DbServerPort", 30820);

	// The io service to operate on
	boost::asio::io_service io_service;

	// The client instance
	this->db_client = new Genesis::Common::Networking::Client::GenesisClient(io_service);

	// The game pulse handler instance
	this->pulse_handler = new Genesis::Game::World::Pulse::GamePulseHandler();

	// The database server connection thread
	std::thread dbserver_thread(std::bind(&Genesis::Common::Networking::Client::GenesisClient::connect, this->db_client, dbserver_address, dbserver_port));

	// Inform the user that we connected to the database server
	genesis_logger->info("Successfully connected to the database server!");

	// Start the game pulse handler
	pulse_handler->start();

	// The port for the io server to bind to
	auto server_port = config_manager->get_value_or_default<unsigned short>("GameServerPort", 30810);

	// The io_server thread
	std::thread thread(std::bind(&Genesis::Game::Io::IoServer::initialise, this->io_server, server_port));
	
	// Wait for the database connection to finish
	dbserver_thread.join();

	// Wait for the thread to finish, and join back to the main program thread
	thread.join();
}

/**
 * Attempts to load the player into the game world.
 *
 * @param player
 *		The player instance
 */
void GameWorld::load_player(Genesis::Game::Model::Entity::Player::Player* player) {

	// Add the player instance
	this->players[player->get_index()] = player;
	
	// Push the task to the pulse handler
	pulse_handler->offer(new Genesis::Game::World::Pulse::Task::Impl::LoadPlayerTask(player));
}

/**
 * Gets the player instance for an index
 *
 * @param index
 *		The index
 */
Genesis::Game::Model::Entity::Player::Player* GameWorld::get_player_for_index(unsigned int index) {
	return this->players[index];
}

/**
 * Gets the player instance for an index
 *
 * @param index
 *		The index
 */
void GameWorld::delete_player_for_index(unsigned int index) {
	
	// The player instance
	auto player = players[index];

	// Erase the player
	players.erase(index);

	// Delete the player
	delete player;
}