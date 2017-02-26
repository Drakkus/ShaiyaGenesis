#ifndef GENESIS_COMMON_NETWORKING_CLIENT_GENESISCLIENT_H
#define GENESIS_COMMON_NETWORKING_CLIENT_GENESISCLIENT_H

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define MAX_PACKET_LENGTH 1024

namespace Genesis::Common::Networking::Client {

	class GenesisClient {

		public:

			GenesisClient(boost::asio::io_service &io_service) : io_service(io_service), socket(io_service) {}

			bool connect(std::string address, unsigned short port);

			void handle_read(unsigned char* data, const boost::system::error_code &error, unsigned int bytes_read);

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

			// The on_receive lambda function, which is called whenever a new packet is received
			std::function<void(unsigned char*, unsigned int)> receive_function;

			// The boost io_service instance
			boost::asio::io_service &io_service;

			// The socket instance
			boost::asio::ip::tcp::socket socket;

			// The array that the client will receive data to
			unsigned char data[1024];
	};
}
#endif