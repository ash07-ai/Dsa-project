#ifndef IDS_ENGINE_H
#define IDS_ENGINE_H

#include "packet.h"
#include "blacklist.h"
#include "bloom_filter.h"
#include "aho_corasick.h"
#include "logger.h"
#include "stats.h"

class IDS {
private:
    Blacklist blacklist;
    BloomFilter bloomFilter;
    AhoCorasick patternMatcher;  // ⭐ NEW: Pattern matching
    Logger logger;
    Stats stats;

public:
    IDS();
    void init();
    void processPacket(Packet p);

    bool detectBlacklist(Packet p);
    bool detectPortScan(Packet p);
    bool detectAnomaly(Packet p);
    bool detectMaliciousPayload(Packet p);  // ⭐ NEW

    void printStats();  
    void saveStats(const char* filePath);
    
    // Statistics
    int bloomChecks;
    int bloomFalsePositives;
    int payloadThreats;  // ⭐ NEW
};

#endif