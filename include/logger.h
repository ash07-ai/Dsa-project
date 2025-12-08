#ifndef LOGGER_H
#define LOGGER_H

#include "btree.h"

class Logger {
private:
    BTree tree;

    void inorderSave(BTreeNode* node, std::ofstream &file);

public:
    void logEvent(int eventCode);     
    void saveToFile(const char* filePath);
};

#endif
