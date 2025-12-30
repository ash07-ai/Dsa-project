#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <string>
#include <vector>

// Simple Trie Node for pattern matching
struct ACNode {
    ACNode* children[256];  // ASCII characters
    ACNode* fail;           // Failure link
    bool isEnd;             // End of pattern
    std::string pattern;    // Matched pattern
    
    ACNode() {
        for (int i = 0; i < 256; i++)
            children[i] = nullptr;
        fail = nullptr;
        isEnd = false;
    }
};

class AhoCorasick {
private:
    ACNode* root;
    
    void buildFailureLinks();  // Build failure function

public:
    AhoCorasick();
    ~AhoCorasick();
    
    // Add a pattern to detect
    void addPattern(const char* pattern);
    
    // Search text for all patterns
    std::vector<std::string> search(const char* text);
    
    // Load patterns from file
    void loadPatternsFromFile(const char* filePath);
};

#endif