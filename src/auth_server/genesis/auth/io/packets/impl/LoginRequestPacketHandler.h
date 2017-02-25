#ifndef GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H
#define GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H

#include <genesis/auth/io/packets/PacketHandler.h>
#include <genesis/common/networking/packets/PacketBuilder.h>

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

			// Write the name
			std::cout << "Name: " << username << std::endl;
			std::cout << "Password: " << password << std::endl;

			// The packet builder instance
			auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

			// Write the response
			bldr->write_byte(0);

			// Write the packet
			session->write(bldr->to_packet());
		}
	};
}
#endif