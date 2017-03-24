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
#ifndef GENESIS_GAME_MODEL_ENTITY_ENTITY_H
#define GENESIS_GAME_MODEL_ENTITY_ENTITY_H

#include <genesis/game/model/entity/Attributes.h>
#include <genesis/game/model/entity/Position.h>
#include <genesis/game/model/entity/UpdateFlags.h>

#include <string>

/**
 * Represents an entity that can interact with the game world (ie all mobs, characters, npcs)
 */
namespace Genesis::Game::Model::Entity {
	class Entity {

		public:

			/**
			 * The constructor for this entity instance
			 */
			Entity(unsigned int index) : index(index) {}

			/**
			 * The destructor for this entity
			 */
			~Entity() {

				// Call the destroy function
				this->destroy();
			}

			// The destructor function
			void destroy();

			// Gets the index of this entity
			unsigned int get_index();

			// Gets the attributes instance for this entity
			Genesis::Game::Model::Entity::Attributes* get_attributes();
			
			// Gets the position instance for this entity
			Genesis::Game::Model::Entity::Position* get_position();

			// Gets teh update flags for this entity
			Genesis::Game::Model::Entity::UpdateFlags* get_update_flags();
			
			// Gets the name of the entity
			std::string& get_name();

			// Sets the name of the entity
			void set_name(const std::string& name);

		private:

			// The index of the entity (character id, mob unique index, etc)
			unsigned int index;

			// The name of the entity
			std::string name;

			// The attributes of the entity
			Genesis::Game::Model::Entity::Attributes* attributes = new Genesis::Game::Model::Entity::Attributes();

			// The position of the entity
			Genesis::Game::Model::Entity::Position* position = new Genesis::Game::Model::Entity::Position();
			
			// The update flags of the entity
			Genesis::Game::Model::Entity::UpdateFlags* update_flags = new Genesis::Game::Model::Entity::UpdateFlags();
	};
}
#endif