#ifndef IDS_ENGINE_H
#define IDS_ENGINE_H

#include "packet.h"
#include "blacklist.h"
#include "logger.h"

class IDS {
private:
    Blacklist blacklist;
    Logger logger;

public:
    void init();
    void processPacket(Packet p);

    bool detectBlacklist(Packet p);
    bool detectPortScan(Packet p);
    bool detectAnomaly(Packet p);
};

#endif
