#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_DEFAULTPACKETHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_DEFAULTPACKETHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
#include <iostream>
#include <iomanip>

namespace Genesis::Database::Io::Packets::Impl {
	class DefaultPacketHandler : public PacketHandler {

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

			// The current state of the standard output
			std::ios old_state(nullptr);
			old_state.copyfmt(std::cout);

			// Inform the user that an undefined packet is received
			std::cout << "[Unhandled packet, Opcode: " << opcode << ", Length: " << length << ", Data: ";

			// Write the packet data, in hex form
			for (int i = 0; i < length; i++) {
				std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)data[i] << " ";
			}

			// End the information message
			std::cout << "]" << std::endl;

			// Restore the standard output state
			std::cout.copyfmt(old_state);
		}
	};
}
#endif