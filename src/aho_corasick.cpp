#include "aho_corasick.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

AhoCorasick::AhoCorasick() {
    root = new ACNode();
}

AhoCorasick::~AhoCorasick() {
    // Simple cleanup - in production use proper recursive delete
    delete root;
}

void AhoCorasick::addPattern(const char* pattern) {
    ACNode* current = root;
    
    // Build trie
    for (int i = 0; pattern[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)pattern[i];
        
        if (current->children[ch] == nullptr) {
            current->children[ch] = new ACNode();
        }
        current = current->children[ch];
    }
    
    // Mark end of pattern
    current->isEnd = true;
    current->pattern = pattern;
}

void AhoCorasick::buildFailureLinks() {
    queue<ACNode*> q;
    
    // Initialize: root's children fail to root
    for (int i = 0; i < 256; i++) {
        if (root->children[i] != nullptr) {
            root->children[i]->fail = root;
            q.push(root->children[i]);
        }
    }
    
    // BFS to build failure links
    while (!q.empty()) {
        ACNode* current = q.front();
        q.pop();
        
        for (int i = 0; i < 256; i++) {
            if (current->children[i] != nullptr) {
                ACNode* child = current->children[i];
                q.push(child);
                
                // Find failure link
                ACNode* failNode = current->fail;
                while (failNode != nullptr && failNode->children[i] == nullptr) {
                    failNode = failNode->fail;
                }
                
                if (failNode == nullptr) {
                    child->fail = root;
                } else {
                    child->fail = failNode->children[i];
                }
            }
        }
    }
}

vector<string> AhoCorasick::search(const char* text) {
    vector<string> matches;
    ACNode* current = root;
    
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)text[i];
        
        // Follow failure links if no match
        while (current != root && current->children[ch] == nullptr) {
            current = current->fail;
        }
        
        // Move to next state
        if (current->children[ch] != nullptr) {
            current = current->children[ch];
        }
        
        // Check for pattern match
        ACNode* temp = current;
        while (temp != root) {
            if (temp->isEnd) {
                matches.push_back(temp->pattern);
            }
            temp = temp->fail;
        }
    }
    
    return matches;
}

void AhoCorasick::loadPatternsFromFile(const char* filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "⚠️  Warning: Could not open " << filePath << endl;
        return;
    }
    
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        addPattern(line.c_str());
        count++;
    }
    
    cout << "🔍 Loaded " << count << " attack patterns" << endl;
    
    // Build failure links after all patterns added
    buildFailureLinks();
    
    file.close();
}