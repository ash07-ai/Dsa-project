#include "stats.h"
#include <cstring>
#include <fstream>
#include <iomanip>

Stats::Stats() {
    totalPackets = 0;
    cleanPackets = 0;
    blacklistHits = 0;
    portScans = 0;
    anomalies = 0;
    topAttackerCount = 0;
    strcpy(topAttackerIP, "None");
}

void Stats::incrementTotal() {
    totalPackets++;
}

void Stats::incrementClean() {
    cleanPackets++;
}

void Stats::incrementBlacklist() {
    blacklistHits++;
}

void Stats::incrementPortScan() {
    portScans++;
}

void Stats::incrementAnomaly() {
    anomalies++;
}

void Stats::updateTopAttacker(const char* ip) {
    // Simple tracking - in real system you'd use HashMap
    topAttackerCount++;
    strcpy(topAttackerIP, ip);
}

void Stats::printSummary() {
    int threats = blacklistHits + portScans + anomalies;
    double threatPercent = totalPackets > 0 ? (threats * 100.0 / totalPackets) : 0;
    double cleanPercent = totalPackets > 0 ? (cleanPackets * 100.0 / totalPackets) : 0;
    
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════╗\n";
    std::cout << "║       IDS DETECTION SUMMARY                ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    std::cout << "║ Total Packets Analyzed: " << std::setw(15) << totalPackets << "    ║\n";
    std::cout << "║ Clean Packets:          " << std::setw(8) << cleanPackets 
              << " (" << std::fixed << std::setprecision(1) << cleanPercent << "%)  ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    std::cout << "║           THREATS DETECTED                 ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    std::cout << "║ 🚨 Blacklist Hits:      " << std::setw(15) << blacklistHits << "    ║\n";
    std::cout << "║ 🚨 Port Scans:          " << std::setw(15) << portScans << "    ║\n";
    std::cout << "║ 🚨 Anomalies:           " << std::setw(15) << anomalies << "    ║\n";
    std::cout << "║ ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ ║\n";
    std::cout << "║ Total Threats:          " << std::setw(8) << threats 
              << " (" << std::fixed << std::setprecision(1) << threatPercent << "%)  ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    std::cout << "║ Most Active IP: " << std::setw(22) << topAttackerIP << "    ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n";
}

void Stats::saveToFile(const char* filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) return;
    
    file << "IDS Statistics Report\n";
    file << "=====================\n\n";
    file << "Total Packets: " << totalPackets << "\n";
    file << "Clean Packets: " << cleanPackets << "\n";
    file << "Blacklist Hits: " << blacklistHits << "\n";
    file << "Port Scans: " << portScans << "\n";
    file << "Anomalies: " << anomalies << "\n";
    file << "Most Active IP: " << topAttackerIP << "\n";
    
    file.close();
}