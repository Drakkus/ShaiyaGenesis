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
#ifndef GENESIS_GAME_WORLD_PULSE_TASK_IMPL_LOADPLAYERTASK_H
#define GENESIS_GAME_WORLD_PULSE_TASK_IMPL_LOADPLAYERTASK_H

#include <genesis/game/world/pulse/task/Task.h>
#include <genesis/game/model/entity/player/Player.h>

#include <boost/shared_ptr.hpp>

#include <iostream>

/**
 * Represents a task used to load a player's details from the database server
 */
namespace Genesis::Game::World::Pulse::Task::Impl {
	class LoadPlayerTask : public Task {

		public:

			/**
			 * The constructor for this task, which will define the player instance
			 * to operate on
			 *
			 * @param player
			 *		The player instance
			 */
			LoadPlayerTask(Genesis::Game::Model::Entity::Player::Player* player) : player(player) {}

			// Execute the task
			void execute();

		private:

			// The player instance
			Genesis::Game::Model::Entity::Player::Player* player;
	};
}
#endif