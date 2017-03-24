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
#include "Player.h"

// The player namespace
using namespace Genesis::Game::Model::Entity::Player;

/**
 * Forward the write packet function to the player's session
 *
 * @param packet
 *		The packet to write
 */
void Player::write(Genesis::Common::Networking::Packets::Packet* packet) {
	this->session->write(packet);
}

/**
 * Gets the faction of this player's account
 *
 * @returns
 *		The faction
 */
unsigned char Player::get_faction() {
	return this->faction;
}

/**
 * Gets the privilege level of this player's account
 *
 * @returns
 *		The privilege level
 */
unsigned char Player::get_privilege_level() {
	return this->privilege_level;
}

/**
 * Gets the maximum selectable game mode for this account
 *
 * @returns
 *		The maximum selectable game mode for character creation
 */
unsigned char Player::get_max_game_mode() {
	return this->max_game_mode;
}
			
unsigned int Player::get_points() {
	return this->points;
}
/**
 * Sets the faction for this player
 *
 * @param faction
 *		The faction id
 */
void Player::set_faction(unsigned char faction) {
	this->faction = faction;
}

/**
 * Sets the privilege level for this player
 *
 * @param privilege_level
 * 		The privilege level
 */
void Player::set_privilege_level(unsigned char privilege_level) {
	this->privilege_level = privilege_level;
}

/**
 * Sets the maximum selectable game mode
 *
 * @param max_game_mode
 *		The max game mode
 */
void Player::set_max_game_mode(unsigned char max_game_mode) {
	this->max_game_mode = max_game_mode;
}

/**
 * Sets the amount of item-mall points
 *
 * @param points
 *		The points
 */
void Player::set_points(unsigned int points) {
	this->points = points;
}

/**
 * Gets the index for this player instance
 *
 * @returns
 *		The player id
 */
unsigned int Player::get_index() {
	return this->player_id;
}

/**
 * Gets the character instance for this player
 *
 * @returns
 *		The character instance
 */
Genesis::Game::Model::Entity::Player::Character* Player::get_character() {
	return this->character;
}

/**
 * Sets the character instance for this player
 *
 * @param character
 *		The character instance
 */
void Player::set_character(Genesis::Game::Model::Entity::Player::Character* character) {

	// Set the selected_character flag
	this->selected_character = true;

	// Set the character instance
	this->character = character;
}