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
#ifndef GENESIS_COMMON_NETWORKING_CLIENT_GENESISCLIENT_H
#define GENESIS_COMMON_NETWORKING_CLIENT_GENESISCLIENT_H

#include <string>
#include <iostream>
#include <mutex>
#include <queue>

#include "../packets/Packet.h"
#include "../packets/PacketBuilder.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define MAX_PACKET_LENGTH 4096

namespace Genesis::Common::Networking::Client {

	class GenesisClient {

		public:

			GenesisClient(boost::asio::io_service &io_service) 
				: io_service(io_service), socket(io_service) {}

			bool connect(std::string address, unsigned short port);

			void handle_read(unsigned char* data, const boost::system::error_code &error, unsigned int bytes_read);

			void process_callbacks();

			/**
			 * Writes a packet to this session's socket
			 *
			 * @param packet
			 *		The packet instance to write
			 */
			void write(Genesis::Common::Networking::Packets::Packet* packet) {

				// The length of the packet
				unsigned int length = packet->length + 4;

				// The array to write to
				unsigned char* data = new unsigned char[length];

				// The request id
				unsigned int request_id = (unsigned int) rand();

				// Write the length
				data[0] = (length);
				data[1] = (length >> 8);

				// Write the opcode
				data[2] = (packet->opcode);
				data[3] = (packet->opcode >> 8);

				// Write the request id
				data[4] = (request_id);
				data[5] = (request_id >> 8);
				data[6] = (request_id >> 16);
				data[7] = (request_id >> 24);

				// Write the data
				for (int i = 0; i < packet->payload.size(); i++) {
					data[8 + i] = packet->payload.at(i);
				}

				// Write the data
				boost::asio::async_write(this->socket, boost::asio::buffer(data, length),
					[&](const boost::system::error_code& error, unsigned int bytes_written) {

						// If an error occurred, close the socket if it is still open
						if (error && this->socket.is_open()) {
							this->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
							this->socket.close();
						}
				});
	
				// Delete the data array and packet
				delete[] data;
				delete packet;
			}

			/**
			 * Writes a packet to this session's socket
			 *
			 * @param packet
			 *		The packet instance to write
			 *
			 * @param callback
			 *		The callback to execute
			 */
			void write(Genesis::Common::Networking::Packets::Packet* packet, std::function<void(unsigned char*, unsigned int)> callback) {

				// The length of the packet
				unsigned int length = packet->length + 4;

				// The array to write to
				unsigned char* data = new unsigned char[length];

				// The request id
				unsigned int request_id = (unsigned int) rand();

				// Lock the mutex
				this->mutex.lock();

				// Generate a unique request id
				while (this->request_map.count(request_id) != 0)
					request_id = (unsigned int) rand();

				// Store the request
				this->request_map[request_id] = callback;

				// Unlock the mutex
				this->mutex.unlock();

				// Write the length
				data[0] = (length);
				data[1] = (length >> 8);

				// Write the opcode
				data[2] = (packet->opcode);
				data[3] = (packet->opcode >> 8);

				// Write the request id
				data[4] = (request_id);
				data[5] = (request_id >> 8);
				data[6] = (request_id >> 16);
				data[7] = (request_id >> 24);

				// Write the data
				for (int i = 0; i < packet->payload.size(); i++) {
					data[8 + i] = packet->payload.at(i);
				}

				// Write the data
				boost::asio::async_write(this->socket, boost::asio::buffer(data, length),
					[&](const boost::system::error_code& error, unsigned int bytes_written) {

						// If an error occurred, close the socket if it is still open
						if (error && this->socket.is_open()) {
							this->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
							this->socket.close();
						}
				});
	
				// Delete the data array and packet
				delete[] data;
				delete packet;
			}
			
			/**
			 * Defines the function to be called whenever a new packet is received
			 *
			 * @param receive_function
			 *		The function to call
			 */
			void on_receive(std::function<void(unsigned char*, unsigned int)> receive_function) {
				this->receive_function = receive_function;
			}

		private:

			// The queue of pending callbacks
			std::queue<std::function<void()>> callback_queue;

			// The mutex
			std::mutex mutex;

			// The callback queue mutex
			std::mutex callback_queue_mutex;

			// A map containing the request ids, and their callbacks
			std::map<unsigned int, std::function<void(unsigned char*, unsigned int)>> request_map;

			// The on_receive lambda function, which is called whenever a new packet is received
			std::function<void(unsigned char*, unsigned int)> receive_function;

			// The boost io_service instance
			boost::asio::io_service &io_service;

			// The socket instance
			boost::asio::ip::tcp::socket socket;

			// The array that the client will receive data to
			unsigned char data[4096];
	};
}
#endif