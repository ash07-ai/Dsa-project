#include "packet.h"
#include <cstdio>

Packet parsePacket(const char* Line) 
{
    Packet pkt;
    pkt.timestamp = 0;
    
    sscanf(Line, "%19s %19s %d %d %255s %ld", 
           pkt.sourceIP, pkt.destIP, 
           &pkt.port, &pkt.packetSize, 
           pkt.payload, &pkt.timestamp);
    
    return pkt;
}