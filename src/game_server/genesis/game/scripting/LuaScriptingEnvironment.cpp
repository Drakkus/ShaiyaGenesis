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
#include "LuaScriptingEnvironment.h"

#include <genesis/common/configuration/ConfigManager.h>
#include <genesis/common/logging/Logger.h>

#include <genesis/game/world/GameWorld.h>
#include <genesis/game/command/CommandListener.h>
#include <genesis/game/io/packets/outgoing/PacketRepository.h>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <iostream>

using namespace Genesis::Game::Scripting;

/**
 * Initialise the Lua scripting environment
 */
void LuaScriptingEnvironment::init() {

	// The script directory
	std::string script_dir = config_manager->get_value_or_default<std::string>("ScriptsDirectory", "./scripts/");

	// The string stream instance
	std::stringstream stream;

	// Construct the stream
	stream << script_dir << "parser.lua";

	// Open the libraries
	state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::string, sol::lib::os, sol::lib::math, sol::lib::table, sol::lib::debug, sol::lib::bit32, sol::lib::io, sol::lib::ffi);

	// The parser table, which requires the MoonScript library for parsing MoonScript
	sol::table parser = state.require_file("moonscript", stream.str().c_str());

	state.new_usertype<Genesis::Game::Model::Entity::Player::Character>("character",
		"get_name", &Genesis::Game::Model::Entity::Player::Character::get_name,
		sol::base_classes, sol::bases<Genesis::Game::Model::Entity::Entity>()
	);

	state.new_usertype<Genesis::Game::Command::Command>("command",
		"get_name", &Genesis::Game::Command::Command::get_name,
		"get_args", &Genesis::Game::Command::Command::get_arguments
	);

	state.new_usertype<Genesis::Game::Io::Packets::Outgoing::PacketRepository>("packet_repository",
		"send_notice", &Genesis::Game::Io::Packets::Outgoing::PacketRepository::send_notice_noargs
	);
	state["packet_repository"] = packet_repository;

	state.set_function("_GENESIS_LOGGER_INFO", [](const char* message) {
		genesis_logger->info(message);
	});

	state.set_function("_GENESIS_LOGGER_ERROR", [](const char* message) {
		genesis_logger->error(message);
	});

	state.set_function("add_event_listener", [](const char* event_type, sol::function func) {
		std::cout << "type: " << event_type << std::endl;
		func(123456);
	});

	state.set_function("add_command_listener", [](std::string command_name, int privilege, sol::function block) {

		// The command dispatcher instance
		auto dispatcher = Genesis::Game::World::GameWorld::get_instance()->get_command_dispatcher();

		// Register the listener
		dispatcher->register_listener(command_name, new Genesis::Game::Command::CommandListener(privilege, block));
	});

	// Clear the string stream instance
	stream.str(std::string());
	stream.clear();

	// Construct the stream
	stream << script_dir << "bootstrap.moon";

	// Load the bootstrap script
	load_script(parser, stream.str());

	// Load all the other scripts
	this->load_all_scripts(script_dir, parser);
}

/**
 * Loads all of the scripts in the script directory
 *
 * @param base_path
 *		The base path directory
 *
 * @param parser
 *		The MoonScript to Lua parser
 */
void LuaScriptingEnvironment::load_all_scripts(std::string base_path, sol::table parser) {

	// The recursive directory iterator
	boost::filesystem::recursive_directory_iterator begin(base_path), end;

	// The directory entires
	std::vector<boost::filesystem::directory_entry> v(begin, end);

	// Loop through the entries
	for (auto &f: v) {

		// The file path
		std::string path = f.path().string();

		// If the entry is not the parser or bootstrap script
		if (!boost::ends_with(path, "bootstrap.moon") && !boost::ends_with(path, "parser.lua")) {

			// If the script is a MoonScript
			if (boost::ends_with(path, ".moon"))

				// Load the script
				load_script(parser, path);
		}
	}
}

/**
 * Loads a script instance
 *
 * @param parser
 *		The MoonScript to Lua parser
 *
 * @param path
 *		The path to the script
 */
void LuaScriptingEnvironment::load_script(sol::table parser, std::string path) {

	// The stream instance, for reading the file
	std::stringstream stream;

	// The file instance
	std::ifstream script(path);

	// Read into the stream
	stream << script.rdbuf();

	// The parsed Lua code
	std::string parsed = parser["parse"](stream.str());

	// Execute the code
	state.do_string(parsed);
}