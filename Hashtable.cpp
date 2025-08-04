#include "Hashtable.h"

// Loads all the words from the dictionary into the hashtable
void HashTable::loadWords(std::vector<std::vector<std::string>>& dictionary) {
    for (std::vector<std::string> entry : dictionary){
       	int index = hashingFunc(entry[0]);
       	buckets[index].emplace_back(entry);
    }
}

    // Retrieves the definition for a given word
std::vector<std::string> HashTable::search(std::string& word) {
   	std::vector<std::string> empty;
    int index = hashingFunc(word);
       
    // Search for the word in the corresponding list
    for (std::vector<std::string> entry : buckets[index]) {
        if (entry[0] == word) {
            return entry;
        }
    }
    return empty;
}
