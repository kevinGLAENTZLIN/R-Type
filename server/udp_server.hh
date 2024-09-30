#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

extern "C" {
    #include <stdio.h>
    #include <string.h>
}

using boost::asio::ip::udp;

class udpServer
{
    public:
        udpServer(boost::asio::io_service& io_service, short port);

        void read_clients();
        void send_back_to_client();
        void received_data_handler(std::size_t recvd_bytes);
        bool check_ACK();

    private:
        udp::socket _socket;
        udp::endpoint _senderEndpoint;
        enum { max_length = 1024 };
        char _data[max_length];
};
