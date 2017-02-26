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
	unsigned short USER_AUTH_REQUEST = 1;

	/**
	 *
	 */
	unsigned short USER_GAME_CONNECT = 2;
}

#endif