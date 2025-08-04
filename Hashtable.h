#pragma once
#include <vector>
#include <list>
#include <string>

class HashTable {
private:
    int tableSize = 100;
    std::vector<std::vector<std::vector<std::string>>> buckets;

    int hashingFunc(const std::string& key) const {
        int hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % tableSize;
        }
        return hashValue;
    }

public:
    HashTable() {
        buckets.resize(tableSize);
    }
    void loadWords(std::vector<std::vector<std::string>>& dictionary);
    std::vector<std::string> search(std::string& word);
};