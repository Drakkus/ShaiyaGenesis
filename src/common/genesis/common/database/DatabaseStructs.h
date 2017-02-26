#ifndef GENESIS_COMMON_DATABASE_DATABASESTRUCTS_H
#define GENESIS_COMMON_DATABASE_DATABASESTRUCTS_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::DatabaseStructs {

	// Represents an authentication request
	struct Auth_AuthRequest {

		// The name of the user
		unsigned char username[19];

		// The password of the user, as an MD5 hash
		unsigned char password[32];

		// The ip address of the user requesting authentication (IPV4)
		unsigned char ip_address[15];
	};

	// Represents the response to an {@code Auth_AuthRequest}
	struct Auth_AuthResponse {

		// The name of the user
		unsigned char username[19];

		// The user id
		unsigned int user_id;

		// The status of the user (result of authentication request, ie valid, banned, invalid password)
		unsigned char status;

		// The privilege level of the user (ie staff member values, Game Sage, Game Master, Administrator)
		unsigned char privilege_level;

		// The session keys, used for identify the user
		unsigned char identity_keys[16];
	};

	// Represents an authentication request to a game server
	struct Game_AuthRequest {

		// The user id
		unsigned int user_id;

		// The identity keys of the user
		unsigned char identity_keys[16];

		// The ip address of the user requesting authentication (IPV4)
		unsigned char ip_address[15];
	};

	// Represents the loaded details of a GameCharacter
	struct Game_GameCharacter {

		// The id of the character
		unsigned int char_id;

		// The name of the character
		unsigned char character[32];

		// The race of the character
		unsigned char char_race;

		// The class of the character
		unsigned char char_class;

		// The sex of the character
		unsigned char char_sex;
	};

	// Represents the response to an {@code Game_AuthRequest}
	struct Game_AuthResponse {

		// The name of the user
		unsigned char username[19];

		// The privilege level of the user
		unsigned char privilege_level;

		// The characters of this account
		Game_GameCharacter game_chars[5];
	};
}
#endif