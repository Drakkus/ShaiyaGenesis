#ifndef GENESIS_DATABASE_IO_PACKETS_PACKETHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_PACKETHANDLER_H

#include <genesis/common/networking/server/session/ServerSession.h>

/**
 * An abstract interface, used for handling incoming packets
 */
namespace Genesis::Database::Io::Packets {

	class PacketHandler {

		public:

			/**
			 * Handles an incoming packet
			 *
			 * @param session
			 *		The session instance
			 *
			 * @param length
			 *		The length of the packet
			 *
			 * @param opcode
			 *		The opcode of the packet
			 *
			 * @param data
			 *		The packet data
			 */
			virtual void handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned int request_id, unsigned char* data) = 0;
	};
}
#endif