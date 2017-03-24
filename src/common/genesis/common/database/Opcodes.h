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
#ifndef GENESIS_COMMON_DATABASE_OPCODES_H
#define GENESIS_COMMON_DATABASE_OPCODES_H

/**
 * Contains all the opcodes, that are used for communication between the authentication
 * and game servers, and the database server.
 */
namespace Genesis::Common::Database::Opcodes {

	/**
	 * Represents a packet sent from the authentication server, to the database server,
	 * requesting that a user authentication request is verified against the database details.
	 *
	 * The client sends the username requesting to login, and an MD5 hash of their password.
	 * The database server responds with an instance of {@link DatabaseStructs::AccountInfo}.
	 */
	const unsigned short USER_AUTH_REQUEST = 1;

	/**
	 * Represents a packet sent from the authentication server to the database server,
	 * requesting the server list.
	 */
	const unsigned short SERVER_LIST = 2;

	/**
	 * Represents a packet sent from the authentication server, informing the
	 * database server that a session should be deleted
	 */
	const unsigned short DELETE_SESSION = 3;
	
	/**
	 *
	 */
	const unsigned short GAME_DEFINITIONS_LOAD = 4;

	/**
	 * Represents a packet sent from the game server, informing the database
	 * server that a user has connected to the game server, and that it should
	 * verify the session.
	 */
	const unsigned short USER_GAME_CONNECT = 5;

	/**
	 * Represents a packet sent from the game server, requesting the details
	 * of a game account to be loaded from the database, and sent to the game server.
	 */
	const unsigned short GAME_USER_LOAD = 6;

	/**
	 * Checks if a character name is available.
	 */
	const unsigned short CHECK_AVAILABLE_NAME = 7;

	/**
	 * Handles the creation of a character
	 */
	const unsigned short CREATE_CHARACTER = 8;

	/**
	 * Gets the data displayed by the character list for a player
	 */
	const unsigned short GET_CHARACTER_LIST_DATA = 9;

	/**
	 * Handles the selection of a faction for the player
	 */
	const unsigned short SELECT_FACTION = 10;

	/**
	 * Handles the request to delete a character
	 */
	const unsigned short DELETE_CHARACTER = 11;

	/**
	 * Handles the request to restore a character that is pending deletion
	 */
	const unsigned short RESTORE_CHARACTER = 12;

	/**
	 * Handles the loading of a game character's data
	 */
	const unsigned short LOAD_GAME_CHARACTER = 13;

	/**
	 * Handles the loading of a game character's skills
	 */
	const unsigned short LOAD_GAME_CHARACTER_SKILLS = 14;
}

#endif