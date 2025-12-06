#ifndef BTREE_H
#define BTREE_H

#define T 3  // branching factor

struct BTreeNode {
    int keys[2*T - 1];
    int count;
    bool leaf;
    BTreeNode* child[2*T];

    BTreeNode(bool isLeaf);
};

class BTree {
private:
    BTreeNode* root;

    void insertNonFull(BTreeNode* node, int key);
    void splitChild(BTreeNode* node, int index, BTreeNode* child);

public:
    BTree();
    void insert(int key);
    bool search(int key);
};

#endif
