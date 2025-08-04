#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include "Trie.h"

std::vector<std::string> linearSearch(std::vector<std::vector<std::string>> dictionary, std::string word){
    std::vector<std::string> definitions;
    for (std::vector<std::string> entry : dictionary) {
        if (entry[0] == word) {
            definitions.push_back(entry[1]);
        }
    }
    
    return definitions;
}

std::vector<std::vector<std::string>> loadDictionary(std::vector<std::vector<std::string>> &dictionary, Trie& trie) {
    std::cout << "Loading dictionary..." << std::endl;
    std::ifstream csvFile("./OPTED-Dictionary.csv");

    if (!csvFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return {};
    }

    std::string line;
    std::getline(csvFile, line);

    std::unordered_map<std::string, std::vector<std::string>> wordAndDefinitions;
    std::vector<std::string> temp;
    std::string field;

    while (std::getline(csvFile, line)) {
        std::stringstream s(line);
        std::string word;
        std::vector<std::string> defs;

        for (int i = 0; i < 4; i++) {
            std::getline(s, field, ',');
            if (i == 0) {
                temp.push_back(field);
                word = field;
            }
            else if (i == 3) {
                field.erase(std::remove(field.begin(), field.end(), '"'), field.end());
                temp.push_back(field);
                defs.push_back(field);
            }
        }

        dictionary.push_back(temp);
        for (auto def : defs) {
            wordAndDefinitions[word].push_back(def);
        }
        temp.clear();
    }

    for (const auto& pair : wordAndDefinitions) {
        trie.insert(pair.first, pair.second);
    }

    return dictionary;
}

int main() {
    std::string wordToLookup;
    std::vector<std::string> definitions;
    std::vector<std::vector<std::string>> dictionary;
    Trie trieDictionary;

    dictionary = loadDictionary(dictionary, trieDictionary);

    while (true) {
        std::cout << "\nEnter a word to look up (or type '1' to exit): ";
        std::getline(std::cin, wordToLookup);

        // Check if the user wants to quit.
        if (wordToLookup == "1") {
            std::cout << "Goodbye!" << std::endl;
            break; // Exit the loop.
        }

        // Convert to matching case
        for (char &c : wordToLookup) {
            c = std::tolower(c);
        }

        // Safeguards against empty string if user inputs enter key
        if (!wordToLookup.empty())
            wordToLookup[0] = std::toupper(wordToLookup[0]);

        // Use a linear search to find the word
        auto startLinear = chrono::high_resolution_clock::now();
        definitions = linearSearch(dictionary, wordToLookup);
        auto endLinear = chrono::high_resolution_clock::now();
        auto startTrie = chrono::high_resolution_clock::now();
        std::vector<std::string> trieDefinitions = trieDictionary.search(wordToLookup);
        auto endTrie = chrono::high_resolution_clock::now();

        for (int i = 0; i < definitions.size(); i++) {
            std::cout << i + 1 << ". " << definitions[i] << std::endl;
        }

        // Print out search times for each algorithm
        std::cout << std::endl;
        std::cout << "Linear search time: " << chrono::duration_cast<chrono::microseconds>(endLinear - startLinear).count() << " microseconds" << std::endl;
        std::cout << "Trie search time: " << chrono::duration_cast<chrono::microseconds>(endTrie - startTrie).count() << " microseconds" << std::endl;
    }

    return 0;
}
