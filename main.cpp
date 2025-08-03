#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<std::string> linearSearch(std::vector<std::vector<std::string>> dictionary, std::string word){
    std::vector<std::string> definitions;
    for (std::vector<std::string> entry : dictionary){
        if(entry[0] == word){
            definitions.push_back(entry[1]);
            definitions.back().erase(std::remove(definitions.back().begin(), definitions.back().end(), '"'), definitions.back().end());
        }
    }
    return definitions;
}

std::vector<std::vector<std::string>> loadDictionary(std::vector<std::vector<std::string>> &dictionary){
    std::ifstream csvFile("./OPTED-Dictionary.csv");
    std::string line;
    std::vector<std::string> temp;
    while (std::getline(csvFile, line)){
        std::stringstream s(line);
        for (int i = 0; i < 4; i++){
            std::getline(s, line, ',');
            if (i == 0 || i == 3){
                temp.push_back(line);
            }
            line.clear();
        }
        dictionary.push_back(temp);
        temp.clear();
    }
    return dictionary;
}

int main() {
    std::string wordToLookup;
    std::vector<std::string> definitions;
    std::vector<std::vector<std::string>> dictionary;

    dictionary = loadDictionary(dictionary);

    while (true) {
        std::cout << "\nEnter a word to look up (or type 'quit' to exit): ";
        std::getline(std::cin, wordToLookup);

        // Convert to matching case
        for (char &c : wordToLookup) {
            c = std::tolower(c);
        }
        wordToLookup[0] = std::toupper(wordToLookup[0]);

        // Check if the user wants to quit.
        if (wordToLookup == "Quit") {
            break; // Exit the loop.
        }

        // Use a linear search to find the word
        definitions = linearSearch(dictionary, wordToLookup);
        // <insert other search>


        for (int i = 0; i < definitions.size(); i++){
            std::cout << i+1 << ". " << definitions[i] << "\n";
        }
    }

    return 0;
}