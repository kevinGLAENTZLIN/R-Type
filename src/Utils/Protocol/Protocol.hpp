/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocole.hh
*/

#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <cstring>

namespace Utils
{
    namespace Network
    {

        enum class InfoType : uint8_t {
            GameInfo = 1 << 1,
            Player = 1 << 2,
            Enemy = 1 << 3,
            Boss = 1 << 4,
            PowerUp = 1 << 5,
            Projectile = 1 << 6,
        };


        using bytes = std::vector<uint8_t>;

        class Protocol
        {
        private:
            // SIZE OF DIFFERENT PARAMS IN BITS
            const std::size_t ACK_SIZE = sizeof(uint32_t);
            const std::size_t PARAMS_SIZE_SIZE = sizeof(uint8_t);
            const std::size_t INFO_TYPE_SIZE = sizeof(uint8_t);
            const std::size_t FUNCTION_TYPE_SIZE = sizeof(uint8_t);
            const std::size_t MIN_SIZE = ACK_SIZE + PARAMS_SIZE_SIZE + INFO_TYPE_SIZE + FUNCTION_TYPE_SIZE;

            template<typename T>
            void appendFixedSizeTypeIntoBytes(bytes &msg, T value) {
                bytes converted_value(sizeof(T));

                std::memcpy(converted_value.data(), &value, sizeof(T));
                msg.insert(msg.end(), converted_value.begin(), converted_value.end());
            }

        public:
            Protocol() = delete;
            template<typename... Args>
            bytes CreateMsg(uint32_t ack, InfoType info, uint8_t functionDefiner, Args... args)
            {
                bytes msg;
                uint16_t sizeOfMsg = MIN_SIZE;
                ((sizeOfMsg += sizeof(args)), ...)
                appendFixedSizeTypeIntoBytes(msg, ack);
                appendFixedSizeTypeIntoBytes(msg, sizeOfMsg);
                appendFixedSizeTypeIntoBytes(msg, info);
                appendFixedSizeTypeIntoBytes(msg, functionDefiner);
                (appendFixedSizeTypeIntoBytes(msg, args), ...);
            }

        };
                
    } // namespace Network
    
} // namespace Utils
