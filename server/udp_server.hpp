#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <stdio.h>
#include <string.h>

/*
 * https://www.boost.org/doc/libs/1_74_0/doc/html/boost_asio.html
 */

using boost::asio::ip::udp;


class udpServer
{
    public:
        udpServer(boost::asio::io_service& io_service, short port);

        void my_udp_receive();
        void my_udp_send_back();

    private:
        udp::socket _socket;
        udp::endpoint _sender_endpoint;
        enum { max_length = 1024 };
        char _data[max_length];
};
