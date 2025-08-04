#pragma once
#include <iostream>
using namespace std;

struct TrieNode {
  bool endOfWord;
  vector<string> definitions;
  TrieNode* alphabet[26];

  TrieNode() {
    endOfWord = false;
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

  void insert(const string& word, const vector<string>& definitions);
  vector<string> search(string& word);
  void destruct(TrieNode* root);

  ~Trie();
};
