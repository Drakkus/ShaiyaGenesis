#ifndef GENESIS_COMMON_NETWORKING_CLIENT_GENESISCLIENT_H
#define GENESIS_COMMON_NETWORKING_CLIENT_GENESISCLIENT_H

#include <string>
#include <boost/asio.hpp>

namespace Genesis::Common::Networking::Client {

	class GenesisClient {

		public:
			GenesisClient(boost::asio::io_service &io_service) : io_service(io_service), socket(io_service) {}

			bool connect(std::string address, unsigned short port);

		private:

			// The boost io_service instance
			boost::asio::io_service &io_service;

			// The socket instance
			boost::asio::ip::tcp::socket socket;
	};
}
#endif