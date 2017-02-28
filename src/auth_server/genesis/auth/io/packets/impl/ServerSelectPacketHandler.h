#ifndef GENESIS_AUTH_IO_PACKETS_IMPL_SERVERSELECTPACKETHANDLER_H
#define GENESIS_AUTH_IO_PACKETS_IMPL_SERVERSELECTPACKETHANDLER_H

#include <genesis/auth/io/packets/PacketHandler.h>
#include <genesis/auth/AuthServer.h>

#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/networking/client/GenesisClient.h>
#include <genesis/common/database/structs/auth/Server.h>
#include <genesis/common/database/Opcodes.h>
#include <genesis/common/packets/Opcodes.h>

#include <string>

namespace Genesis::Auth::Io::Packets::Impl {
	class ServerSelectPacketHandler : public PacketHandler {


		/**
		 * Handles an incoming game server selection
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

			// If the length is not 5
			if (length != 5)
				return;

			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

			// The server id
			unsigned char server_id = (data[0] & 0xFF);

			// The client version
			unsigned int client_version = ((data[1] & 0xFF) + ((data[2] & 0xFF) << 8) + ((data[3] & 0xFF) << 16) + ((data[4] & 0xFF) << 24));

			// Lock the mutex
			Genesis::Auth::AuthServer::get_instance()->get_list_mutex()->lock();

			// The servers instance
			auto servers = Genesis::Auth::AuthServer::get_instance()->get_servers();

			// If the server has been found
			bool found = false;

			// The server instance
			Genesis::Common::Database::Structs::Auth::Server* found_server;

			// Loop through the servers
			for (auto server : *servers) {

				// If the server id matches
				if (server.server_id == server_id) {
					found = true;
					found_server = &server;
					break;
				}
			}

			// Write the status, or server id
			bldr->write_byte(client_version == found_server->client_version && found_server->status == 0 ? server_id : -2);

			// If the client version matches
			if (client_version == found_server->client_version) {

				// The ip address string
				std::string ip_address(found_server->ip_address);

				// The string delimiter
				std::string delimiter = ".";

				// The current position
				size_t pos = 0;

				// The current token
				std::string token;

				// Parse the ip address string
				while ((pos = ip_address.find(delimiter)) != std::string::npos) {

					// The token
    				token = ip_address.substr(0, pos);
    				
    				// Write the token as a byte
    				bldr->write_byte(std::stoi(token));

    				// Remove the token from the string
    				ip_address.erase(0, pos + delimiter.length());
				}
			}

			// Unlock the mutex
			Genesis::Auth::AuthServer::get_instance()->get_list_mutex()->unlock();

			// Write the packet
			session->write(bldr->to_packet());

			// Delete the packet builder and server
			delete bldr;
		}
	};
}
#endif