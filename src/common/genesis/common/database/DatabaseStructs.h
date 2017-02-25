#ifndef GENESIS_COMMON_DATABASE_DATABASESTRUCTS_H
#define GENESIS_COMMON_DATABASE_DATABASESTRUCTS_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::DatabaseStructs {

	// Represents an authentication request
	struct AuthRequest {

		// The name of the user
		char username[19];

		// The password of the user
		char password[19];
	};

	// Represents an account's information
	struct AccountInfo {

		// The name of the user
		char username[19];

		// The user id
		unsigned int user_id;

		// The status of the user (result of authentication request)
		unsigned char status;

		// The privilege level of the user (ie staff member values, Game Sage, Game Master, Administrator)
		unsigned char privilege_level;
	};

}
#endif