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
#include "PacketBuilder.h"

// Use the packet namespace
using namespace Genesis::Common::Networking::Packets;

/**
 * Gets the opcode for this {@code PacketBuilder}
 *
 * @returns
 *		The opcode
 */
unsigned short PacketBuilder::get_opcode() { 
	return this->opcode;
}

/**
 * Gets te length of the packet builder
 *
 * @returns
 *		The current length
 */
unsigned short PacketBuilder::get_length() { 
	return this->payload.size();
}

/**
 * Writes a single byte to the payload
 *
 * @param value
 *		The value to write
 *
 * @returns
 *		This instance, for method chaining
 */
PacketBuilder* PacketBuilder::write_byte(unsigned char value) {
	payload.push_back(value);
	return this;
}

PacketBuilder* PacketBuilder::write_bytes(unsigned char* values, unsigned int length) {
	for (int i = 0; i < length; i++) {
		this->write_byte(values[i]);
	}
	return this;
}

/**
 * Writes a little-endian short to the payload
 *
 * @param value
 *		The value to write
 *
 * @returns
 *		This instance, for method chaining
 */
PacketBuilder* PacketBuilder::write_short_le(unsigned short value) {
	write_byte((unsigned char) (value >> 8) & 0xFF);
	write_byte((unsigned char) value);
	return this;
}

PacketBuilder* PacketBuilder::write_short(unsigned short value) {
	write_byte((unsigned char) value);
	write_byte((unsigned char) (value >> 8) & 0xFF);
	return this;
}

/**
 * Writes a little-endian integer to the payload
 *
 * @param value
 *		The value to write
 *
 * @returns
 *		This instance, for method chaining
 */
PacketBuilder* PacketBuilder::write_int_le(unsigned int value) {
	write_byte((unsigned char) (value >> 24) & 0xFF);
	write_byte((unsigned char) (value >> 16) & 0xFF);
	write_byte((unsigned char) (value >> 8) & 0xFF);
	write_byte((unsigned char) value & 0xFF);
	return this;
}

PacketBuilder* PacketBuilder::write_int(unsigned int value) {
	write_byte((unsigned char) value & 0xFF);
	write_byte((unsigned char) (value >> 8) & 0xFF);
	write_byte((unsigned char) (value >> 16) & 0xFF);
	write_byte((unsigned char) (value >> 24) & 0xFF);
	return this;
}

/**
 * Writes a little endian long integer to the payload
 *
 * @param value
 *		The value to write
 *
 * @returns
 *		This instance, for method chaining
 */
PacketBuilder* PacketBuilder::write_long(unsigned long value) {
	write_byte((unsigned char) (value >> 56) & 0xFF);
	write_byte((unsigned char) (value >> 48) & 0xFF);
	write_byte((unsigned char) (value >> 40) & 0xFF);
	write_byte((unsigned char) (value >> 32) & 0xFF);
	write_byte((unsigned char) (value >> 24) & 0xFF);
	write_byte((unsigned char) (value >> 16) & 0xFF);
	write_byte((unsigned char) (value >> 8) & 0xFF);
	write_byte((unsigned char) value & 0xFF);
	return this;
}

/**
 * Converts this packet builder instance, into a packet opcode
 *
 * @return
 *		The packet
 */
Packet* PacketBuilder::to_packet() {

	// The packet instance
	Packet* packet = new Packet;

	// Define the opcode
	packet->opcode = this->opcode;

	// Define the packet length
	packet->length = this->get_length() + 4;

	// Define the payload
	packet->payload = this->payload;

	// Return the packet instance
	return packet;
}