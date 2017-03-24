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
#ifndef GENESIS_GAME_MODEL_ENTITY_ATTRIBUTES_H
#define GENESIS_GAME_MODEL_ENTITY_ATTRIBUTES_H

/**
 * Represents the attributes of a game entity (ie Mob, Character, NPC).
 */
namespace Genesis::Game::Model::Entity {
	class Attributes {

		public:

			// Gets the entity's stats
			unsigned short get_level();
			unsigned int get_strength();
			unsigned int get_dexterity();
			unsigned int get_resistance();
			unsigned int get_intelligence();
			unsigned int get_wisdom();
			unsigned int get_luck();
			unsigned int get_current_hp();
			unsigned int get_current_mp();
			unsigned int get_current_sp();
			unsigned int get_current_experience();

			// Sets the entity's stats
			void set_level(unsigned short level);
			void set_strength(unsigned int strength);
			void set_dexterity(unsigned int dexterity);
			void set_resistance(unsigned int resistance);
			void set_intelligence(unsigned int intelligence);
			void set_wisdom(unsigned int wisdom);
			void set_luck(unsigned int luck);
			void set_current_hitpoints(unsigned int current_hitpoints);
			void set_current_mana(unsigned int current_mana);
			void set_current_stamina(unsigned int current_stamina);
			void set_current_experience(unsigned int current_experience);

		private:

			// The level of the entity
			unsigned short level;

			// The strength of the entity
			unsigned int strength;

			// The dexterity of the entity
			unsigned int dexterity;

			// The physical resistance of the entity
			unsigned int resistance;

			// The intelligence of the entity
			unsigned int intelligence;

			// The wisdom of the entity
			unsigned int wisdom;

			// The luck of the entity
			unsigned int luck;

			// The current hitpoints of the entity
			unsigned int current_hitpoints;

			// The current mana of the entity
			unsigned int current_mana;

			// The current stamina of the entity
			unsigned int current_stamina;

			// The current experience of the entity
			unsigned int current_experience;
	};
}
#endif