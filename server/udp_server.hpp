#pragma once

/*
 * https://www.boost.org/doc/libs/1_74_0/doc/html/boost_asio.html
 */

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <stdio.h>
#include <string.h>

using boost::asio::ip::udp;

class server
{
    public:
        server(boost::asio::io_service& io_service, short port);
        ~server();

        void my_udp_receive();
        void my_udp_send_back();

    private:
        udp::socket socket_;
        udp::endpoint sender_endpoint_;
        enum { max_length = 1024 };
        std::string data_;
};

  