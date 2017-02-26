#ifndef GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H
#define GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H

#include <genesis/auth/io/packets/PacketHandler.h>
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/auth/AuthServer.h>
#include <genesis/common/networking/client/GenesisClient.h>
#include <genesis/common/database/structs/auth/AuthRequest.h>
#include <iostream>
#include <iomanip>

namespace Genesis::Auth::Io::Packets::Impl {
	class LoginRequestPacketHandler : public PacketHandler {

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

			// The username and password
			char* username = new char;
			char* password = new char;

			// Copy the username and password
			std::copy(data, data + 32, username);
			std::copy(data + 32, data + length, password);

			// The client instance
			auto db_client = AuthServer::get_instance()->get_db_client();

			// The auth request stucture
			Genesis::Common::Database::Structs::Auth::AuthRequest auth_request;

			// The session ip address
			auto ip_address = session->get_remote_address().c_str();

			// Define the details
			std::copy(username, username + 32, auth_request.username);
			std::copy(password, password + 32, auth_request.password);
			std::copy(ip_address, ip_address + 15, auth_request.ip_address);

			// The byte array
			unsigned char struct_array[sizeof(auth_request)];
			memcpy(struct_array, &auth_request, sizeof(auth_request));

			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(1);

			// Write the struct array
			bldr->write_bytes(struct_array, sizeof(struct_array));

			// Write the packet
			db_client->write(bldr->to_packet(), [&](unsigned char* data, unsigned int length) {
				
				std::cout << "Callback: Val " << (unsigned int) data[0] << std::endl;
				
				// Write the response from the database server, to the client
				auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

				// Write the byte
				bldr->write_byte(data[0]);

				// Write the packet
				session->write(bldr->to_packet());

				// Delete the packet builder
				delete bldr;
			});

			// Delete the packet builder
			delete bldr;
		}
	};
}
#endif