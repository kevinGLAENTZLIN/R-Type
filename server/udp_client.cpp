#include "./udp_client.hh"
#include "./socket.hh"

udpSocket::udpSocket(char *inServer, int inPort) : _port(inPort), _sByte(0), _rByte(0), _server(inServer)
{
}

udpSocket::~udpSocket()
{
}

ssize_t udpSocket::sendRecv(char *inMsg)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servAddr;
    struct sockaddr_in  cliAddr;
    socklen_t cLen = sizeof(cliAddr);
    socklen_t sLen = sizeof(servAddr);

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = Encapsulation::c_socket::my_htons(_port);
    servAddr.sin_addr.s_addr = Encapsulation::c_socket::my_inet_addr(_server);
    _bufferSend = inMsg;
    _sByte = Encapsulation::c_socket::my_sendto(sockfd, _bufferSend,0,(struct sockaddr * )&servAddr,sLen);
    std::cout << "[" << _sByte << "] Bytes Sent : " << std::endl;
    _rByte = Encapsulation::c_socket::my_recvfrom(sockfd, _bufferRecv,0,(struct sockaddr *)&cliAddr,&cLen);
    close(sockfd);
    return _sByte;
}

void  udpSocket::printMsg() 
{
    std::cout << "[" << _rByte << "] Bytes Rcvd : " << _bufferRecv << std::endl;
}

std::string udpSocket::getRecvMsg()
{
    return _bufferRecv;
}

ssize_t udpSocket::getRecvBytes()
{
    return _rByte;
}

int main(int argc, char **argv)
{
    if ( argc != 4 ) {
        std::cout << "Usage:udp_client [server] [_port] [Message]" << std::endl;
        exit(84);
    }
    udpSocket mUDP(argv[1], std::stoi(argv[2]));
    if ( mUDP.sendRecv(argv[3]) > 0 ) {
        std::cout << "[" << mUDP.getRecvBytes() << "] " << mUDP.getRecvMsg() << std::endl;
    }

    exit(0);
}
 