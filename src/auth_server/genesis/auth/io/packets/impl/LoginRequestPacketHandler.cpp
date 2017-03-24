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
#include "LoginRequestPacketHandler.h"

// The packet handler implementation namespace
using namespace Genesis::Auth::Io::Packets::Impl;

/**
 * Handles a server list response, and sends the server list to the user
 *
 * @param session
 *		The session instance
 *
 * @param data
 *		The server list data, returned by the database server
 */
void LoginRequestPacketHandler::handle_server_list(Genesis::Common::Networking::Server::Session::ServerSession* session) {

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::SERVER_LIST_DETAILS);

	// Lock the mutex
	Genesis::Auth::AuthServer::get_instance()->get_list_mutex()->lock();

	// The servers instance
	auto servers = Genesis::Auth::AuthServer::get_instance()->get_servers();

	// The number of servers to choose from
	unsigned char server_count = servers->size();

	// Write the server count
	bldr->write_byte(server_count);

	// Loop through the servers
	for (int i = 0; i < server_count; i++) {

		// The server instance
		auto server = servers->at(i);

		// TODO: Properly find the values that these fields should be
		// or how they should be manipulated

		// Write the server id
		bldr->write_short(server.server_id);

		// Write the server status
		bldr->write_short(server.status);

		// Write the server population
		bldr->write_short(server.population);

		// Write the server name
		bldr->write_bytes((unsigned char*) &server.server_name[0], sizeof(server.server_name));
	}

	// Unlock the mutex
	Genesis::Auth::AuthServer::get_instance()->get_list_mutex()->unlock();

	// Write the packet to the client
	session->write(bldr->to_packet());

	// Delete the packet builder instance
	delete bldr;
}

/**
 * Handles an incoming login request
 *
 * @param session
 *		The session instance
 *
 * @param length
 *		The length of the packet
 *
 * @param opcode
 *		The opcode of the incoming packet
 *
 * @param data
 *		The packet data
 */
bool LoginRequestPacketHandler::handle(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned int length, unsigned short opcode, unsigned char* data) {

	// If the packet is not the correct length
	if (length != 48)
		return true;
			
	// The username and password
	unsigned char username[19];
	unsigned char password[32];
	char hashed_password[33];

	// Copy the username and password
	std::copy(data, data + 19, username);
	std::copy(data + 32, data + length, password);
			
	// The MD5 digest
	std::string digest = md5((char*) password);

    // Copy the digest
	digest.copy(hashed_password, digest.length() + 1);

	// Define null terminators
	username[sizeof(username) - 1] = '\0';
	hashed_password[sizeof(hashed_password) - 1] = '\0';

	// The client instance
	auto db_client = AuthServer::get_instance()->get_db_client();

	// The auth request stucture
	Genesis::Common::Database::Structs::Auth::AuthRequest auth_request;

	// The session ip address
	auto ip_address = session->get_remote_address().c_str();

	// Define the details
	std::copy(username, username + sizeof(username), auth_request.username);
	std::copy(hashed_password, hashed_password + sizeof(hashed_password), auth_request.password);
	std::copy(ip_address, ip_address + sizeof(auth_request.ip_address), auth_request.ip_address);

	// The byte array
	unsigned char struct_array[sizeof(auth_request)];
	memcpy(struct_array, &auth_request, sizeof(auth_request));

	// The packet builder instance
	auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::USER_AUTH_REQUEST);

	// Write the struct array
	bldr->write_bytes(struct_array, sizeof(struct_array));

	// The class instance
	auto current = this;

	// Write the packet
	db_client->write(bldr->to_packet(), [session, current](unsigned char* data, unsigned int length) {
				
		// The auth response stucture
		Genesis::Common::Database::Structs::Auth::AuthResponse auth_response;

		// Copy the data
		memcpy(&auth_response, data, sizeof(auth_response));

		// Write the response from the database server, to the client
		auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Packets::Opcodes::LOGIN_REQUEST);

		// The status
		int status = auth_response.status;

		// Write the status
		bldr->write_byte(status);

		// If the status is 0
		if (status == 0) {

			// Write the user id
			bldr->write_int(auth_response.user_id);

			// Write the privilege level
			bldr->write_byte(auth_response.privilege_level);

			// Write the identity keys
			bldr->write_bytes(auth_response.identity_keys, sizeof(auth_response.identity_keys));

			// Set the identity keys for the session
			session->set_identity_keys(auth_response.identity_keys);
			
			// Handle the server list processing
			current->handle_server_list(session);
		}

		// Write the packet
		session->write(bldr->to_packet());

		// Delete the packet builder
		delete bldr;
	});

	// Delete the packet builder
	delete bldr;

	// Return true
	return true;
}