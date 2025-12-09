#include"hash_map.h"
#include <cstring>
#include <iostream>
using namespace std;

HashMap::HashMap(int size) 
{
    capacity = size;
    table = new HashNode * [capacity];
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
    if (count >= capacity * REHASH_THRESHOLD) 
    {
        rehash();
    }


    int index=hashFunction(key);
    if(search(key))
    {
        cout<<"IP "<<key<<" already exists in the HashMap."<<endl;
        return;
    }


    HashNode* newNode = new HashNode();
    strcpy(newNode->key,key);
    newNode->next = table[index];
    table[index] = newNode;
    count++;
    cout<<"Inserted IP "<<key<<" at index "<<index<<endl;
}

void HashMap::rehash() 
{
    int oldcapacity = capacity;
    HashNode **oldtable = table;
    capacity *= 2;
    table = new HashNode * [capacity];
    for (int i = 0; i < capacity; i++) 
    {
        table[i] = nullptr;
    }
    
    for(int i=0;i<oldcapacity;i++)
    {
        HashNode *curr=oldtable[i];
        while(curr!=nullptr)
        {
            HashNode *nextNode=curr->next;
            int newIndex=hashFunction(curr->key);
            curr->next=table[newIndex];
            table[newIndex]=curr;
            curr=nextNode;
        }
    }
    delete[] oldtable;
    std::cout << "--- HASH TABLE REHASHED! New Capacity: " << capacity << " ---" << std::endl;

}