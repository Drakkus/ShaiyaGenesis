#include <genesis/game/command/CommandDispatcher.h>

#include <algorithm>
#include <iostream>

using namespace Genesis::Game::Command;

void CommandDispatcher::register_listener(std::string command_name, Genesis::Game::Command::CommandListener* listener) {

	std::transform(command_name.begin(), command_name.end(), command_name.begin(), ::tolower);

	this->listeners[command_name] = listener;
}

void CommandDispatcher::dispatch(Genesis::Game::Model::Entity::Player::Character* character, Genesis::Game::Command::Command* command) {
	
	std::string command_name = command->get_name();

	std::transform(command_name.begin(), command_name.end(), command_name.begin(), ::tolower);

	if (this->listeners.count(command_name) != 0) {

		auto listener = this->listeners[command_name];
		listener->execute_privileged(character, command);
	}
}