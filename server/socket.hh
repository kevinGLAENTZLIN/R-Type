/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Encapsulation of C function from the socket.h includes
** socket
*/

#pragma once

extern "C" {
    #include<arpa/inet.h>
    #include<unistd.h>
    #include<sys/socket.h>
    #include<sys/types.h>
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
}
#include<iostream>

namespace Encapsulation
{
    class c_socket
    {
        public:
            static int my_socket(int domain, int type, int protocol);
            static uint16_t my_htons(uint16_t host);
            static in_addr_t my_inet_addr(std::string addr);
            static ssize_t my_sendto(int fd, const void *buf, size_t n, int flags, const sockaddr *addr, socklen_t addr_len);
            static ssize_t my_sendto(int fd, std::string buf, int flags, const sockaddr *addr, socklen_t addr_len);
            static ssize_t my_recvfrom(int fd, void *buf, size_t n, int flags, sockaddr *addr, socklen_t *addr_len);
            static ssize_t my_recvfrom(int fd, std::string &buf, int flags, sockaddr *addr, socklen_t *addr_len);
    };
}
