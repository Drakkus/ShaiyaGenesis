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
#include <genesis/game/io/IoServer.h>

#include <genesis/common/networking/server/GenesisServer.h>
#include <genesis/common/networking/server/session/ServerSession.h>
#include <genesis/common/networking/packets/PacketBuilder.h>
#include <genesis/common/packets/Opcodes.h>
#include <iostream>
#include <functional>
#include <iomanip>

// An alias for the name space
using namespace Genesis::Game::Io;

/**
 * Initialise the IoServer instance, and listen on a specified address and port.
 *
 * @param address
 *		The local address to listen on
 *
 * @param port
 *		The port to listen on
 *
 * @returns
 *		If the server was successfully initialised
 */
bool IoServer::initialise(unsigned short port) {
	
	// The io service to operate on
	boost::asio::io_service io_service;

	// The GenesisServer instance
	auto server = new Genesis::Common::Networking::Server::GenesisServer(io_service, port);

	// Define the network events
	server->on_connect(std::bind(&IoServer::on_connect, this, std::placeholders::_1));
	server->on_receive(std::bind(&IoServer::on_receive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	server->on_send(std::bind(&IoServer::on_send, this, std::placeholders::_1));
	server->on_terminate(std::bind(&IoServer::on_terminate, this, std::placeholders::_1));

	// Return if the server managed to successfully bind to a port specified
	return server->bind(port);
}

/**
 * Called whenever an on_connect event is received by the server.
 *
 * @param session
 *		The session instance
 */
void IoServer::on_connect(Genesis::Common::Networking::Server::Session::ServerSession* session) {

}

/**
 * Called whenever an on_receive event is received by the server, which signifies
 * an incoming packet from an existing connection.
 */
bool IoServer::on_receive(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned char* data, unsigned int bytes_read) {

	// The packet length
	unsigned short packet_length = ((data[0] & 0xFF) + ((data[1] & 0xFF) << 8));

	// The packet opcode
	unsigned short packet_opcode = ((data[2] & 0xFF) + ((data[3] & 0xFF) << 8));

	// The packet data
	unsigned char* packet_data = (data + 4);

	// The packet handler
	auto handler = this->packet_manager->get_handler(packet_opcode);

	// Handle the incoming packet
	return handler->handle(session, packet_length - 4, packet_opcode, packet_data);
}

/**
 * Called whenever an on_send event is received by the server, which signifies
 * an outgoing packet from an existing connection.
 */
void IoServer::on_send(char* name) {
	std::cout << "sending, " << name << std::endl;
}

/**
 * Called whenever an on_terminate event is received by the server, which signifies
 * an existing connection that has had it's connection terminated.
 */
void IoServer::on_terminate(Genesis::Common::Networking::Server::Session::ServerSession* session) {
	std::cout << "session termination called" << std::endl;
}