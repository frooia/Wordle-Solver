
#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
#include <map>
#include <unordered_map>
using namespace std;

class Trie {
public:
    Trie();
    Trie(int wordLength);
    struct TrieNode {
        TrieNode* children[26];
        bool endOfWord;
    };
    string guessNoFeedback(); // use for first guess or invalid guess (no feedback to give)
    string generateGuess(vector<pair<char, int>> feedback); // use when have feedback
    void remove(string key); // use if invalid guess - remove word from trie
private:
    // attributes
    int wordLength;
    TrieNode* root;
    vector<unordered_set<char>> positions; // represents possible letters for each position
    vector<vector<pair<double, char>>> sortedFreq; // used to get highest frequency letter for each position
    unordered_set<char> lettersInWord; // keep track of what letters colored yellow or green

    // funtions
    bool containsAllLeters(string key); // see if guess contains all letters previously marked yellow or green - to optimize
    bool isEmpty(TrieNode* current); // if node has no children
    TrieNode* removeHelper(TrieNode* current, string key, int depth = 0); // remove node if considered invalid guess
    void insert(string key); // insert node into trie
    TrieNode* getNode(); // make new node
    void updateSets(vector<pair<char, int>> feedback); // update position sets according to feedback
    string findWord(); // make best guess of word
    string findWordHelper(TrieNode* current, char str[], int level); // helper to make guess
};
