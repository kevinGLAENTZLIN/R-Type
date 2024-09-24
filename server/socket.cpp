/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** socket
*/

#include "./socket.hh"

extern "C" {

    int Encapsulation::c_socket::my_socket(int domain, int type, int protocol)
    {
        return socket(domain, type, protocol);
    }

    uint16_t Encapsulation::c_socket::my_htons(uint16_t host)
    {
        return htons(host);
    }

    in_addr_t Encapsulation::c_socket::my_inet_addr(std::string addr)
    {
        return inet_addr(addr.c_str());
    }

    ssize_t Encapsulation::c_socket::my_sendto(int fd, const void *buf, size_t n, int flags, const sockaddr *addr, socklen_t addr_len)
    {
        return sendto(fd, buf, n, flags, addr, addr_len);
    }

    ssize_t Encapsulation::c_socket::my_sendto(int fd, std::string buf, int flags, const sockaddr *addr, socklen_t addr_len)
    {
        return sendto(fd, buf.c_str(), buf.length(), flags, addr, addr_len);
    }

    ssize_t Encapsulation::c_socket::my_recvfrom(int fd, void *buf, size_t n, int flags, sockaddr *addr, socklen_t *addr_len)
    {
        return recvfrom(fd, buf, n, flags, addr, addr_len);
    }

    ssize_t Encapsulation::c_socket::my_recvfrom(int fd, std::string &buf, int flags, sockaddr *addr, socklen_t *addr_len)
    {
        char tmp[256];
        ssize_t ret = 0;

        memset(tmp, '\0', 256);
        memcpy(tmp, buf.c_str(), buf.length());
        ret = recvfrom(fd, tmp, sizeof(tmp), flags, addr, addr_len);
        buf = tmp;
        return ret;
    }

}