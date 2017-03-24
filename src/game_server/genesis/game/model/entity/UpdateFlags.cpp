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
#include "UpdateFlags.h"

// Use the entity namespace
using namespace Genesis::Game::Model::Entity;

/**
 * If an update on the entity's movement / position is required
 */
bool UpdateFlags::is_movement_update_required() {
	return this->movement_update;
}

/**
 * If an update on the entity's equipped items is required
 */
bool UpdateFlags::is_equipment_update_required() {
	return this->equipment_update;
}

/** 
 * If an update is required on the entity's buffs/debuffs
 */
bool UpdateFlags::is_buff_update_required() {
	return this->buff_update;
}

/** 
 * If an update is required on the entity's HP/MP/SP
 */
bool UpdateFlags::is_hitpoint_update_required() {
	return this->hitpoint_update;
}

/**
 * Reset the movement update flag
 */
void UpdateFlags::reset_movement_update() {
	this->movement_update = false;
}

/**
 * Reset the equipment update flag
 */
void UpdateFlags::reset_equipment_update() {
	this->equipment_update = false;
}

/**
 * Reset the buff update flag
 */
void UpdateFlags::reset_buff_update() {
	this->buff_update = false;
}

/**
 * Reset the hitpoint update flag
 */
void UpdateFlags::reset_hitpoint_update() {
	this->hitpoint_update = false;
}