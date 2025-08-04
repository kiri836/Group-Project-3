#pragma once
#include <iostream>
using namespace std;

struct TrieNode {
  bool endOfWord;
  string definition;
  TrieNode* alphabet[26];

  TrieNode() {
    endOfWord = false;
    definition = "";
    for (auto& letter : alphabet)
      letter = nullptr;
  }
};

class Trie {
private:
  TrieNode* root;

public:
  Trie() {
    root = new TrieNode();
  }

  void insert(const string& word, const string& definition);
  string search(const string& word);
};
