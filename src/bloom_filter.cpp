#include "bloom_filter.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include<string>


using namespace std;

BloomFilter::BloomFilter(int filterSize, int hashCount) {
    size = filterSize;
    numHashes = hashCount;
    
    // Allocate bit array (size in bytes = size/8)
    int byteSize = (size + 7) / 8;
    bitArray = new uint8_t[byteSize];
    
    // Initialize all bits to 0
    memset(bitArray, 0, byteSize);
}

BloomFilter::~BloomFilter() {
    delete[] bitArray;
}

// Hash function 1: Simple string hash
int BloomFilter::hash1(const char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31 + key[i]) % size;
    }
    return hash < 0 ? -hash : hash;
}

// Hash function 2: DJB2 hash
int BloomFilter::hash2(const char* key) {
    unsigned long hash = 5381;
    int c;
    int i = 0;
    while ((c = key[i++])) {
        hash = ((hash << 5) + hash) + c;
    }
    return (hash % size);
}

// Hash function 3: SDBM hash
int BloomFilter::hash3(const char* key) {
    unsigned int hash = 0;
    int c;
    int i = 0;
    while ((c = key[i++])) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return (hash % size);
}

void BloomFilter::setBit(int position) {
    int byteIndex = position / 8;
    int bitIndex = position % 8;
    bitArray[byteIndex] |= (1 << bitIndex);
}

bool BloomFilter::getBit(int position) {
    int byteIndex = position / 8;
    int bitIndex = position % 8;
    return (bitArray[byteIndex] & (1 << bitIndex)) != 0;
}

void BloomFilter::add(const char* ip) {
    // Apply all hash functions and set bits
    int h1 = hash1(ip);
    int h2 = hash2(ip);
    int h3 = hash3(ip);
    
    setBit(h1);
    setBit(h2);
    setBit(h3);
}

bool BloomFilter::mightContain(const char* ip) {
    // Check all hash positions
    int h1 = hash1(ip);
    int h2 = hash2(ip);
    int h3 = hash3(ip);
    
    // If ANY bit is not set, definitely not in the set
    return getBit(h1) && getBit(h2) && getBit(h3);
}

void BloomFilter::loadFromFile(const char* filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "⚠️  Warning: Could not open " << filePath << " for bloom filter" << endl;
        return;
    }
    
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        add(line.c_str());
        count++;
    }
    
    cout << "🌸 Bloom Filter loaded " << count << " IPs" << endl;
    file.close();
}