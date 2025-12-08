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
    int count; // Tracks the number of elements
    const int REHASH_THRESHOLD = 5; //  desired factor

    int hashFunction(const char* key);
    void rehash();

public:
<<<<<<< HEAD
    HashMap()
    {

    }

=======
>>>>>>> 63cdf17b66d77fcf3146468ad2e073ef6e5f4d8f
    HashMap(int size);
    void insert(const char* key);
    bool search(const char* key);
    ~HashMap();
};

#endif
