#include "blacklist.h"
#include <fstream>
#include <iostream>
#include<string>

using namespace std;

Blacklist::Blacklist() 
{
    map = new HashMap(100);  
}

void Blacklist::loadFromFile(const char* filePath)
{
    ifstream rdr(filePath);
    if (!rdr.is_open())
    {
        cout << "Could not open the file: " << filePath << endl;
        return;
    }

    string line;
    int lines = 0;
    while (getline(rdr, line))
    {
        if (line.empty())
            continue;

        map->insert(line.c_str());
        lines++;
    }
    cout << "✅ Loaded " << lines << " blacklisted IPs." << endl;
    rdr.close();
}

bool Blacklist::isBlacklisted(const char* ip)
{
    return map->search(ip);
}