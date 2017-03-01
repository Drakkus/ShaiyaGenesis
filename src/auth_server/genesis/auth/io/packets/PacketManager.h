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
#ifndef GENESIS_AUTH_IO_PACKETS_PACKETMANAGER_H
#define GENESIS_AUTH_IO_PACKETS_PACKETMANAGER_H

#include <map>

// Forward declaration of the PacketHandler class
namespace Genesis::Auth::Io::Packets { class PacketHandler; }

/**
 * The PacketManager class, which assigns the packet handler for each opcode.
 * This is referenced as a singleton, and is used to call the approprite handler instances
 */
namespace Genesis::Auth::Io::Packets {
	class PacketManager {

		public:

			// The constructor, which initialises the handler instances
			PacketManager();

			/**
			 * Retrieves the PacketHandler for a specific opcode
			 *
			 * @param opcode
			 *		The opcode
			 *
			 * @returns
			 *		The packet handler
			 */
			Genesis::Auth::Io::Packets::PacketHandler* get_handler(unsigned short opcode);
			
		private:

			// The map of opcodes to packet handlers
			std::map<unsigned short, Genesis::Auth::Io::Packets::PacketHandler*> handlers;
	};
}
#endif