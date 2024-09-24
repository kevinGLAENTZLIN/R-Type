#include "udp_server.hpp"

server::server(boost::asio::io_service& io_service, short port):
    socket_(io_service, udp::endpoint(udp::v4(), port))
{
    my_udp_receive();
}

server::~server()
{
}

void server::my_udp_receive()
{
    socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_,
    [this] (boost::system::error_code error, std::size_t recvd_bytes) {
        if (!error && recvd_bytes > 0) {
            std::cout << "[" << recvd_bytes << "] " << data_ << std::endl;
            my_udp_send_back();
        } else {
            my_udp_receive();
        }
    }
    );
}

void server::my_udp_send_back() {
    std::string myStr = "Sender endpoint : ";
    myStr += sender_endpoint_.address().to_string().c_str();
    myStr += " port ";
    myStr += std::to_string((int)sender_endpoint_.port());
    myStr += " Message : ";
    myStr += data_;
    socket_.async_send_to(boost::asio::buffer(myStr.c_str(), myStr.length()), sender_endpoint_,
    [this] (boost::system::error_code error, std::size_t recvd_bytes) {
        my_udp_receive();
    });
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: udp_server <port>\n";
        return 1;
    }

    try {
        //! Important to understand :
        // 1) instantiate io_service
        // 2) make a customized server
        // 3) start io_service

        boost::asio::io_service io_service;
        server udpServer(io_service, std::atoi(argv[1]));
        io_service.run();
    } catch (std::exception &error) {
        std::cerr << "Exception: " << error.what() << "\n";
    }
    return 0;
}