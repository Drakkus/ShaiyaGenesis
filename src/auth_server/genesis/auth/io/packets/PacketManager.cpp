#include <genesis/auth/io/packets/PacketManager.h>
#include <genesis/auth/io/packets/PacketHandler.h>
#include <genesis/auth/io/packets/impl/Handlers.h>
#include <genesis/common/packets/Opcodes.h>

// The opcodes namespace
namespace Opcodes = Genesis::Common::Packets::Opcodes;

/**
 * The {@code PacketManager} constructor, which is used to pre-define the packet handlers
 * for the opcodes used by the Shaiya Genesis authentication server.
 */
Genesis::Auth::Io::Packets::PacketManager::PacketManager() {

	// The default packet handler
	this->handlers[0] = new Genesis::Auth::Io::Packets::Impl::DefaultPacketHandler();

	// Define the packet handlers
	this->handlers[Opcodes::LOGIN_HANDSHAKE] = new Genesis::Auth::Io::Packets::Impl::HandshakePacketHandler();
	this->handlers[Opcodes::LOGIN_REQUEST] = new Genesis::Auth::Io::Packets::Impl::LoginRequestPacketHandler();
}

/**
 * Gets the handler assigned to a specific opcode
 *
 * @param opcode
 * 		The opcode
 *
 * @returns
 *		The handler if found. If not, the {@link DefaultPacketHandler} instance is returned
 */
Genesis::Auth::Io::Packets::PacketHandler* Genesis::Auth::Io::Packets::PacketManager::get_handler(unsigned short opcode) {

	// The number of key instances for the opcode
	int count = this->handlers.count(opcode);

	// Return the handler
	return (count >= 1 ? this->handlers[opcode] : this->handlers[0]);
}