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
#ifndef GENESIS_COMMON_GAME_RACECONSTANTS_H
#define GENESIS_COMMON_GAME_RACECONSTANTS_H

/**
 * Contains constants used by the game world
 */
namespace Genesis::Common::Game::Constants {

	// The human race
	const unsigned char RACE_HUMAN = 0;

	// The elven race
	const unsigned char RACE_ELF = 1;

	// The vail race
	const unsigned char RACE_VAIL = 2;

	// The deatheater race
	const unsigned char RACE_DEATHEATER = 3;

	/* The Fighter/Warrior class */
	const unsigned char CLASS_FIGHTER = 0;
	const unsigned char CLASS_WARRIOR = 0;

	/* The Defender/Guardian class */
	const unsigned char CLASS_DEFENDER = 1;
	const unsigned char CLASS_GUARDIAN = 1;

	/* The Ranger/Assassin class */
	const unsigned char CLASS_RANGER = 2;
	const unsigned char CLASS_ASSASSIN = 2;

	/* The Archer/Hunter class */
	const unsigned char CLASS_ARCHER = 3;
	const unsigned char CLASS_HUNTER = 3;

	/* The Mage/Pagan class */
	const unsigned char CLASS_MAGE = 4;
	const unsigned char CLASS_PAGAN = 4;

	/* The Priest/Oracle class */
	const unsigned char CLASS_PRIEST = 5;
	const unsigned char CLASS_ORACLE = 5;

	/* The Alliance of Light / Union of Fury factions */
	const unsigned char FACTION_AOL = 0;
	const unsigned char FACTION_UOF = 1;
};

#endif