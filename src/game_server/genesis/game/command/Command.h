#ifndef GENESIS_GAME_COMMAND_COMMAND_H
#define GENESIS_GAME_COMMAND_COMMAND_H

#include <string>
#include <vector>

namespace Genesis::Game::Command {
	class Command {

		public:

			Command(std::string command_name, std::vector<std::string> args): command_name(command_name), args(args) {}

			std::string get_name() {
				return command_name;
			}

			std::vector<std::string> get_arguments() {
				return args;
			}

		private:

			std::string command_name;
			std::vector<std::string> args;
	};
}
#endif