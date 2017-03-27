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
#include "LoadCharacterGameWorldTask.h"
 
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/Opcodes.h>
#include <genesis/common/packets/Opcodes.h>
#include <genesis/common/database/structs/game/CharacterLoadInfo.h>

#include <genesis/game/command/Command.h>
#include <genesis/game/world/GameWorld.h>
#include <genesis/game/model/entity/player/Character.h>
#include <genesis/game/model/entity/Position.h>
#include <genesis/game/io/packets/outgoing/PacketRepository.h>

#include <iostream>
#include <ctime>

// Use the task namespace
using namespace Genesis::Game::World::Pulse::Task::Impl;
 
/**
 * Begin loading the character from the database
 */
void LoadCharacterGameWorldTask::execute() {
 
    // Load the character's details from the database
    load_character_data();
}
 
/**
 * Loads the character's data from the database
 */
void LoadCharacterGameWorldTask::load_character_data() {
     
    // The character instance
    auto character = new Genesis::Game::Model::Entity::Player::Character(player, character_id);
 
    // The client instance
    auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();
 
    // The current task instance
    auto current = this;
 
    // The packet builder instance
    auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::LOAD_GAME_CHARACTER);
 
    // Write the player id, character id, and server id
    bldr->write_int(player->get_index());
    bldr->write_int(character->get_index());
    bldr->write_byte(Genesis::Game::World::GameWorld::get_instance()->get_server_id());
 
    // Write the packet to the database server
    db_client->write(bldr->to_packet(), [current, character](unsigned char* data, unsigned int length) {
 
        // The response from the database server
        unsigned char response = (data[0] & 0xFF);
 
        // If the response was not 0 (0 is success), then we delete the character instance and cancel loading
        if (response != 0) {
 
            // The packet builder instance
            auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::CHARACTER_SELECTION);
 
            // Write a failed opcode
            bldr->write_byte(response);
 
            // Write the character id
            bldr->write_int(character->get_index());
 
            // Write the packet to the character instance
            character->write(bldr->to_packet());
 
            // Delete the packet builder instance
            delete bldr;
             
            // Delete the character instance
            delete character;
            return;
 
        // If the response was 0, then we successfully loaded the character data
        } else {
 
            // The character info
            Genesis::Common::Database::Structs::Game::CharacterLoadInfo info;
 
            // Copy the data
            std::memcpy(&info, data + 1, sizeof(info));
 
            // Null-terminate the name
            info.name[sizeof(info.name) - 1] = '\0';
 
            // The character's name
            std::string character_name(info.name);
 
            // Set the character name
            character->set_name(character_name);
 
            // Set the character's profession, race and mode
            character->set_profession(info.profession);
            character->set_race(info.race);
            character->set_mode(info.mode);
 
            // Set the character's stat points, skill points, gold, kills, etc
            character->set_stat_points(info.stat_points);
            character->set_skill_points(info.skill_points);
            character->set_gold(info.gold);
            character->set_kills(info.kills);
            character->set_deaths(info.deaths);
            character->set_victories(info.victories);
            character->set_defeats(info.defeats);
            character->set_guild_id(info.guild_id);
 
            // The character's position
            character->get_position()->set(info.map_id, info.position_x, info.position_y, info.position_height, info.direction);
 
            // The character's attributes
            auto attributes = character->get_attributes();
 
            // Set the attributes
            attributes->set_level(info.level);
            attributes->set_strength(info.strength);
            attributes->set_dexterity(info.dexterity);
            attributes->set_resistance(info.resistance);
            attributes->set_intelligence(info.intelligence);
            attributes->set_wisdom(info.wisdom);
            attributes->set_luck(info.luck);
            attributes->set_current_hitpoints(info.current_hp);
            attributes->set_current_mana(info.current_mp);
            attributes->set_current_stamina(info.current_sp);

            current->do_test(character);
            
            // Load the character's skills
            current->load_character_skills(character);

            // Load the character's items
            current->load_character_items(character);

            // The character's active buffs
            current->load_character_active_buffs(character);

            // The character's skill bars
            current->load_character_skill_bars(character);

            // The character's quests
            current->load_character_quests(character);
        }
    });
 
 
    // Delete the packet builder instance
    delete bldr;
}
 
/**
 * Loads the skills for the character, from the database
 *
 * @param character
 *      The character instance
 */
void LoadCharacterGameWorldTask::load_character_skills(Genesis::Game::Model::Entity::Player::Character* character) {
 
    // The client instance
    auto db_client = Genesis::Game::World::GameWorld::get_instance()->get_db_client();
 
    // The current task instance
    auto current = this;
 
    // The packet builder instance
    auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::LOAD_GAME_CHARACTER_SKILLS);
 
    // Write the player id, character id, and server id
    bldr->write_int(player->get_index());
    bldr->write_int(character->get_index());
    bldr->write_byte(Genesis::Game::World::GameWorld::get_instance()->get_server_id());
 
    // Write the packet to the database server
    db_client->write(bldr->to_packet(), [current, character](unsigned char* data, unsigned int length) {
 
        // The number of skills learnt by the character
        unsigned char skill_count = (data[0] & 0xFF);
 
        // Loop through the skills
        for (int i = 0; i < skill_count; i++) {
 
            // The skill id
            unsigned short skill_id;
 
            // The skill level
            unsigned char skill_level;
 
            // The cooldown remaining on the skill
            unsigned int cooldown;
        }
    });
 
 
    // Delete the packet builder instance
    delete bldr;
}
 
/**
 * Loads the items for the character, from the database
 *
 * @param character
 *      The character instance
 */
void LoadCharacterGameWorldTask::load_character_items(Genesis::Game::Model::Entity::Player::Character* character) {
    std::cout << "Load items for character name: " << character->get_name() << std::endl;
 
}

/**
 * Loads the items for the character, from the database
 *
 * @param character
 *      The character instance
 */
void LoadCharacterGameWorldTask::load_character_quests(Genesis::Game::Model::Entity::Player::Character* character) {
    std::cout << "Load quests for character name: " << character->get_name() << std::endl;
 
}

/**
 * Loads the items for the character, from the database
 *
 * @param character
 *      The character instance
 */
void LoadCharacterGameWorldTask::load_character_active_buffs(Genesis::Game::Model::Entity::Player::Character* character) {
    std::cout << "Load active buffs for character name: " << character->get_name() << std::endl;
 
}

/**
 * Loads the items for the character, from the database
 *
 * @param character
 *      The character instance
 */
void LoadCharacterGameWorldTask::load_character_skill_bars(Genesis::Game::Model::Entity::Player::Character* character) {
    std::cout << "Load skill bars for character name: " << character->get_name() << std::endl;
 
}

void LoadCharacterGameWorldTask::do_test(Genesis::Game::Model::Entity::Player::Character* character) {
// The packet builder instance
            auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::CHARACTER_SELECTION);
 
            // Write a failed opcode
            bldr->write_byte(0);

            // Write the character id
            bldr->write_int(character->get_index());
 
            // Write the packet to the character instance
            character->write(bldr->to_packet());

 
    // The sixth packet
    Genesis::Common::Networking::Packets::PacketBuilder pkt6(0x0D0D);
    character->write(pkt6.to_packet());
 
    // List of guilds in the guild master
    packet_repository->send_faction_guild_list(character);
 
    // The eight packet
    Genesis::Common::Networking::Packets::PacketBuilder pkt8(0x0E0D);
    character->write(pkt8.to_packet());
 
    // Send the character data
    packet_repository->send_character_data(character);
 
    // Skills
    packet_repository->send_learned_skills(character);
 
    // 11 Buffs
    packet_repository->send_active_buffs(character);
 
    // 12 Quests
    packet_repository->send_quest_list(character);
 
    // 14 Attack Speed, Movement Speed
    packet_repository->send_attack_movement_speed(character, character);
 
    // 15 Bless
    packet_repository->send_bless_amount(character);
 
    // Account AP
    packet_repository->send_ap(character->get_player());

 	// The current time
 	//std::time current_time = std::time();s

    // 18 and 19 = something to do with time
    // 18
    Genesis::Common::Networking::Packets::PacketBuilder pkt18(0x0114);
    pkt18.write_int(1483326283);
    //unsigned char payload18[] = {0x16,0x27,0xF8,0x41};
    //pkt18.write_bytes(payload18, sizeof(payload18));
    //character->write(pkt18.to_packet());
 
    // 19
    Genesis::Common::Networking::Packets::PacketBuilder pkt19(0x0115);
    pkt19.write_int(1483326283);
   // character->write(pkt19.to_packet());
 // The command dispatcher instance
        auto dispatcher = Genesis::Game::World::GameWorld::get_instance()->get_command_dispatcher();
        std::vector<std::string> args;
        args.push_back("hello");

        auto command = new Genesis::Game::Command::Command("notice", args);

        // Register the listener
        dispatcher->dispatch(character, command);

 
    // 22 Skillbar
    packet_repository->send_skillbars(character);
 
    // Ojs, Stats
    packet_repository->send_extra_stats(character);
 
    // Current HP, MP, SP
    packet_repository->send_current_hp_mp_sp(character);

    // Send a welcome notice
  //  packet_repository->send_notice(character, "Welcome to Shaiya Genesis, %s!", { character->get_name().c_str() });
}