#ifndef LOGGER_H
#define LOGGER_H

#include "btree.h"

class Logger {
private:
    BTree tree;

<<<<<<< HEAD
    void inorderSave(BTreeNode* node, std::ofstream &file);

public:
    void logEvent(int eventCode);     
=======
public:
    void logEvent(int eventCode);     // eventCode = hash(timestamp)
>>>>>>> 63cdf17b66d77fcf3146468ad2e073ef6e5f4d8f
    void saveToFile(const char* filePath);
};

#endif
