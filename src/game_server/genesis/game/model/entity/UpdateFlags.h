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
#ifndef GENESIS_GAME_MODEL_ENTITY_UPDATEFLAGS_H
#define GENESIS_GAME_MODEL_ENTITY_UPDATEFLAGS_H

/**
 * A utility class, which indicates whether an entity required an update
 * for an action performed.
 */
namespace Genesis::Game::Model::Entity {
	class UpdateFlags {

		public:

			// If an update is required on the entity's position
			bool is_movement_update_required();

			// If an update is required on the entity's equipment
			bool is_equipment_update_required();

			// If an update is required on the entity's buffs
			bool is_buff_update_required();

			// If an update is required on the entity's hitpoints
			bool is_hitpoint_update_required();

			// Resets the various update flags
			void reset_movement_update();
			void reset_equipment_update();
			void reset_buff_update();
			void reset_hitpoint_update();

		private:

			// If a movement update is required
			bool movement_update = false;

			// If an equipment update is required
			bool equipment_update = false;

			// If a buff update is required
			bool buff_update = false;

			// If an update on the hitpoints is required
			bool hitpoint_update = false;
	};
}
#endif