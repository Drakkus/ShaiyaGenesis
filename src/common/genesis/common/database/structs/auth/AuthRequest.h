#ifndef GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_AUTHREQUEST_H
#define GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_AUTHREQUEST_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::Structs::Auth {

	// Represents an authentication request
	struct AuthRequest {

		// The name of the user
		unsigned char username[19];

		// The password of the user, as an MD5 hash
		unsigned char password[32];

		// The ip address of the user requesting authentication (IPV4)
		unsigned char ip_address[15];
	};

}
#endif