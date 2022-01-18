#pragma once

#include "History.hpp"
#include "SafeQueue.hpp"
#include "IClient.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <array>
#include <thread>


using boost::asio::ip::udp;
static const std::size_t NetworkBufferSizeUdp = 4096;

namespace NetworkClient::Udp {
	class UdpClient : public NetworkClient::IClient {
	public:
		/**
		 * @brief Construct a new Udp Client object
		 *
		 * @param server_port port of the serveur to connect
		 * @param udpSafeQueue use to keep trace of message receive
		 */
		UdpClient(unsigned short server_port, Network::LockedQueue<unsigned char *> &udpSafeQueue, std::string &);
		/**
		 * @brief Destroy the Udp Client object
		 *
		 */
		virtual ~UdpClient();
		/**
		 * @brief send a message to the serveur
		 *
		 * @param paquet message pack to bee lighter
		 */
		void Send(Network::Protocol::Packet &) override;
		/**
		 * @brief Send message to last endpoint (serveur)
		 *
		 * @param serverEndpointArg
		 */
		void SendToEndPt(Network::Protocol::Packet &, const udp::endpoint& serverEndpointArg);
		/**
		 * @brief stop all activities from client
		 *
		 */
        void Stop();
		/**
		 * @brief Set the Endpoint object
		 *
		 */
        void SetEndpoint(std::string &);
		/**
		 * @brief is the queue got message
		 *
		 * @return true
		 * @return false
		 */
		bool HasMessages() override;
		/**
		 * @brief pop message from the queue to handle them
		 *
		 * @return unsigned char*
		 */
		unsigned char *PopMessage() override;
		bool _isStopped;

		boost::asio::io_service io_service;//private
		udp::endpoint server_endpoint;//private
    private:

		// UdpClient send/receive stuff

        Network::LockedQueue<unsigned char *> &_udpSafeQueue;//private
		udp::socket socket;
		std::thread service_thread;
		boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _work {io_service.get_executor()};
		unsigned char _buff[Network::BuffSize]{};

		// Queues for messages
		//Network::LockedQueue<unsigned char *> &_udpSafeQueue;
		/**
		 * @brief start receive from the serveur (run callback)
		 *
		 */
		void start_receive();
		/**
		 * @brief callback from the receiver
		 *
		 * @param error error possibly happening
		 * @param bytes_transferred size of the msg
		 */
		void handle_receive(const std::error_code& error, [[maybe_unused]]std::size_t bytes_transferred);
		/**
		 * @brief run io_context, make sure to keep him busy
		 *
		 */
		void RunService();
        std::string _remoteEndpoint;
		/**
		 * @brief Construct a new Udp Client object
		 *
		 */
		UdpClient(UdpClient&); // block default copy constructor

		// Statistics
		Network::Historys history;
	};
}
