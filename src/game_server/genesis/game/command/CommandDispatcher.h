#ifndef GENESIS_GAME_COMMAND_COMMANDDISPATCHER_H
#define GENESIS_GAME_COMMAND_COMMANDDISPATCHER_H

#include <genesis/game/command/CommandListener.h>
#include <genesis/game/command/Command.h>
#include <genesis/game/model/entity/player/Character.h>

#include <string>
#include <map>

namespace Genesis::Game::Command {
	class CommandDispatcher {

		public:

			void register_listener(std::string command, Genesis::Game::Command::CommandListener*);
			void dispatch(Genesis::Game::Model::Entity::Player::Character*, Genesis::Game::Command::Command*);

		private:

			// The map of command names, to listener instances
			std::map<std::string, Genesis::Game::Command::CommandListener*> listeners;
	};
}
#endif