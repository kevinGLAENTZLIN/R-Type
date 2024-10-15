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
    bool param1 = true;
    int32_t param2 = 42;
    bool new_param1;
    int32_t new_param2;
    
    //                                 | ack        |I| F|P1| P2
    Utils::Network::bytes msg_exemple = {1, 0, 0, 0, 0, 3, 1, 42, 0, 0, 0};
    std::size_t size_of_the_msg = msg_exemple.size();
    std::vector<Utils::PrimitiveType> args = {param1, param2};

    // Let say that the Server send a message to the Client
    Utils::Network::bytes msg = Utils::Network::Protocol::CreateMsg(ack, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame, args);

    for (std::size_t i = 0; i < size_of_the_msg; i++)
        CHECK(msg[i] == msg_exemple[i]);


    // Let say the Client want to decode the Msg
    Utils::Network::Response resp = Utils::Network::Protocol::ParseMsg(true, msg);
    new_param1 = resp.PopParam<bool>();
    new_param2 = resp.PopParam<int32_t>();  

    CHECK(resp.GetACK() == ack);
    CHECK(resp.GetInfoType() == Utils::InfoTypeEnum::GameInfo);
    CHECK(resp.GetInfoFunction() == static_cast<uint8_t>(Utils::GameInfoEnum::JoinGame));
    CHECK(new_param1 == param1);
    CHECK(new_param2 == param2);
}