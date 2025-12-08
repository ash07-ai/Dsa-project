#ifndef BLACKLIST_H
#define BLACKLIST_H

#include "hash_map.h"

class Blacklist {
private:
    HashMap* map;

public:
    Blacklist();
    void loadFromFile(const char* filePath);

    bool isBlacklisted(const char* ip);

};

#endif
