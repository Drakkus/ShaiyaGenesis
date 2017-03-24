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
		bool handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
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

			// Return true
			return true;
		}
	};
}
#endif