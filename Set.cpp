//
// Created by Lydia Chung on 4/19/22.
//
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Set {
private:
    unordered_set<string> fullSet;
    int length;

public:
    explicit Set(int wordLength);
    void generate(const vector<string> &wordList);
    void update(const vector<pair<char, int>>& feedback);
    string guess();

};

/**
 * Constructor
 * @param wordLength
 */
Set::Set(int wordLength) {
    fullSet = unordered_set<string>();
    length = wordLength;
}

/**
 * Puts every word in wordList into the set at every index of fullSet
 * @param wordList
 */
void Set::generate(const vector<string> &wordList) {
    for (int i = 0; i < length; i++) {
        for (auto & word : wordList) {
            fullSet.insert(word);
        }
    }
}

/**
 * Removes potential Wordle guesses from fullSet based on feedback
 * @param feedback
 */
void Set::update(const vector<pair<char, int>> &feedback) {
    for (int i = 0; i < length; i++) {
        // Green
        if (feedback[i].second == 1) {
            // Remove every word that does not contain that letter at that location
            for (auto it = fullSet.begin(); it != fullSet.end(); ) {
                if (it->at(i) != feedback[i].first)
                    fullSet.erase(it);
                else
                    ++it;
            }
        }
        // Yellow
        else if (feedback[i].second == 2) {
            for (auto it = fullSet.begin(); it != fullSet.end(); ) {
                // Check the word to see if it contains that letter
                string word = *it;
                bool hasLetter = false;
                for (int j = 0; j < length; j++) {
                    if (i == j)
                        continue;
                    if (word[j] == feedback[i].first)
                        hasLetter = true;
                }
                // If the word doesn't have that letter, remove it from the candidates
                if (!hasLetter)
                    fullSet.erase(it);
                else
                    ++it;
            }
        }
        // Gray
        else if (feedback[i].second == 3) {
            // Remove every word that contains that letter
            for (auto it = fullSet.begin(); it != fullSet.end(); ) {
                if (it->find(feedback[i].first) != string::npos)
                    fullSet.erase(it);
                else
                    ++it;
            }
        }
    }
}

/**
 * Generates a random word guess from fullSet
 * @return
 */
string Set::guess() {
    return *fullSet.begin();
}
