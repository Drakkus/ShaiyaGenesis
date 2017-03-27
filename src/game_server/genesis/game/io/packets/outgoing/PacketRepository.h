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
#ifndef GENESIS_GAME_IO_PACKETS_OUTGOING_PACKETREPOSITORY_H
#define GENESIS_GAME_IO_PACKETS_OUTGOING_PACKETREPOSITORY_H

#include <genesis/game/model/entity/player/Character.h>
#include <genesis/game/model/entity/player/Player.h>

#include <string>

/**
 * Represents a utility class that is used to easily construct and send outgoing packets
 */
namespace Genesis::Game::Io::Packets::Outgoing {
	class PacketRepository {

		public:

			/**
			 * Gets the static instance for this {@code PacketRepository}
			 */
			static PacketRepository* get_instance() {
				static PacketRepository instance;
				return &instance;
			}

			/**
			 * Sends standard character data, such as the character's attributes, experience,
			 * gold, and guild name.
			 */
			void send_character_data(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends a notice message to the character
			 */
			void send_notice(Genesis::Game::Model::Entity::Player::Character*, const char*, std::initializer_list<const char*>);
			void send_notice_noargs(Genesis::Game::Model::Entity::Player::Character* character, const char* message) {
				this->send_notice(character, message, {});
			}

			/**
			 * Sends the character's current HP, MP and SP
			 */
			void send_current_hp_mp_sp(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the amount of Aeria Points the player currently possesses,
			 */
			void send_ap(Genesis::Game::Model::Entity::Player::Player*);

			/**
			 * Sends the bless values of the game world
			 */
			void send_bless_amount(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the attack and movement speed of a character, to the character
			 */
			void send_attack_movement_speed(Genesis::Game::Model::Entity::Player::Character*, Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the list of quests for the character
			 */
			void send_quest_list(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the active buffs/debuffs for the character
			 */
			void send_active_buffs(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the list of skills learned by this character
			 */
			void send_learned_skills(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the list of guilds for the character's faction
			 */
			void send_faction_guild_list(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the calculated extra stats, which are provided by item and skill bonuses
			 */
			void send_extra_stats(Genesis::Game::Model::Entity::Player::Character*);

			/**
			 * Sends the skill bars for this character
			 */
			void send_skillbars(Genesis::Game::Model::Entity::Player::Character*);
	};
}

// A macro for easily obtaining a packet repository instance
#define packet_repository Genesis::Game::Io::Packets::Outgoing::PacketRepository::get_instance()

#endif