#ifndef GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_AUTHRESPONSE_H
#define GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_AUTHRESPONSE_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::Structs::Auth {

	// Represents the response to an {@code Auth_AuthRequest}
	struct AuthResponse {

		// The user id
		unsigned int user_id;

		// The status of the user (result of authentication request, ie valid, banned, invalid password)
		unsigned char status;

		// The privilege level of the user (ie staff member values, Game Sage, Game Master, Administrator)
		unsigned char privilege_level;

		// The session keys, used for identify the user
		unsigned char identity_keys[16];
	};


}
#endif