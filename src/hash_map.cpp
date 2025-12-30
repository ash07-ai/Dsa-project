#include "hash_map.h"
#include <cstring>
#include <iostream>
using namespace std;

HashMap::HashMap(int size) 
{
    capacity = size;
    count = 0;  
    table = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++) 
    {
        table[i] = nullptr;
    }
}

int HashMap::hashFunction(const char* key) 
{
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) 
    {
        hash = (hash + key[i]) % capacity;
    }
    return hash;
}

bool HashMap::search(const char* key) 
{
    int index = hashFunction(key);
    HashNode* current = table[index];
    
    while (current != nullptr)
    {
        if (strcmp(current->key, key) == 0) 
        {
            return true;
        }
        current = current->next;

    }

    return false;

}

void HashMap::insert(const char* key) 
{
    // Check if already exists
    if (search(key))
    {
        // Silently ignore duplicates (no need to print)
        return;


    }

    // Check load factor BEFORE inserting
    double loadFactor = (double)count / capacity;
    if (loadFactor >= REHASH_THRESHOLD) 
    {
        cout << "⚠️  Load factor " << loadFactor 
             << " exceeded threshold. Rehashing..." << endl;
        rehash();
    }

    // Insert the new node
    int index = hashFunction(key);
    HashNode* newNode = new HashNode();
    strcpy(newNode->key, key);
    newNode->next = table[index];
    table[index] = newNode;
    count++;


}

void HashMap::rehash() 
{
    int oldCapacity = capacity;
    HashNode** oldTable = table;
    
    // Double the capacity
    capacity *= 2;
    count = 0;  // Reset count (will be recalculated during reinsert)
    
    // Create new table
    table = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++) 
    {
        table[i] = nullptr;
    }
    
    // Reinsert all elements
    for (int i = 0; i < oldCapacity; i++)
    {
        HashNode* current = oldTable[i];
        while (current != nullptr)
        {
            HashNode* next = current->next;
            
            // Recompute hash with new capacity
            int newIndex = hashFunction(current->key);
            
            // Insert into new table
            current->next = table[newIndex];
            table[newIndex] = current;
            count++;
            
            current = next;
        }
    }
    
    delete[] oldTable;
    cout << "✅ Rehashed! Old capacity: " << oldCapacity 
         << " → New capacity: " << capacity << endl;
}

HashMap::~HashMap()
{
    for (int i = 0; i < capacity; i++)
    {
        HashNode* current = table[i];
        while (current != nullptr)
        {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}