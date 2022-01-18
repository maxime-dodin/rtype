/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-killian.fleury
** File description:
** IProtocol.hpp
*/
#pragma once

#include "Packet.hpp"

namespace Network::Protocol {
    class IProtocol {
        public:
        /**
         * @brief Destroy the IProtocol object
         *
         */
        virtual ~IProtocol() = default;
        /**
         * @brief
         *
         * @param format variadic argument format of the package
         * @param ...
         */
        virtual void pack(const char *format, ...) = 0;
        /**
         * @brief clear buffer in packet
         *
         */
        virtual void clear() = 0;
    };
}
