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
#include <genesis/game/model/entity/Entity.h>

// The entity namespace
using namespace Genesis::Game::Model::Entity;

/**
 * Handle the clean-up and destruction of a game entity
 */
void Entity::destroy() {

	// Delete the attributes instance
	delete this->attributes;

	// Delete the position instance
	delete this->position;

	// Delete the update flags instance
	delete this->update_flags;
}

// Gets the name of the entity
std::string& Entity::get_name() {
	return this->name;
}

// Sets the name of the entity
void Entity::set_name(const std::string& name) {
	this->name = name;
}

/**
 * Gets the index for this entity
 *
 * @returns
 *		The unique index
 */
unsigned int Entity::get_index() {
	return this->index;
}

/**
 * Gets the attributes instance for this entity
 *
 * @returns
 *		The attribute
 */
Genesis::Game::Model::Entity::Attributes* Entity::get_attributes() {
	return this->attributes;
}

/**
 * Gets the position of this entity
 *
 * @returns
 *		The position
 */
Genesis::Game::Model::Entity::Position* Entity::get_position() {
	return this->position;
}

/**
 * Gets the update flags of this entity
 *
 * @returns
 *		The update flags
 */
Genesis::Game::Model::Entity::UpdateFlags* Entity::get_update_flags() {
	return this->update_flags;
}