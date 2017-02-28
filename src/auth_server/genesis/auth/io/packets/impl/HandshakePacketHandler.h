#ifndef GENESIS_AUTH_IO_PACKETS_IMPL_HANDSHAKEPACKETHANDLER_H
#define GENESIS_AUTH_IO_PACKETS_IMPL_HANDSHAKEPACKETHANDLER_H

#include <iostream>
#include <genesis/auth/io/packets/PacketHandler.h>

namespace Genesis::Auth::Io::Packets::Impl {
	class HandshakePacketHandler : public PacketHandler {

		/**
		 * Handles an handshake response
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

			// If the length is not 129
			if (length != 129)
				return;
			
			// NOTE: This is used for setting up the encryption
			// The packet should be decrypted using the private RSA key, and then
			// we can take the AES Key and IV from the packet, and use it for decrypting incoming packets
			//
			// TODO: Finish this
		}
	};
}
#endif