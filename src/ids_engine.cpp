#include "ids_engine.h"
#include "utils.h"
#include <cmath>
#include <iostream>
using namespace std;

IDS::IDS() : bloomFilter(2048, 3) {
    bloomChecks = 0;
    bloomFalsePositives = 0;
    payloadThreats = 0;
}

void IDS::init() {
    cout << "🔧 Initializing IDS Engine..." << endl;
    
    // Load blacklist into both HashMap and Bloom Filter
    blacklist.loadFromFile("data/blacklist.txt");
    bloomFilter.loadFromFile("data/blacklist.txt");
    
    // Load attack patterns for Aho-Corasick
    patternMatcher.loadPatternsFromFile("data/patterns.txt");
    
    cout << "✅ IDS Engine Initialized\n" << endl;
}

void IDS::processPacket(Packet p) {
    stats.incrementTotal();
    
    cout << "\n--- Processing Packet from " << p.sourceIP << " ---" << endl;

    bool flag1 = detectBlacklist(p);
    bool flag2 = detectPortScan(p);
    bool flag3 = detectAnomaly(p);
    bool flag4 = detectMaliciousPayload(p);  // NEW: Pattern matching

    if (!flag1 && !flag2 && !flag3 && !flag4) {
        stats.incrementClean();
        cout << "✅ Packet is CLEAN" << endl;
    } else {
        stats.updateTopAttacker(p.sourceIP);
    }

    int eventCode = generateEventCode(p.sourceIP, p.port);
    logger.logEvent(eventCode);
}

void IDS::printStats() {
    stats.printSummary();
    
    // Print Bloom Filter statistics
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║       BLOOM FILTER PERFORMANCE             ║\n";
    cout << "╠════════════════════════════════════════════╣\n";
    cout << "║ Total Bloom Checks: " << bloomChecks << "                   ║\n";
    cout << "║ False Positives:    " << bloomFalsePositives << "                   ║\n";
    
    if (bloomChecks > 0) {
        double fpRate = (bloomFalsePositives * 100.0) / bloomChecks;
        cout << "║ False Positive Rate: " << fpRate << "%              ║\n";
    }
    
    cout << "╚════════════════════════════════════════════╝\n";
    
    // Print Pattern Matching statistics
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║       PATTERN MATCHING RESULTS             ║\n";
    cout << "╠════════════════════════════════════════════╣\n";
    cout << "║ Malicious Payloads Found: " << payloadThreats << "            ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
}

void IDS::saveStats(const char* filePath) {
    stats.saveToFile(filePath);
}

bool IDS::detectBlacklist(Packet p) {
    bloomChecks++;
    
    // FIRST: Quick bloom filter check
    bool mightBeBlacklisted = bloomFilter.mightContain(p.sourceIP);
    
    if (!mightBeBlacklisted) {
        cout << "🌸 Bloom: Definitely NOT blacklisted (fast path)" << endl;
        return false;
    }
    
    cout << "🌸 Bloom: Might be blacklisted - checking HashMap..." << endl;
    
    bool actuallyBlacklisted = blacklist.isBlacklisted(p.sourceIP);
    
    if (!actuallyBlacklisted) {
        bloomFalsePositives++;
        cout << "⚠️  Bloom Filter false positive detected!" << endl;
        return false;
    }
    
    cout << "🚨 ALERT: Blacklisted IP detected!" << endl;
    logger.logEvent(90001);
    stats.incrementBlacklist();
    return true;
}

bool IDS::detectPortScan(Packet p) {
    static int portCount[1000] = {0};
    static long lastTime[1000] = {0};

    int idx = ipToHash(p.sourceIP) % 1000;

    if (p.timestamp - lastTime[idx] > 5) {
        portCount[idx] = 0;
    }

    portCount[idx]++;
    lastTime[idx] = p.timestamp;

    if (portCount[idx] > 6) {
        cout << "🚨 ALERT: Port scan detected!" << endl;
        logger.logEvent(70001);
        stats.incrementPortScan();
        return true;
    }

    return false;
}

bool IDS::detectAnomaly(Packet p) {
    static double mean = 500.0;
    static double variance = 10000.0;
    static int count = 1;

    double deviation = p.packetSize - mean;
    double stdDev = sqrt(variance);

    if (abs(deviation) > 3 * stdDev) {
        cout << "🚨 ALERT: Anomaly detected (size=" << p.packetSize << ")" << endl;
        logger.logEvent(80001);
        stats.incrementAnomaly();
        return true;
    }

    double oldMean = mean;
    mean = mean + (p.packetSize - mean) / count;
    variance = variance + (p.packetSize - oldMean) * (p.packetSize - mean);
    count++;

    return false;
}

bool IDS::detectMaliciousPayload(Packet p) {
    // Use Aho-Corasick to search for attack patterns in payload
    vector<string> matches = patternMatcher.search(p.payload);
    
    if (!matches.empty()) {
        cout << "🚨 ALERT: Malicious payload detected!" << endl;
        cout << "   Found patterns: ";
        for (size_t i = 0; i < matches.size(); i++) {
            cout << "'" << matches[i] << "'";
            if (i < matches.size() - 1) cout << ", ";
        }
        cout << endl;
        
        logger.logEvent(95001);
        payloadThreats++;
        return true;
    }
    
    return false;
}