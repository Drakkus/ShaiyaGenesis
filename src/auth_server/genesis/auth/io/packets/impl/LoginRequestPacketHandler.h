#ifndef GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H
#define GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H

#include <genesis/auth/io/packets/PacketHandler.h>
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/auth/AuthServer.h>
#include <genesis/common/networking/client/GenesisClient.h>

#include <genesis/common/database/structs/auth/AuthRequest.h>
#include <genesis/common/database/structs/auth/AuthResponse.h>
#include <genesis/common/database/structs/auth/Server.h>

#include <genesis/common/database/Opcodes.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <thread>

#include <genesis/common/cryptography/MD5.h>
#include <genesis/common/packets/Opcodes.h>

namespace Genesis::Auth::Io::Packets::Impl {
	class LoginRequestPacketHandler : public PacketHandler {

		/**
		 * Handles a server list response, and sends the server list to the user
		 *
		 * @param session
		 *		The session instance
		 *
		 * @param data
		 *		The server list data, returned by the database server
		 */
		void handle_server_list(Genesis::Common::Networking::Server::Session::ServerSession* session) {

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

				// Write the server id
				bldr->write_short(server.server_id);

				// Write the server status
				bldr->write_short(server.status);

				// Write the server population
				bldr->write_short(server.population);

				// Write the server name
				for (int i = 0; i < sizeof(server.server_name); i++) {
					bldr->write_byte(server.server_name[i]);
				}
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
		void handle(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned int length, unsigned short opcode, unsigned char* data) override {

			// If the packet is not the correct length
			if (length != 48)
				return;
			
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
			username[18] = '\0';
			hashed_password[32] = '\0';

			// The client instance
			auto db_client = AuthServer::get_instance()->get_db_client();

			// The auth request stucture
			Genesis::Common::Database::Structs::Auth::AuthRequest auth_request;

			// The session ip address
			auto ip_address = session->get_remote_address().c_str();

			// Define the details
			std::copy(username, username + 19, auth_request.username);
			std::copy(hashed_password, hashed_password + 32, auth_request.password);
			std::copy(ip_address, ip_address + 15, auth_request.ip_address);

			// The byte array
			unsigned char struct_array[sizeof(auth_request)];
			memcpy(struct_array, &auth_request, sizeof(auth_request));

			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(Genesis::Common::Database::Opcodes::USER_AUTH_REQUEST);

			// Write the struct array
			bldr->write_bytes(struct_array, sizeof(struct_array));

			// Write the packet
			db_client->write(bldr->to_packet(), [&](unsigned char* data, unsigned int length) {
				
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

					// Handle the server list processing
					handle_server_list(session);
				}

				// Write the packet
				session->write(bldr->to_packet());

				// Delete the packet builder
				delete bldr;
			});

			// Delete the pointers
			delete bldr;
		}
	};
}
#endif