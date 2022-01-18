/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-Babel-killian.fleury
** File description:
** Packet.hpp
*/
#pragma once

#include <iostream>
#include <cstring>
#include "Data.hpp"

namespace Network::Protocol {
    struct Packet {
        /**
         * @brief Construct a new Packet object
         *
         */
        Packet();
        /**
         * @brief Destroy the Packet object
         *
         */
        ~Packet() = default;
        /**
         * @brief Construct a new Packet object
         *
         * @param copy
         */
        Packet(const Packet &copy)
        {
            sizeOfPacket = copy.sizeOfPacket;
            typeHeader = copy.typeHeader;
        }
        Digit sizeOfPacket;
        Digit typeHeader;

    };
}
