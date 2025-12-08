#include"ids_engine.h"
#include<string>
#include"hash_map.h"
using namespace std;

void IDS::init() {
    // Initialization code for IDS
}

void IDS::processPacket(Packet p) {
    if (detectBlacklist(p)) {
        logger.logEvent(1); // Log blacklist detection
    }
    if (detectPortScan(p)) {
        logger.logEvent(2); // Log port scan detection
    }
    if (detectAnomaly(p)) {
        logger.logEvent(3); // Log anomaly detection 
    }
}

bool IDS::detectBlacklist(Packet p) {
    return blacklist.isBlacklisted(p.sourceIP);
}



bool IDS::detectPortScan(Packet p) {
    static HashMap portMap; // to track ports per source ip
    std::string key = std::string(p.sourceIP) + ":" + std::to_string(p.port);
    // Port scan detected
    if (portMap.search(key.c_str())) {
        return true; 
    } else {
        portMap.insert(key.c_str());
        return false;
    }
}

bool IDS::detectAnomaly(Packet p) {
    // Simple anomaly detection based on packet size
    return p.packetSize > 1500; 
}
