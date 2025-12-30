#ifndef HASH_MAP_H
#define HASH_MAP_H

struct HashNode {
    char key[20];   // IP
    HashNode* next;
};

class HashMap {
private:
    HashNode** table;
    int capacity;
    int count;
    
    // Load factor threshold (0.75 = 75% full)
    const double REHASH_THRESHOLD = 0.75;

    int hashFunction(const char* key);
    void rehash();

public:
    HashMap(int size);
    void insert(const char* key);
    bool search(const char* key);
    ~HashMap();
};

#endif