#include <cctype>
#include "Trie.h"
using namespace std;

void Trie::insert(const string& word, const vector<string>& definitions) {
  TrieNode* letter = root;
  for (char c : word) {
    c = tolower(c);
    if (c < 'a' || c > 'z')
      continue;

    int index = c - 'a';
    if (!letter->alphabet[index]) {
      letter->alphabet[index] = new TrieNode();
    }

    letter = letter->alphabet[index];
  }

  letter->endOfWord = true;
  letter->definitions = definitions;
}

vector<string> Trie::search(string& word) {
  TrieNode* letter = root;
  for (char c : word) {
    c = tolower(c);
    int index = c - 'a';
    if (!letter->alphabet[index]) {
      cout << "Word not found." << endl;
      return {};
    }

    letter = letter->alphabet[index];
  }

  if (letter->endOfWord) {
    return letter->definitions;
  }

  cout << "Word not found." << endl;
  return {};
}

void Trie::pushWords(TrieNode* node, string word, vector<string>& matches) {
  if (node->endOfWord)
    matches.push_back(word);

  for (int i = 0; i < 26; i++) {
    if (node->alphabet[i]) {
      char c = i + 'a';
      pushWords(node->alphabet[i], word + c, matches);
    }
  }
}

vector<string> Trie::prefix(string& prefix) {
  TrieNode* letter = root;
  for (char c : prefix) {
    c = tolower(c);
    int index = c - 'a';
    if (!letter->alphabet[index]) {
      cout << "No matches for entered prefix." << endl;
      return {};
    }

    letter = letter->alphabet[index];
  }

  vector<string> matchingWords;
  pushWords(letter, prefix, matchingWords);
  return matchingWords;
}

void Trie::destruct(TrieNode* root) {
  if (root == nullptr)
    return;

  for (int i = 0; i < 26; i++)
    if (root->alphabet[i])
      destruct(root->alphabet[i]);

  delete root;
}

Trie::~Trie() {
  destruct(root);
}
