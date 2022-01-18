//
// Created by thomas on 11/11/2021.
//

#pragma once
#include "TcpServer.hpp"

namespace NetworkServer {
    class ManagerTcpServer {
    public:
        ManagerTcpServer();
        void Stop();
        void Init();
        std::shared_ptr<NetworkServer::TcpServer> CreateTcpServer(Network::PairQueue<Network::Digit, unsigned char *>&);
        //std::shared_ptr<NetworkServer::TcpConnection> CreateTcpConnection();
//        std::vector<std::unique_ptr<IUdpClient>> _udpCli;

    private:
       // std::vector<std::shared_ptr<TcpServer>> _tcpCli;
        /* Multi threading variables */
        std::shared_ptr<boost::asio::io_context::work> _worker;
        boost::asio::io_context _ioContext;
        std::thread _threadContext;
    };
}