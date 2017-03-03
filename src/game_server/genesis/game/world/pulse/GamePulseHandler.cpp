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
#include "GamePulseHandler.h"

#include <genesis/common/logging/Logger.h>

// Use the pulse namespace
using namespace Genesis::Game::World::Pulse;

/**
 * Start the game pulse handler
 */
void GamePulseHandler::start() {
	if (this->is_running) {
		genesis_logger->error("Game pulse handler is already running.");
		return;
	}

	// The thread instance
	std::thread thread(std::bind(&GamePulseHandler::pulse, this));

	// Detach the thread
	thread.detach();

	// Start the pulse handler
	this->is_running = true;
}

/**
 * Begin processing game tasks.
 */
void GamePulseHandler::pulse() {

	// Loop while the pulse handler is running
	while(this->is_running) {

		// Lock the mutex
		this->mutex.lock();

		// If there are tasks to be processed
		if (tasks.size() != 0) {

			// The task to execute
			auto task = tasks.front();

			// Pop the task from the queue
			tasks.pop();
		
			// Execute the task
			task->execute();

			// Delete the task
			delete task;
		}

		// Unlock the mutex
		this->mutex.unlock();
	}
}

/**
 * Offers a new task to be processed
 *
 * @param task
 *		The task instance
 */
void GamePulseHandler::offer(Genesis::Game::World::Pulse::Task::Task* task) {

	// Lock the mutex
	this->mutex.lock();

	// Add the task to the queue
	this->tasks.push(task);

	// Unlock the mutex
	this->mutex.unlock();
}