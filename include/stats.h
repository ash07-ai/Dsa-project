#ifndef STATS_H
#define STATS_H

#include <iostream>

class Stats {
private:
    int totalPackets;
    int cleanPackets;
    int blacklistHits;
    int portScans;
    int anomalies;
    
    // Detailed tracking
    char topAttackerIP[20];
    int topAttackerCount;

public:
    Stats();
    
    void incrementTotal();
    void incrementClean();
    void incrementBlacklist();
    void incrementPortScan();
    void incrementAnomaly();
    
    void updateTopAttacker(const char* ip);
    
    void printSummary();
    void saveToFile(const char* filePath);
};

#endif