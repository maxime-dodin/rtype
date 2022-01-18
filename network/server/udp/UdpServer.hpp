//
// Created by thomas on 08/11/2021.
//
#pragma once
#include "PortManager.hpp"
#include <unordered_map>
#include "EcsServer.hpp"

namespace NetworkServer {
    class UdpServer {
    public:
        UdpServer();
        ~UdpServer();
        // PUBLIC GETTER
        Network::UdpSessionMode GetUdpSessionMode(uint32_t) const;

        // PUBLIC SETTER
        void SetUdpSessionMode(uint32_t, Network::UdpSessionMode);

        // PUBLIC UDP SESSION API
        std::vector<Network::Digit> &GetAllClientId(Network::Digit);
        uint32_t CreateUdpSession(Network::Digit);
        void RemoveUdpSession(uint32_t);
        Network::UdpSessionRole AddClientToUdpSession(uint32_t client, uint32_t session);
        void RemoveClientFromUdpSession(uint32_t client, uint32_t session);
        bool IsUdpSessionFull(uint32_t);
        bool IsUdpSessionEmpty(uint32_t);
        Network::Digit GetUdpSessionPort(uint32_t);
        void SetUdpSessionClientReadyState(uint32_t, uint32_t, bool);
        bool IsUdpSessionReadyToPlay(uint32_t);
        void InitUdpSession(uint32_t);
        std::size_t InitUdpSessionPlayerUuid(uint32_t);
        void SetUdpSessionSpaceshipUuid(uint32_t, uint32_t, std::size_t);
        std::size_t GetUdpSessionSpaceshipUuid(uint32_t, uint32_t) const;
        Network::Digit GetUdpSessionMaxPlayer(uint32_t);
        Network::Digit GetUdpSessionNbPlayer(uint32_t);
        Network::Digit GetUdpSessionNbRdyPlayer(uint32_t);
        void GetEveryLobbyInfoPack();

        std::map<uint32_t, std::unique_ptr<EcsServer>> _udpSessionList;

    private:

        std::atomic_int32_t _udpSessionID;
        NetworkServer::PortManager _portManager;
        std::vector<Network::Digit> _idList;

    };
}