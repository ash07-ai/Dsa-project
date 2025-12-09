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