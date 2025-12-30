#ifndef BTREE_H
#define BTREE_H

#define T 3  // branching factor

struct BTreeNode {
    int keys[2*T - 1];
    int count;
    bool leaf;
    BTreeNode* child[2*T];

    BTreeNode(bool isLeaf)
    {
        leaf = isLeaf;
        count = 0;
        for (int i = 0; i < 2*T; i++)
            child[i] = nullptr;
    }
};

class BTree {
private:
    BTreeNode* root;

    void insertNonFull(BTreeNode* node, int key);
    void splitChild(BTreeNode* node, int index, BTreeNode* child);
public:
    BTree();
    BTreeNode* getRoot() { return root; }
    void insert(int key);
    bool search(int key);
};

#endif
