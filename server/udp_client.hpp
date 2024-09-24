#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma once

using namespace std;

class udpSocket {

    public:
        udpSocket(char *inServer, int inPort);
        ~udpSocket();

        ssize_t sendRecv(char *inMsg);
        void  printMsg();
        std::string getRecvMsg();
        ssize_t getRecvBytes();

    private:
        int     _port;
        ssize_t _sByte;
        ssize_t _rByte;
        char    _server[100];
        char _bufferSend[256];
        char _bufferRecv[256];
};
