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
		bool handle(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned int length, unsigned short opcode, unsigned char* data) override {

			// If the length is not 5
			if (length != 5)
				return true;

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

				// TODO: Finish ip address string splitting
				bldr->write_byte(192);
				bldr->write_byte(168);
				bldr->write_byte(0);
				bldr->write_byte(5);

			}

			// Unlock the mutex
			Genesis::Auth::AuthServer::get_instance()->get_list_mutex()->unlock();

			// Write the packet
			session->write(bldr->to_packet());

			// Delete the packet builder and server
			delete bldr;
			
			// Return true
			return true;
		}
	};
}
#endif
