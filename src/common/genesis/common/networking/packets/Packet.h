#ifndef GENESIS_COMMON_NETWORKING_PACKETS_PACKET_H
#define GENESIS_COMMON_NETWORKING_PACKETS_PACKET_H

/**
 * Represents a packet structure, which is an incoming or outgoing message.
 */
namespace Genesis::Common::Networking::Packets {
	struct Packet {

		// The packet length
		unsigned short length;

		// The opcode
		unsigned short opcode;

		// The payload of the packet
		std::vector<uint8_t> payload;
	};
}
#endif