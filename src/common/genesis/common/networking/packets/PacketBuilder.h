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
			unsigned short get_opcode() { return this->opcode; }

			// Gets the current length of the payload
			unsigned short get_length() { return this->payload.size(); }

			/**
			 * Writes a single byte to the payload
			 *
			 * @param value
			 *		The value to write
			 *
			 * @returns
			 *		This instance, for method chaining
			 */
			PacketBuilder* write_byte(uint8_t value) {
				payload.push_back(value);
				return this;
			}

			PacketBuilder* write_bytes(uint8_t* values, unsigned int length) {
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
			PacketBuilder* write_short(unsigned short value) {
				write_byte((uint8_t) value >> 8);
				write_byte((uint8_t) value);
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
			PacketBuilder* write_int(unsigned int value) {
				write_byte((uint8_t) value & 0xFF);
				write_byte((uint8_t) (value >> 8) & 0xFF);
				write_byte((uint8_t) (value >> 16) & 0xFF);
				write_byte((uint8_t) (value >> 24) & 0xFF);
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
			PacketBuilder* write_long(unsigned long value) {
				write_byte((uint8_t) value >> 56);
				write_byte((uint8_t) value >> 48);
				write_byte((uint8_t) value >> 40);
				write_byte((uint8_t) value >> 32);
				write_byte((uint8_t) value >> 24);
				write_byte((uint8_t) value >> 16);
				write_byte((uint8_t) value >> 8);
				write_byte((uint8_t) value);
				return this;
			}

			/**
			 * Converts this packet builder instance, into a packet opcode
			 *
			 * @return
			 *		The packet
			 */
			Packet* to_packet() {

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

		private:

			// The opcode of the packet
			unsigned short opcode;

			// The payload
			std::vector<uint8_t> payload;
	};
}

#endif