//
// Created by Lydia Chung on 4/19/22.
//
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

class Set {
private:
    unordered_set<string> fullSet;
    constexpr static const float COMMON_WORD_RATE = 0.8;
public:
    int length;
    inline explicit Set(int wordLength);
    inline void generate(const vector<string> &wordList);
    inline void update(const vector<pair<char, int>>& feedback);
    inline string randomGuess();
    inline string nonRandomGuess(const unordered_set<string>& commonWords);
};

/**
 * Constructor with wordLength
 * @param wordLength
 */
Set::Set(int wordLength) {
    fullSet = unordered_set<string>();
    length = wordLength;
}

/**
 * Puts every word in wordList into fullSet
 * @param wordList
 */
void Set::generate(const vector<string> &wordList) {
    fullSet.reserve(wordList.size());
    for (const string& word : wordList) {
        fullSet.insert(word);
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
                string currWord = *it;
                if (currWord[i] != feedback[i].first) {
                    it = fullSet.erase(it);
                } else {
                    ++it;
                }
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
            // Remove the guessed word
            string guess;
            for (auto & p : feedback)
                guess.push_back(p.first);
            fullSet.erase(guess);
        }
        // Gray
        else if (feedback[i].second == 3) {
            // Remove every word that contains that letter
            for (auto it = fullSet.begin(); it != fullSet.end(); ) {
                string currWord = *it;
                if (currWord.find(feedback[i].first) != string::npos) {
                    it = fullSet.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}

/**
 * Generates a random word guess from fullSet
 * @return
 */
string Set::randomGuess() {
    int rand = (int)(random() % fullSet.size());
    auto it = fullSet.begin();
    advance(it, rand);
    return *it;
}

/**
 * Generates a common or uncommon word guess based on a likelihood constant
 * @param commonWords
 * @return
 */
string Set::nonRandomGuess(const unordered_set<string> &commonWords) {
    // Separate fullSet into common and uncommon words
    unordered_set<string> commonViable, uncommonViable;
    for (auto & word : fullSet) {
        if (commonWords.find(word) != commonWords.end())
            commonViable.insert(word);
        else
            uncommonViable.insert(word);
    }
    // Generate a random guess from the chosen set
    int rand;
    unordered_set<string>::iterator it;
    if (random() % 100 < (int)(COMMON_WORD_RATE * 100)) {
        rand = (int)(random() % commonViable.size());
        it = commonViable.begin();
    } else {
        rand = (int)(random() % uncommonViable.size());
        it = uncommonViable.begin();
    }
    advance(it, rand);
    return *it;
}
