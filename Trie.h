#pragma once
#include <iostream>
#include <vector>
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
  vector<string> prefix(string& prefix);
  void pushWords(TrieNode* node, string word, vector<string>& matches);
  void destruct(TrieNode* root);

  ~Trie();
};
