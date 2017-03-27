#ifndef GENESIS_GAME_COMMAND_COMMANDLISTENER_H
#define GENESIS_GAME_COMMAND_COMMANDLISTENER_H

#include <genesis/game/command/Command.h>
#include <genesis/game/model/entity/player/Player.h>
#include <genesis/game/model/entity/player/Character.h>

#include <genesis/common/scripting/sol.hpp>

namespace Genesis::Game::Command {
	class CommandListener {

		public:

			CommandListener(sol::function block) : privilege_level(0), block(block) {}

			CommandListener(unsigned char privilege_level, sol::function block) : privilege_level(privilege_level), block(block) {}

			void execute(Genesis::Game::Model::Entity::Player::Character* character, Genesis::Game::Command::Command* command) {
				this->block(character, command);
			}

			void execute_privileged(Genesis::Game::Model::Entity::Player::Character* character, Genesis::Game::Command::Command* command) {
				if (character->get_player()->get_privilege_level() >= this->privilege_level)
					this->execute(character, command);
			}

		private:

			unsigned char privilege_level;

			sol::function block;
	};

}
#endif