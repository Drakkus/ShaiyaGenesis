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
		bool handle(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned int length, unsigned short opcode, unsigned char* data) override {

			// If the length is not 129
			if (length != 129)
				return true;
			
			// NOTE: This is used for setting up the encryption
			// The packet should be decrypted using the private RSA key, and then
			// we can take the AES Key and IV from the packet, and use it for decrypting incoming packets
			//
			// TODO: Finish this
			return true;
		}
	};
}
#endif