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
#ifndef GENESIS_COMMON_PACKETS_OPCODES_H
#define GENESIS_COMMON_PACKETS_OPCODES_H

/**
* Here we define all the various opcodes for the packets used throughout the Shaiya protocol.
* Theoretically, these values should never change, even throughout episodes.
*
* TODO: Re-check encryption algorithm, perhaps there's a seperate procedure that attempts
* to randomize game packet opcodes depending on the client version.
*/
namespace Genesis::Common::Packets::Opcodes {

	/* The ping packet sent by the client, which is used to ensure the client is still connected */
	const unsigned short PING = 0x03;

	/* Called whenever a login session is terminated, either through ALT + F4, or the "Quit Game" button */
	const unsigned short LOGIN_TERMINATE = 0x010B;

	/* The login handshake is the first packet sent from the server, to the client, and is responsible
	for defining the values used for the encryption algorithm. */
	const unsigned short LOGIN_HANDSHAKE = 0xA101;

	/* A standard login request, sent to the login server, which contains the username and password
	values. The server responds with the login result, and if the login result equals 0,
	then the server also sends the user id, privilege level, and session identity keys. */
	const unsigned short LOGIN_REQUEST = 0xA102;

	/* The server list packet sent by the server, which contains the various server ids,
	the server names, and the server status/population */
	const unsigned short SERVER_LIST_DETAILS = 0xA201;

	/* Sent by the client when selecting the game server. The client sends the server id
	it wishes to connect to, as well as the client version. If the client version matches
	that of the server, the packet contains the ip address of the game server that the client
	should attempt to connect to. */
	const unsigned short SELECT_GAME_SERVER = 0xA202;

	/* The game handshake request sent by the client, which should contain the previously assigned
	user id and session identity keys from the login request. */
	const unsigned short GAME_HANDSHAKE = 0xA301;

	/* Contains information about the various characters for the character selection list */
	const unsigned short CHARACTER_LIST = 0x0101;

	/* Contains information about a character creation request from the current game account */
	const unsigned short CREATE_CHARACTER = 0x0102;

	/* Contains information about a character deletion request from the current game account */
	const unsigned short DELETE_CHARACTER = 0x0103;

	/* Represents a request to enter the game world with a specific character */
	const unsigned short CHARACTER_SELECTION = 0x0104;

	/* Contains specific details about the game character, such as the max HP, Gold, Stat/Skill Points,
	Kills/Deaths, and guild name */
	const unsigned short CHARACTER_DETAILS = 0x0105;

	/* Contains details about the skills the character has learned, their levels, their index (for use
	in the cast skill packet), and the remaining cooldown */
	const unsigned short CHARACTER_SKILLS = 0x0108;

	/* Contains the current faction of the game account (either Light, Fury, or undecided) */
	const unsigned short ACCOUNT_FACTION = 0x0109;

	/* Contains the character's active buffs and debuffs */
	const unsigned short CHARACTER_ACTIVE_BUFFS = 0x010A;

	/* Contains the character's skill bar arrangements */
	const unsigned short CHARACTER_SKILL_BARS = 0x010B;

	/* Contains the request to restore a deleted character */
	const unsigned short RESTORE_CHARACTER = 0x010F;

	/* Checks if a given character name is available */
	const unsigned short AVAILABLE_CHARACTER_NAME = 0x0119;

	/* Contains the amount of bless in the game world */
	const unsigned short BLESS_AMOUNT = 0x0211;

	/* Contains the amount of "Aeria Points" the account possesses */
	const unsigned short ACCOUNT_AERIA_POINTS = 0x2601;

	/* */
	const unsigned short CHANGE_APPEARANCE = 0x0507;

	/* Contains the attack and movement speed values for a character */
	const unsigned short CHARACTER_ATTACK_MOVEMENT_SPEED = 0x051C;

	/* Contains the values of the character's current HP/MP/SP */
	const unsigned short CURRENT_CHARACTER_HITPOINTS = 0x0521;
	
	/* Contains variable character stats, such as the total yellow stats provided by gear,
	the minimum/maximum attack powers, the defense, and the resistance values */
	const unsigned short ADDITIONAL_CHARACTER_STATS = 0x0526;

	/* Contains the list of quests for the character */
	const unsigned short QUEST_LIST = 0x0901;

	/* Contains the list of guilds for the character */
	const unsigned short GUILD_LIST = 0x2F0D;

	/* Sent from the server to the client, containing a notice to be sent to the player */
	const unsigned short NOTICE = 0xF90B;
}

#endif