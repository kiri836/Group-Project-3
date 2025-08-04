#include "Trie.h"
using namespace std;

void Trie::insert(const string& word, const string& definition) {
  TrieNode* letter = root;
  for (const char c : word) {
    int index = c - 'a';
    if (!letter->alphabet[index]) {
      letter->alphabet[index] = new TrieNode();
    }

    letter = letter->alphabet[index];
  }

  letter->endOfWord = true;
  letter->definition = definition;
}

string Trie::search(const string& word) {
  TrieNode* letter = root;
  for (const char c : word) {
    int index = c - 'a';
    if (!letter->alphabet[index]) {
      cout << "Word not found." << endl;
      return "";
    }

    letter = letter->alphabet[index];
  }

  if (letter->endOfWord) {
    return letter->definition;
  }

  return "Word not found.\n";
}
