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
#include <genesis/game/model/entity/Position.h>

// Use the entity namespace
using namespace Genesis::Game::Model::Entity;

/**
 * Sets the values of the current position, to another position
 *
 * @param position
 *		The position
 */
void Position::set(Position* position) {
	this->set(position->get_map(), position->get_x(), position->get_y(), position->get_height(), position->get_direction());
}

/**
 * Sets the values of the current position
 *
 * @param map
 *		The map id
 *
 * @param x
 *		The x coordinate
 *
 * @param y
 *		The y coordinate
 *
 * @param height
 *		The height (z) coordinate
 * 
 * @param direction
 *		The direction to face
 */
void Position::set(unsigned short map, float x, float y, float height, unsigned short direction) {
	this->set_map(map);
	this->set_x_y_height(x, y, height);
	this->set_direction(direction);
}

/**
 * Sets the map value of the current position
 *
 * @param map
 *		The map
 */
void Position::set_map(unsigned short map) {
	this->map = map;
}

/**
 * Sets the x coordinate value
 *
 * @param x
 *		The x coordinate
 */
void Position::set_x(float x) {
	this->x = x;
}

/**
 * Sets the y coordinate value
 *
 * @param y
 *		The y coordinate
 */
void Position::set_y(float y) {
	this->y = y;
}

/**
 * Sets the height coordinate value
 *
 * @param height
 *		The height coordinate
 */
void Position::set_height(float height) {
	this->height = height;
}

/**
 * Sets the direction value
 *
 * @param direction
 *		The direction value
 */
void Position::set_direction(unsigned short direction) {
	this->direction = direction;
}

/**
 * A helper method to set both the x and y coordinates
 *
 * @param x
 *		The x coordinate
 *
 * @param y
 *		The y coordinate
 */
void Position::set_x_y(float x, float y) {
	this->set_x(x);
	this->set_y(y);
}

/**
 * A helper method to set the x, y, and height coordinates
 *
 * @param x
 *		The x coordinate
 *
 * @param y
 *		The y coordinate
 *
 * @param height
 *		The height coordinate
 */
void Position::set_x_y_height(float x, float y, float height) {
	this->set_x_y(x, y);
	this->set_height(height);
}

// Get the map id
unsigned short Position::get_map() {
	return this->map;
}

// Get the x coordinate
float Position::get_x() {
	return this->x;
}

// Get the y coordinate
float Position::get_y() {
	return this->y;
}

// Get the height coordinate
float Position::get_height() {
	return this->height;
}

// Get the direction
unsigned short Position::get_direction() {
	return this->direction;
}