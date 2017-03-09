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
 * Gets the strength of the entity
 *
 * @returns
 *		The strength value
 */
unsigned short Attributes::get_strength() {
	return this->strength;
}

/**
 * Gets the dexterity of the entity
 *
 * @returns
 *		The dexterity value
 */
unsigned short Attributes::get_dexterity() {
	return this->dexterity;
}

/**
 * Gets the resistance of the entity
 *
 * @returns
 *		The resistance value
 */
unsigned short Attributes::get_resistance() {
	return this->resistance;
}

/**
 * Gets the intelligence of the entity
 *
 * @returns
 *		The intelligence value
 */
unsigned short Attributes::get_intelligence() {
	return this->intelligence;
}

/**
 * Gets the wisdom of the entity
 *
 * @returns
 *		The wisdom value
 */
unsigned short Attributes::get_wisdom() {
	return this->wisdom;
}

unsigned short Attributes::get_luck() {
	return this->luck;
}

unsigned int Attributes::get_current_hp() {
	return this->current_hitpoints;
}

unsigned int Attributes::get_current_mp() {
	return this->current_mana;
}

unsigned int Attributes::get_current_sp() {
	return this->current_stamina;
}

unsigned int Attributes::get_current_experience() {
	return this->current_experience;
}

// Sets the entity's stats
void Attributes::set_strength(unsigned short strength) {
	this->strength = strength;
}

void Attributes::set_dexterity(unsigned short dexterity) {
	this->dexterity = dexterity;
}

void Attributes::set_resistance(unsigned short resistance) {
	this->resistance = resistance;
}

void Attributes::set_intelligence(unsigned short intelligence) {
	this->intelligence = intelligence;
}

void Attributes::set_wisdom(unsigned short wisdom) {
	this->wisdom = wisdom;
}

void Attributes::set_luck(unsigned short luck) {
	this->luck = luck;
}

void Attributes::set_current_hitpoints(unsigned int current_hitpoints) {
	this->current_hitpoints = current_hitpoints;
}

void Attributes::set_current_mana(unsigned int current_mana) {
	this->current_mana = current_mana;
}

void Attributes::set_current_stamina(unsigned int current_stamina) {
	this->current_stamina = current_stamina;
}

void Attributes::set_current_experience(unsigned int current_experience) {
	this->current_experience = current_experience;
}