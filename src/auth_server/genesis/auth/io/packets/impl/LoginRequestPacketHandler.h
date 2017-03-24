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
#ifndef GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H
#define GENESIS_AUTH_IO_PACKETS_IMPL_LOGINREQUESTPACKETHANDLER_H

#include <genesis/auth/io/packets/PacketHandler.h>
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/auth/AuthServer.h>
#include <genesis/common/networking/client/GenesisClient.h>

#include <genesis/common/database/structs/auth/AuthRequest.h>
#include <genesis/common/database/structs/auth/AuthResponse.h>
#include <genesis/common/database/structs/auth/Server.h>

#include <genesis/common/database/Opcodes.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <thread>

#include <genesis/common/cryptography/MD5.h>
#include <genesis/common/packets/Opcodes.h>

namespace Genesis::Auth::Io::Packets::Impl {
	class LoginRequestPacketHandler : public PacketHandler {

		/**
		 * Handles a server list response, and sends the server list to the user
		 *
		 * @param session
		 *		The session instance
		 *
		 * @param data
		 *		The server list data, returned by the database server
		 */
		void handle_server_list(Genesis::Common::Networking::Server::Session::ServerSession* session);

		/**
		 * Handles an incoming login request
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
		bool handle(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned int length, unsigned short opcode, unsigned char* data);
	};
}
#endif