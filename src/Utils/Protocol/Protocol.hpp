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
#include <any>
#include "../Response/Response.hpp"

namespace Utils
{
    namespace Network
    {
        using bytes = std::vector<uint8_t>;

        class Protocol
        {
        private:
            // SIZE OF DIFFERENT PARAMS IN BITS
            static const std::size_t ACK_SIZE = sizeof(uint32_t);
            static const std::size_t PARAMS_SIZE_SIZE = sizeof(uint8_t);
            static const std::size_t INFO_TYPE_SIZE = sizeof(uint8_t);
            static const std::size_t FUNCTION_TYPE_SIZE = sizeof(uint8_t);

            template<typename T>
            static void appendFixedSizeTypeIntoBytes(bytes &msg, T value) {
                bytes converted_value(sizeof(T));

                std::memcpy(converted_value.data(), &value, sizeof(T));
                msg.insert(msg.end(), converted_value.begin(), converted_value.end());
            }
            static std::any newParam(std::size_t &offset, bytes msg, char type_);
            

        public:
            Protocol() = delete;

            template<Utils::FunctionIndex T, typename... Args>
           static bytes CreateMsg(uint32_t ack, Utils::InfoTypeEnum info, T functionDefiner, Args... args)
            {
                bytes msg;

                appendFixedSizeTypeIntoBytes(msg, ack);
                appendFixedSizeTypeIntoBytes(msg, info);
                appendFixedSizeTypeIntoBytes(msg, static_cast<uint8_t>(functionDefiner));
                (appendFixedSizeTypeIntoBytes(msg, args), ...);

                return msg;
            }
            static Response ParseMsg(bool isClient, bytes &msg);
        };
    } // namespace Network
    
} // namespace Utils
