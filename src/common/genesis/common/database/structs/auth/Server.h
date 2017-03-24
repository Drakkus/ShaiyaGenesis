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