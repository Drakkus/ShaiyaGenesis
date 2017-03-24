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
#include <genesis/game/model/entity/Attributes.h>

// Use the entity namespace
using namespace Genesis::Game::Model::Entity;

/**
 * Gets the level of the entity
 *
 * @returns
 *		The level of the entity
 */
unsigned short Attributes::get_level() {
	return this->level;
}

/**
 * Gets the strength of the entity
 *
 * @returns
 *		The strength value
 */
unsigned int Attributes::get_strength() {
	return this->strength;
}

/**
 * Gets the dexterity of the entity
 *
 * @returns
 *		The dexterity value
 */
unsigned int Attributes::get_dexterity() {
	return this->dexterity;
}

/**
 * Gets the resistance of the entity
 *
 * @returns
 *		The resistance value
 */
unsigned int Attributes::get_resistance() {
	return this->resistance;
}

/**
 * Gets the intelligence of the entity
 *
 * @returns
 *		The intelligence value
 */
unsigned int Attributes::get_intelligence() {
	return this->intelligence;
}

/**
 * Gets the wisdom of the entity
 *
 * @returns
 *		The wisdom value
 */
unsigned int Attributes::get_wisdom() {
	return this->wisdom;
}

/**
 * Gets the luck of the entity
 *
 * @returns
 *		The luck value
 */
unsigned int Attributes::get_luck() {
	return this->luck;
}

/**
 * Gets the current HP of the entity
 *
 * @returns
 *		The current HP
 */
unsigned int Attributes::get_current_hp() {
	return this->current_hitpoints;
}

/**
 * Gets the current MP of the entity
 *
 * @returns
 *		The current MP
 */
unsigned int Attributes::get_current_mp() {
	return this->current_mana;
}

/**
 * Gets the current SP of the entity
 *
 * @returns
 *		The current SP
 */
unsigned int Attributes::get_current_sp() {
	return this->current_stamina;
}

/**
 * Gets the current experience of the entity
 *
 * @returns
 *		The current experience of the entity
 */
unsigned int Attributes::get_current_experience() {
	return this->current_experience;
}

/**
 * Sets the current level of the entity
 *
 * @param level
 *		The level
 */
void Attributes::set_level(unsigned short level) {
	this->level = level;
}

/**
 * Sets the strength of the entity
 *
 * @param strength
 *		The strength
 */
void Attributes::set_strength(unsigned int strength) {
	this->strength = strength;
}

/**
 * Sets the dexterity of the entity
 *
 * @param dexterity
 *		The dexterity
 */
void Attributes::set_dexterity(unsigned int dexterity) {
	this->dexterity = dexterity;
}

/**
 * Sets the resistance of the entity
 *
 * @param resistance
 *		The resistance
 */
void Attributes::set_resistance(unsigned int resistance) {
	this->resistance = resistance;
}

/**
 * Sets the intelligence of the entity
 *
 * @param intelligence
 *		The intelligence
 */
void Attributes::set_intelligence(unsigned int intelligence) {
	this->intelligence = intelligence;
}

/**
 * Sets the wisdom of the entity
 *
 * @param wisdom
 *		The wisdom
 */
void Attributes::set_wisdom(unsigned int wisdom) {
	this->wisdom = wisdom;
}

/**
 * Sets the luck of the entity
 *
 * @param luck
 *		The luck of the entity
 */
void Attributes::set_luck(unsigned int luck) {
	this->luck = luck;
}

/**
 * Sets the current hitpoints of the entity
 *
 * @param current_hitpoints
 *		The current hitpoints
 */
void Attributes::set_current_hitpoints(unsigned int current_hitpoints) {
	this->current_hitpoints = current_hitpoints;
}

/**
 * Sets the current mana of the entity
 *
 * @param current_mana
 *		The current mana
 */
void Attributes::set_current_mana(unsigned int current_mana) {
	this->current_mana = current_mana;
}

/**
 * Sets the current staminda of the entity
 *
 * @param current_stamina
 *		The stamina of the entity
 */
void Attributes::set_current_stamina(unsigned int current_stamina) {
	this->current_stamina = current_stamina;
}

/**
 * Sets the current experience of the entity
 *
 * @param current_experience
 *		The new experience of the entity
 */
void Attributes::set_current_experience(unsigned int current_experience) {
	this->current_experience = current_experience;
}