#include "udp_server.hpp"

udpServer::udpServer(boost::asio::io_service& io_service, short port)
  : _socket(io_service, udp::endpoint(udp::v4(), port))
{
  my_udp_receive();
}

void udpServer::my_udp_receive() {
    _socket.async_receive_from(boost::asio::buffer(_data, max_length), _sender_endpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if ( !ec && recvd_bytes > 0 ) {
            std::cout << "[" << recvd_bytes << "] " << _data << std::endl;
            my_udp_send_back();
        }
        else {
            my_udp_receive();
        }
    });
}

void udpServer::my_udp_send_back()
{
    // do add sender information and send back
    std::string myStr = "Sender endpoint : ";
    myStr += _sender_endpoint.address().to_string().c_str();
    myStr += " port ";
    myStr += std::to_string((int)_sender_endpoint.port());
    myStr += " Message : ";
    myStr += _data;
    _socket.async_send_to(boost::asio::buffer(myStr.c_str(), myStr.length()), _sender_endpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
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
        boost::asio::io_service io_service;
        udpServer mySer(io_service, std::atoi(argv[1]));
        io_service.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}