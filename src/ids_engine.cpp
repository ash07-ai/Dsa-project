#include "ids_engine.h"
#include "utils.h"
#include <cmath>
#include <iostream>
using namespace std;

void IDS::init()
{
    blacklist.loadFromFile("data/blacklist.txt");
    cout << "✅ IDS Engine Initialized" << endl;
}

void IDS::processPacket(Packet p)
{
    cout << "\n--- Processing Packet from " << p.sourceIP << " ---" << endl;

    bool flag1 = detectBlacklist(p);
    bool flag2 = detectPortScan(p);
    bool flag3 = detectAnomaly(p);

    if (!flag1 && !flag2 && !flag3)
    {
        cout << "✅ Packet is CLEAN" << endl;
    }

    int eventCode = generateEventCode(p.sourceIP, p.port);
    logger.logEvent(eventCode);
}

// ✅ FIXED: Use p.sourceIP
bool IDS::detectBlacklist(Packet p)
{
    if (blacklist.isBlacklisted(p.sourceIP))
    {
        cout << "🚨 ALERT: Blacklisted IP detected!" << endl;
        logger.logEvent(90001);
        return true;
    }
    return false;
}

// ✅ FIXED: Use ipToHash() instead of %
bool IDS::detectPortScan(Packet p)
{
    static int portCount[1000] = {0};
    static long lastTime[1000] = {0};

    int idx = ipToHash(p.sourceIP) % 1000;

    if (p.timestamp - lastTime[idx] > 5)
    {
        portCount[idx] = 0;
    }

    portCount[idx]++;
    lastTime[idx] = p.timestamp;

    if (portCount[idx] > 5)  // 5+ ports = scan
    {
        cout << "🚨 ALERT: Port scan detected!" << endl;
        logger.logEvent(70001);
        return true;
    }

    return false;
}


bool IDS::detectAnomaly(Packet p)
{
    static double mean = 500.0;
    static double variance = 10000.0;
    static int count = 1;

    double deviation = p.packetSize - mean;
    double stdDev = sqrt(variance);

    if (abs(deviation) > 3 * stdDev)
    {
        cout << "🚨 ALERT: Anomaly detected (size=" << p.packetSize << ")" << endl;
        logger.logEvent(80001);
        return true;
    }

    // Update stats
    double oldMean = mean;
    mean = mean + (p.packetSize - mean) / count;
    variance = variance + (p.packetSize - oldMean) * (p.packetSize - mean);
    count++;

    return false;
}
