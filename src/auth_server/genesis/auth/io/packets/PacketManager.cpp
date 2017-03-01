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
	this->handlers[Opcodes::LOGIN_TERMINATE] = new Genesis::Auth::Io::Packets::Impl::ConnectionTerminatedPacketHandler();
	this->handlers[Opcodes::LOGIN_HANDSHAKE] = new Genesis::Auth::Io::Packets::Impl::HandshakePacketHandler();
	this->handlers[Opcodes::LOGIN_REQUEST] = new Genesis::Auth::Io::Packets::Impl::LoginRequestPacketHandler();
	this->handlers[Opcodes::SELECT_GAME_SERVER] = new Genesis::Auth::Io::Packets::Impl::ServerSelectPacketHandler();
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