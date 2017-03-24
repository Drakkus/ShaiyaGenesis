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
#ifndef GENESIS_COMMON_NETWORKING_PACKETS_PACKETBUILDER_H
#define GENESIS_COMMON_NETWORKING_PACKETS_PACKETBUILDER_H

#include <vector>
#include "Packet.h"

/**
 * A utility class, used for building packet objects.
 */
namespace Genesis::Common::Networking::Packets {
	class PacketBuilder {

		public:

			// The constructor, which initialises the opcode value
			PacketBuilder(unsigned short opcode) : opcode(opcode) {}

			// Gets the packet builder opcode
			unsigned short get_opcode();

			// Gets the current length of the payload
			unsigned short get_length();

			/**
			 * Writes a single byte to the payload
			 *
			 * @param value
			 *		The value to write
			 *
			 * @returns
			 *		This instance, for method chaining
			 */
			PacketBuilder* write_byte(unsigned char value);

			PacketBuilder* write_bytes(unsigned char* values, unsigned int length);

			/**
			 * Writes a little-endian short to the payload
			 *
			 * @param value
			 *		The value to write
			 *
			 * @returns
			 *		This instance, for method chaining
			 */
			PacketBuilder* write_short_le(unsigned short value);

			PacketBuilder* write_short(unsigned short value);

			/**
			 * Writes a little-endian integer to the payload
			 *
			 * @param value
			 *		The value to write
			 *
			 * @returns
			 *		This instance, for method chaining
			 */
			PacketBuilder* write_int_le(unsigned int value);

			PacketBuilder* write_int(unsigned int value);

			/**
			 * Writes a little endian long integer to the payload
			 *
			 * @param value
			 *		The value to write
			 *
			 * @returns
			 *		This instance, for method chaining
			 */
			PacketBuilder* write_long(unsigned long value);

			/**
			 * Converts this packet builder instance, into a packet opcode
			 *
			 * @return
			 *		The packet
			 */
			Packet* to_packet();

		private:

			// The opcode of the packet
			unsigned short opcode;

			// The payload
			std::vector<unsigned char> payload;
	};
}

#endif