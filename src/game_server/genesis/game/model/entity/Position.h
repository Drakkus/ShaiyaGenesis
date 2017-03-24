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
#ifndef GENESIS_GAME_MODEL_ENTITY_POSITION_H
#define GENESIS_GAME_MODEL_ENTITY_POSITION_H

/**
 * Represents the position of a game entity (ie Mob, Character, NPC).
 */
namespace Genesis::Game::Model::Entity {
	class Position {

		public:

			// A default constructor
			Position() {
				this->set(0, 0, 0, 0, 0);
			}

			// A constructor instance
			Position(unsigned short map, float x, float y, float height, unsigned short direction) {
				this->set(map, x, y, height, direction);
			}
			
			// Set the position
			void set(Position* position);
			void set(unsigned short map, float x, float y, float height, unsigned short direction);
			void set_map(unsigned short map);
			void set_x(float x);
			void set_y(float y);
			void set_height(float height);
			void set_direction(unsigned short direction);
			void set_x_y(float x, float y);
			void set_x_y_height(float x, float y, float height);

			// Get the map id
			unsigned short get_map();

			// Get the x coordinate
			float get_x();

			// Get the y coordinate
			float get_y();

			// Get the height coordinate
			float get_height();

			// Get the direction
			unsigned short get_direction();

			// Overload the equal comparison operator for position comparisons
			bool operator==(Genesis::Game::Model::Entity::Position* position) {
				return ((this->get_map() == position->get_map()) && 
					(this->get_x() == position->get_x()) && 
					(this->get_y() == position->get_y()) && 
					(this->get_height() == position->get_height()) &&
					(this->get_direction() == position->get_direction()));
			}

		private:

			// The map of the entity
			unsigned short map;

			// The coordinates
			float x;
			float y;
			float height;

			// The direction the entity is facing
			unsigned short direction;
	};
}
#endif