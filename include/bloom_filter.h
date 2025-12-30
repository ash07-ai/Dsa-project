#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <cstdint>

class BloomFilter {
private:
    uint8_t* bitArray;      // Bit array for the filter
    int size;               // Size in bits
    int numHashes;          // Number of hash functions
    
    // Multiple hash functions
    int hash1(const char* key);
    int hash2(const char* key);
    int hash3(const char* key);
    
    // Set bit at position
    void setBit(int position);
    
    // Check bit at position
    bool getBit(int position);

public:
    BloomFilter(int filterSize = 1024, int hashCount = 3);
    ~BloomFilter();
    
    // Add IP to bloom filter
    void add(const char* ip);
    
    // Check if IP might be in set (may have false positives)
    bool mightContain(const char* ip);
    
    // Load IPs from file into bloom filter
    void loadFromFile(const char* filePath);
    
    // Get statistics
    int getSize() { return size; }
    int getNumHashes() { return numHashes; }
};

#endif