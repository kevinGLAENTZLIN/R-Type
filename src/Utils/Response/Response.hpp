/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Response.hpp
*/

#pragma once
#include <vector>
#include <any>
#include <queue>
#include <cstdint>
#include "../ParametersMap/ParametersMap.hpp"

namespace Utils
{
    namespace Network
    {
        class Response
        {
        private:
            Utils::InfoTypeEnum _infoType;
            uint8_t _infoFunction;
            std::queue<std::any> _params;
            uint32_t _ACK;

        public:
            Response(uint32_t ACK, Utils::InfoTypeEnum infoType, uint8_t infoFunction, std::vector<std::any> list_params);
            ~Response() = default;

            Utils::InfoTypeEnum GetInfoType() const;
            uint8_t GetInfoFunction() const;
            uint32_t GetACK() const;

            std::any RawPopParam();

            template<typename T>
            T PopParam()
            {
                return std::any_cast<T>(RawPopParam());
            }
        };       
    }
}