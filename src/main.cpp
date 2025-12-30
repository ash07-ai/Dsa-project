#include "ids_engine.h"
#include "packet.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
    IDS ids;
    ids.init();

    ifstream fin("data/packets.txt");
    if (!fin.is_open())
    {
        cout << "❌ Error: Could not open data/packets.txt" << endl;
        return 1;
    }

    char line[300];
    int packetNum = 0;

    cout << "🔍 Starting packet analysis...\n" << endl;

    while (fin.getline(line, 300)) 
    {
        if (line[0] == '\0') continue;
        
        Packet p = parsePacket(line);
        packetNum++;
        
        cout << "\n========== PACKET #" << packetNum << " ==========" << endl;
        ids.processPacket(p);
    }

    fin.close();
    
    // Print beautiful summary
    cout << "\n\n";
    cout << "═══════════════════════════════════════════\n";
    cout << "    ANALYSIS COMPLETE\n";
    cout << "═══════════════════════════════════════════\n";
    
    ids.printStats();
    
    // Save to file
    ids.saveStats("data/ids_report.txt");
    cout << "\n📊 Report saved to: data/ids_report.txt\n" << endl;
    
    return 0;
    
}

int main1() 
{
    IDS ids;
    ids.init();

    ifstream fin("data/packets.txt");
    if (!fin.is_open())
    {
        cout << "❌ Error: Could not open packets.txt" << endl;
        return 1;
    }

    char line[300];
    int packetNum = 0;

    while (fin.getline(line, 300)) 
    {
        if (line[0] == '\0') continue;  // skip empty
        
        Packet p = parsePacket(line);
        packetNum++;
        
        cout << "\n========== PACKET #" << packetNum << " ==========" << endl;
        ids.processPacket(p);
    }

    cout << "\n✅ IDS Finished. Total packets: " << packetNum << endl;
    fin.close();
    
    return 0;
}

int main2()
{
    IDS ids;
    ids.init();
Packet p1 = {"192.168.1.10", "10.0.0.5", 22, 500, "SSH attempt", 1001};
Packet p2 = {"192.168.1.10", "10.0.0.5", 22, 600, "SSH attempt", 1002};
Packet p3 = {"192.168.1.10", "10.0.0.3", 80, 300, "HTTP GET", 1003};
ids.processPacket(p1);
ids.processPacket(p2);
ids.processPacket(p3);
    return 0;

}