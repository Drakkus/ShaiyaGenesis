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
#ifndef GENESIS_COMMON_GAME_DEFINITIONS_SKILLDEFINITION_H
#define GENESIS_COMMON_GAME_DEFINITIONS_SKILLDEFINITION_H

namespace Genesis::Common::Game::Definitions {
	struct SkillDefinition {

		// The skill id
		unsigned short skill_id;

		// The skill level
		unsigned char skill_level;

		// The name of the skill
		char skill_name[32];

		// Is the skill usable by AOL
		char usable_light;

		// Is the skill usable by UOF
		char usable_fury;

		// Classes that the skill is usable by
		char usable_fighter;
		char usable_defender;
		char usable_ranger;
		char usable_archer;
		char usable_mage;
		char usable_priest;

		// The chain skill id, which must be used before this skill can be cast
		unsigned short chain_skill_id;

		// The required level to learn this skill
		unsigned short required_level;

		// The game mode required to learn this skill
		unsigned char required_mode;

		// The skill points required to learn this skill
		unsigned char required_skillpoints;
	};
}
#endif