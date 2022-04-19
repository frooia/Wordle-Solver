//
// Created by Lydia Chung on 4/19/22.
//

#include <random>
#include <unordered_set>

using namespace std;

class WordleGenerator {
private:
    constexpr static const float COMMON_WORD_RATE = 0.8;
public:
    int length;
    explicit WordleGenerator(int _length);
    static string randomWord(const vector<string>& wordList);
    static string nonRandomWord(const vector<string>& allWords, const vector<string>& commonWords);
};

/**
 * Constructor
 * @param _length
 */
WordleGenerator::WordleGenerator(int _length) {
    length = _length;
}

/**
 * Generates a completely random word from a word list
 * @param wordList
 * @return
 */
string WordleGenerator::randomWord(const vector<string>& wordList) {
    return wordList[random() % wordList.size()];
}

/**
 * Generates a common or uncommon word based on a likelihood constant
 * @param allWords
 * @param commonWords
 * @return
 */
string WordleGenerator::nonRandomWord(const vector<string> &allWords, const vector<string> &commonWords) {
    if (random() % 100 < (int)(COMMON_WORD_RATE * 100))
        return commonWords[random() % commonWords.size()];
    unordered_set<string> commonWordsSet;
    for (auto & word : commonWords)
        commonWordsSet.insert(word);
    vector<string> uncommonWords;
    for (auto & word : allWords) {
        if (commonWordsSet.find(word) != commonWordsSet.end())
            uncommonWords.push_back(word);
    }
    return uncommonWords[random() % uncommonWords.size()];
}
