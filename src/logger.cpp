<<<<<<< HEAD
#include "logger.h"
#include <fstream>
#include"btree.h"

void Logger::logEvent(int eventCode)
{
    tree.insert(eventCode);
}

void Logger::saveToFile(const char* filePath)
{
    std::ofstream file(filePath);
    if (!file.is_open()) 
        return;

    inorderSave(tree.getRoot(), file);
    file.close();
}


void Logger::inorderSave(BTreeNode* node, std::ofstream &file)
{
    if (node == nullptr) return;

    for (int i = 0; i < node->count; i++)
    {
        // left child
        inorderSave(node->child[i], file);   
        // key
        file << node->keys[i] << "\n";       
    }

    inorderSave(node->child[node->count], file); // last child
}
=======
#include"logger.h"
void Logger::logEvent(int eventCode)
{
    

}
>>>>>>> 63cdf17b66d77fcf3146468ad2e073ef6e5f4d8f
