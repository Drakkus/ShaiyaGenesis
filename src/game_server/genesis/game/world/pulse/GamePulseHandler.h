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
#ifndef GENESIS_GAME_WORLD_PULSE_GAMEPULSEHANDLER_H
#define GENESIS_GAME_WORLD_PULSE_GAMEPULSEHANDLER_H

#include <genesis/game/world/pulse/task/Task.h>

#include <boost/shared_ptr.hpp>

#include <queue>
#include <thread>
#include <mutex>
#include <functional>

/**
 * The game pulse handler, which is used to process game world tasks.
 */
namespace Genesis::Game::World::Pulse {
	class GamePulseHandler {

		public:

			// Starts the pulse handler
			void start();

			// Begins processing a task
			void pulse();

			// Pulse for player updating
			void pulse_player_updates();

			// Pulse for mob updating
			void pulse_mob_updates();

			// Offers a new task to the pulse handler
			void offer(Genesis::Game::World::Pulse::Task::Task* task);
			
		private:

			// If the pulse handler is running
			bool is_running = false;

			// The queue of pending tasks
			std::queue<Genesis::Game::World::Pulse::Task::Task*> tasks;

			// The mutex
			std::mutex mutex;
	};
}
#endif