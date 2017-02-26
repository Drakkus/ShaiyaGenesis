#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_USERAUTHREQUESTHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_USERAUTHREQUESTHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/database/structs/auth/AuthRequest.h>
#include <iostream>

namespace Genesis::Database::Io::Packets::Impl {
	class UserAuthRequestHandler : public PacketHandler {

		/**
		 * Handles an undefined packet
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
		void handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned int request_id, unsigned char* data) override {

			// The auth request instance
			Genesis::Common::Database::Structs::Auth::AuthRequest request;

			// Copy the data
			memcpy(&request, data, sizeof(request));

			std::cout << "Received auth request. Name: " << request.username << ", Password: " << request.password << std::endl;
			
			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

			// Write the request id
			bldr->write_int(request_id);

			// Write a byte
			bldr->write_byte(3);

			// Write the packet
			session->write(bldr->to_packet());

			// Delete the packet builder
			delete bldr;
		}
	};
}
#endif