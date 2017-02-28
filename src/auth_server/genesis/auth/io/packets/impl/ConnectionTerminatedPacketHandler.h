#ifndef GENESIS_AUTH_IO_PACKETS_IMPL_CONNECTIONTERMINATEDPACKETHANDLER_H
#define GENESIS_AUTH_IO_PACKETS_IMPL_CONNECTIONTERMINATEDPACKETHANDLER_H

#include <genesis/auth/io/packets/PacketHandler.h>
#include <iostream>

namespace Genesis::Auth::Io::Packets::Impl {
	class ConnectionTerminatedPacketHandler : public PacketHandler {

		/**
		 * Handles a terminated connection packet
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
				unsigned int length, unsigned short opcode, unsigned char* data) override {

			std::cout << "Connection terminated from: " << session->get_remote_address() << std::endl;
		}
	};
}
#endif