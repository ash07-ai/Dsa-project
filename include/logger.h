#ifndef LOGGER_H
#define LOGGER_H

#include "btree.h"

class Logger {
private:
    BTree tree;

public:
    void logEvent(int eventCode);     // eventCode = hash(timestamp)
    void saveToFile(const char* filePath);
};

#endif
