/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocole.hh
*/

/**
 * @file Protocole.hpp
 * @brief Declaration of the Utils::Network::Protocole class for the communication protocol.
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
        /**
         * @typedef bytes
         * @brief Alias for a vector of uint8_t.
         */
        using bytes = std::vector<uint8_t>;

        class Protocol
        {
        private:
            static const std::size_t ACK_SIZE = sizeof(uint32_t);
            static const std::size_t PARAMS_SIZE_SIZE = sizeof(uint8_t);
            static const std::size_t INFO_TYPE_SIZE = sizeof(uint8_t);
            static const std::size_t FUNCTION_TYPE_SIZE = sizeof(uint8_t);

            /**
             * @brief Appends a fixed-size type into a bytes vector.
             * 
             * @tparam T have to be Primitive type.
             * @param msg The bytes vector to append the value to.
             * @param value The value to append.
             */
            template<typename T>
            static void appendFixedSizeTypeIntoBytes(bytes &msg, T value) {
                bytes converted_value(sizeof(T));

                std::memcpy(converted_value.data(), &value, sizeof(T));
                msg.insert(msg.end(), converted_value.begin(), converted_value.end());
            }
            /**
             * @brief Extracts a fixed-size type from a bytes vector.
             * 
             * @param offset The offset to start extracting from.
             * @param msg The bytes vector to extract the value from.
             * @param type_ The type of the value to extract.
             * @return The extracted value in a std::any.
             */
            static std::any newParam(std::size_t &offset, bytes msg, char type_);
            

        public:
            Protocol() = delete;

            /**
             * @brief Encode the msg in bytes.
             * @tparam T The type of the function to send.
             * @param ack The ACK number.
             * @param info The type of the message.
             * @param functionDefiner The function to send.
             * @param args The list of arguments to send.
             * @return The message to send in bytes.
             */
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

            /**
             * @brief Parse the message received.
             * @param isClient True if the message is read by a Client, False if it's read by a Server.
             * @param msg The message to parse.
             * @return The response to the message.
             */
            static Response ParseMsg(bool isClient, bytes &msg);
        };
    } // namespace Network
    
} // namespace Utils
