#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_USERAUTHREQUESTHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_USERAUTHREQUESTHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
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
		void handle(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned int length, unsigned short opcode, unsigned char* data) override {

			// The auth request instance
			Genesis::Common::Database::Structs::Auth::AuthRequest request;

			// Copy the data
			memcpy(&request, data, sizeof(request));

			// Write the details
			std::cout << "Username: " << request.username << ", Password: " << request.password << ", Ip: " << request.ip_address << std::endl;
		}
	};
}
#endif