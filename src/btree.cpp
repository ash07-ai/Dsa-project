#include"btree.h"
#include <iostream>
using namespace std;

BTree::BTree() 
{
    root = nullptr;
}


void splitChild(BTreeNode* parent, int index, BTreeNode* child) 
{
    BTreeNode* newChild = new BTreeNode(child->leaf);
    newChild->count = T - 1;

    for (int j = 0; j < T - 1; j++)
        newChild->keys[j] = child->keys[j + T];

    if (!child->leaf) 
    {
        for (int j = 0; j < T; j++)
            newChild->child[j] = child->child[j + T];
    }

    child->count = T - 1;

    for (int j = parent->count; j >= index + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[index + 1] = newChild;

    for (int j = parent->count - 1; j >= index; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[index] = child->keys[T - 1];
    parent->count++;
}

void insertNonFull(BTreeNode* node, int key) 
{
    int i = node->count - 1;

    if (node->leaf) 
    {
        while (i >= 0 && node->keys[i] > key) 
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->count++;
    } 
    else 
    {
        while (i >= 0 && node->keys[i] > key)
            i--;

        i++;
        if (node->child[i]->count == 2 * T - 1) 
        {
            splitChild(node, i, node->child[i]);
            if (node->keys[i] < key)
                i++;
        }
        insertNonFull(node->child[i], key);
    }
}

void BTree::insert(int key) 
{
    if (root == nullptr) 
    {
        root = new BTreeNode(true);
        root->keys[0] = key;
        root->count = 1;
    } 
    else 
    {
        if (root->count == 2 * T - 1) 
        {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->child[0] = root;
            splitChild(newRoot, 0, root);
            int i = 0;
            if (newRoot->keys[0] < key)
                i++;
            insertNonFull(newRoot->child[i], key);
            root = newRoot;
        } 
        else 
        {
            insertNonFull(root, key);
        }
    }
}

bool BTree::search(int key) 
{
    BTreeNode* current = root;
    while (current != nullptr) 
    {
        int i = 0;
        while (i < current->count && key > current->keys[i])
            i++;

        if (i < current->count && current->keys[i] == key)
            return true;

        if (current->leaf)
            return false;
        else
            current = current->child[i];
    }
    return false;
}