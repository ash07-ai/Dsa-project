#include"packet.h"
#include<iostream>
#include <cstdio>


using namespace std;

Packet parsePacket(const char* Line) 
{
    Packet pkt;
    sscanf(Line, "%19s %19s %d %d %255s", pkt.sourceIP, pkt.destIP, &pkt.port, &pkt.packetSize, pkt.payload);
    return pkt;
}

