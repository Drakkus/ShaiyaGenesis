#ifndef GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_SERVERSTATUS_H
#define GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_SERVERSTATUS_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::Structs::Auth {

	// Represents a server instance
	struct Server {

		// The server id
		unsigned char server_id;

		// The current population of the server
		unsigned short population;

		// The status of the server
		unsigned char status;

		// The ip address of the server
		char ip_address[15];

		// The maximum number of players allowed on the server
		unsigned short max_players;

		// The client version
		unsigned int client_version;

		// The server name
		char server_name[32];
	};


}
#endif