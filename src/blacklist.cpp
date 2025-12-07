#include"blacklist.h"
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

void Blacklist::loadFromFile(const char* filePath)
{
    ifstream rdr("data/blacklist.txt");
    if(!rdr.is_open())
    {
        cout<<"Could not opne the file";
        return;
    }

    string line;
    int lines=0;
    while(getline(rdr,line))
    {
        if(line.empty())
        continue;

        map->insert(line.c_str());
        lines++;
    }
    cout << "Successfully loaded " << lines << " IP(s) from the blacklist." << endl;

}

bool Blacklist::isBlacklisted(const char* ip)
{
    return map->search(ip);
    
}