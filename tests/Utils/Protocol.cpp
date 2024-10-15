/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocol.cpp
*/

#include <doctest/doctest.h>
#include "Utils/Protocol/Protocol.hpp"

TEST_CASE("Protocol") {
    uint32_t ack = 1;
    int32_t param1 = 42;
    double param2 = 3.14;
    int32_t new_param1;
    double new_param2;
    
    //                                 | ack        |I| F|     P1     | P2
    Utils::Network::bytes msg_exemple = {1, 0, 0, 0, 0, 0, 42, 0, 0, 0, 31, 133, 235, 81, 184, 30, 9, 64};
    std::size_t size_of_the_msg = msg_exemple.size();

    // Let say that the Server send a message to the Client
    Utils::Network::bytes msg = Utils::Network::Protocol::CreateMsg(ack, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected, param1, param2);

    for (std::size_t i = 0; i < size_of_the_msg; i++)
        CHECK(msg[i] == msg_exemple[i]);


    // Let say the Client want to decode the Msg
    Utils::Network::Response resp = Utils::Network::Protocol::ParseMsg(true, msg);
    new_param1 = resp.PopParam<int32_t>();
    new_param2 = resp.PopParam<double>();  

    CHECK(resp.GetACK() == ack);
    CHECK(resp.GetInfoType() == Utils::InfoTypeEnum::GameInfo);
    CHECK(resp.GetInfoFunction() == static_cast<uint8_t>(Utils::GameInfoEnum::NewClientConnected));
    CHECK(new_param1 == param1);
    CHECK(new_param2 == param2);
}