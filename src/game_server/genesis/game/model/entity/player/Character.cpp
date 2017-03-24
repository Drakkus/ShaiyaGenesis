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
#include <genesis/game/model/entity/player/Character.h>
#include <genesis/game/model/entity/player/Player.h>

// Use the Player entity namespace
using namespace Genesis::Game::Model::Entity::Player;

/**
 * Checks if this character instance is initialised
 *
 * @return
 *		If the character is initialised
 */
bool Character::is_initialised() const {
	return this->initialised;
}

/**
 * Writes the packet to the session
 *
 * @param packet
 *		The packet to write
 */
void Character::write(Genesis::Common::Networking::Packets::Packet* packet) {
	this->player->write(packet);
}

			// Setters and getters for the character's profession
			void Character::set_profession(unsigned char profession) {
				this->profession = profession;
			}

			unsigned char Character::get_profession() const {
				return this->profession;
			}

			// Setters and getters for the character's race
			void Character::set_race(unsigned char race) {
				this->race = race;
			}

			unsigned char Character::get_race() const {
				return this->race;
			}

			// Setters and getters for the character's game mode
			void Character::set_mode(unsigned char mode) {
				this->mode = mode;
			}

			unsigned char Character::get_mode() const {
				return this->mode;
			}

			// Setters and getters for the character's hair
			void Character::set_hair(unsigned char hair) {
				this->hair = hair;
			}

			unsigned char Character::get_hair() const {
				return this->hair;
			}

			// Setters and getters for the character's face
			void Character::set_face(unsigned char face) {
				this->face = face;
			}

			unsigned char Character::get_face() const {
				return this->face;
			}

			// Setters and getters for the character's height
			void Character::set_height(unsigned char height) {
				this->height = height;
			}

			unsigned char Character::get_height() const {
				return this->height;
			}

			// Setters and getters for the character's gender
			void Character::set_gender(unsigned char gender) {
				this->gender = gender;
			}

			unsigned char Character::get_gender() const {
				return this->gender;
			}

			// Setters and getters for the character's stat points
			void Character::set_stat_points(unsigned short stat_points) {
				this->stat_points = stat_points;
			}

			unsigned short Character::get_stat_points() const {
				return this->stat_points;
			}

			// Setters and getters for the character's skill points
			void Character::set_skill_points(unsigned short skill_points) {
				this->skill_points = skill_points;
			}

			unsigned short Character::get_skill_points() const {
				return this->skill_points;
			}

			// Setters and getters for the character's gold
			void Character::set_gold(unsigned int gold) {
				this->gold = gold;
			}

			unsigned int Character::get_gold() const {
				return this->gold;
			}

			// Setters and getters for the character's kill count
			void Character::set_kills(unsigned int kills) {
				this->kills = kills;
			}

			unsigned int Character::get_kills() const {
				return this->kills;
			}

			// Setters and getters for the character's death count
			void Character::set_deaths(unsigned int deaths) {
				this->deaths = deaths;
			}

			unsigned int Character::get_deaths() const {
				return this->deaths;
			}

			// Setters and getters for the character's victories
			void Character::set_victories(unsigned int victories) {
				this->victories = victories;
			}

			unsigned int Character::get_victories() const {
				return this->victories;
			}

			// Setters and getters for the character's defeats
			void Character::set_defeats(unsigned int defeats) {
				this->defeats = defeats;
			}

			unsigned int Character::get_defeats() const {
				return this->defeats;
			}

			// Setters and getters for the character's guild id
			void Character::set_guild_id(unsigned int guild_id) {
				this->guild_id = guild_id;
			}

			unsigned int Character::get_guild_id() const {
				return this->guild_id;
			}