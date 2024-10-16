/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocol.cpp
*/

#include "./Protocol.hpp"
#include "../Response/Response.hpp"

namespace Utils
{
    namespace Network
    {
        
        /**
         * @brief Read a fixed-size type from a bytes vector.
         * @param offset The offset to start reading from.
         * @param msg The bytes vector to read from.
         * @param type The type to read.
         * @return The value read as a std::any.
         */
        std::any Protocol::newParam(std::size_t &offset, bytes msg, char type_)
        {
            char char_placeholder;
            int32_t int_placeholder;
            double float_placeholder;
            bool bool_placeholder;


            switch (type_)
            {
            case 'c':
                std::memcpy(&char_placeholder, msg.data() + offset, sizeof(char));
                offset += sizeof(char);
                return std::any(char_placeholder);
            case 'i':
                std::memcpy(&int_placeholder, msg.data() + offset, sizeof(int32_t));
                offset += sizeof(int32_t);
                return std::any(int_placeholder);
            case 'f':
                std::memcpy(&float_placeholder, msg.data() + offset, sizeof(double));
                offset += sizeof(double);
                return std::any(float_placeholder);
            case 'b':
                std::memcpy(&bool_placeholder, msg.data() + offset, sizeof(bool));
                offset += sizeof(bool);
                return std::any(bool_placeholder);
            default:
                throw std::runtime_error("Unknown type");
            }
        }

        /**
         * @brief Parse the message received.
         * @param isClient A boolean to know if the message is read by the client or the server.
         * @param msg The message to parse.
         * @return The response object.
         */
        Response Protocol::ParseMsg(bool isClient, bytes &msg)
        {
            uint32_t ack = 0;
            Utils::InfoTypeEnum info = Utils::InfoTypeEnum::GameInfo;
            uint8_t functionDefiner = 0;
            std::vector<std::any> params;
            std::size_t offset = 0;
            std::string params_types;

            Utils::ParametersMap::init_map();

            std::memcpy(&ack, msg.data() + offset, ACK_SIZE);
            offset += ACK_SIZE;
            std::memcpy(&info, msg.data() + offset, INFO_TYPE_SIZE);
            offset += INFO_TYPE_SIZE;
            std::memcpy(&functionDefiner, msg.data() + offset, FUNCTION_TYPE_SIZE);
            offset += FUNCTION_TYPE_SIZE;
            if (isClient)
                params_types = Utils::ParametersMap::getParameterTypePerFunctionClient(info, functionDefiner);
            else
                params_types = Utils::ParametersMap::getParameterTypePerFunctionServer(info, functionDefiner);
            
            for (char type_ : params_types)
                params.push_back(newParam(offset, msg, type_));

            return Response(ack, info, functionDefiner, params);
        }
    } // namespace Network
    
} // namespace Utils
