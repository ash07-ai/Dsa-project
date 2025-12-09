#ifndef LOGGER_H
#define LOGGER_H
#include "btree.h"
#include <fstream>

class Logger {
private:
    BTree tree;

    void inorderSave(BTreeNode* node, std::ofstream &file);

public:
    void logEvent(int eventCode);     
    void saveToFile(const char* filePath);
};

#endif
