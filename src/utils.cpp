#include "utils.h"
#include <cstring>

int generateEventCode(const char* srcIP, int port) 
{
    int hash = 0;
    for (int i = 0; srcIP[i] != '\0'; i++) 
    {
        hash = (hash * 31 + srcIP[i]) % 100000;
    }
    return (hash + port) % 100000;
}

int ipToHash(const char* ip) 
{
    int hash = 0;
    for (int i = 0; ip[i] != '\0'; i++) 
    {
        hash = (hash * 31 + ip[i]);
    }
    return hash > 0 ? hash : -hash;  // make positive
}