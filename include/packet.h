#ifndef PACKET_H
#define PACKET_H

struct Packet {
    char sourceIP[20];
    char destIP[20];
    int port;
    int packetSize;
    char payload[256];
};

Packet parsePacket(const char* Line);

#endif
