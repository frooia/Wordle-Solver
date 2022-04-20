
/* Sources:
 * Used in findWordHelper(): https://www.geeksforgeeks.org/trie-display-content/
 * Used in insert(), getNode(): https://www.geeksforgeeks.org/trie-insert-and-search/?ref=lbp
 * Used in removeHelper(), isEmpty(): https://www.geeksforgeeks.org/trie-delete/?ref=lbp
*/

#include "Trie.h"
#include <fstream>
#include <sstream>
#include <iomanip>

Trie::Trie()
{
    root = getNode();
    wordLength = 0;
}

Trie::Trie(int _wordLength)
{
    root = getNode();
    wordLength = _wordLength;

    // initialize all sets with complete alphabet
    for (int i = 0; i < wordLength; i++)
    {
        positions.push_back({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I','J','K','L','M','N','O','P','Q',
                             'R','S','T','U','V','W','X','Y','Z'});
    }

    /*------------- Insert Words into Trie -------------*/
    // open word list file with correct size
    string wordsFile = "../word lists/";
    char length = _wordLength + '0';
    wordsFile += length;
    wordsFile += "-letter-words.txt";
    ifstream inFile(wordsFile);
    if (inFile.is_open())
    {
        string input;
        while (getline(inFile, input))
        {
            // get only the word, not new lines
            input = input.substr(0, wordLength);

            // insert word into trie
            insert(input);
        }
    }
    else
        cout << "word file not open" << endl;
    inFile.close();
    inFile.clear();

    /*------------- Set Frequencies -------------*/
    string freqFile = "../frequencies/";
    freqFile += length;
    freqFile += "-letter-frequencies.txt";
    inFile.open(freqFile);
    if (inFile.is_open())
    {
        string input;
        for (int i = 0; i < wordLength; i++)
        {
            // ignore position line
            getline(inFile, input);
            sortedFreq.push_back({});

            // get letters
            for (int j = 0; j < 26; j++)
            {
                getline(inFile, input);
                istringstream line(input);
                string letterStr;
                char letter;
                string freqStr;
                double freq;

                // get letter
                getline(line, letterStr, ' ');
                letter = letterStr[0];

                // get frequency
                getline(line, freqStr, '\n');
                freq = stod(freqStr);

                // insert letter and frequency into frequency mapping
                sortedFreq[i].push_back(make_pair(freq, letter));
            }
        }
    }
    else
        cout << "frequency file not open" << endl;

    // sort frequecy in descending order according to first element of pair
    for (int i = 0; i < sortedFreq.size(); i++)
        sort(sortedFreq[i].rbegin(), sortedFreq[i].rend());
}

void Trie::insert(string key)
{
    TrieNode* current = root;

    for (int i = 0; i < key.size(); i++)
    {
        // convert character into index in children array
        int index = key[i] - 'A';

        // if next letter doesn't exist, insert it
        if (!current->children[index])
            current->children[index] = getNode();

        // move on to next letter
        current = current->children[index];
    }

    // reached end of word
    current->endOfWord = true;
}

Trie::TrieNode* Trie::getNode()
{
    TrieNode* current = new TrieNode;
    current->endOfWord = false;
    for (int i = 0; i < 26; i++)
        current->children[i] = nullptr;
    return current;
}

void Trie::updateSets(vector<pair<char, int>> feedback)
{
    for (int i = 0; i < wordLength; i++)
    {
        // green letter
        if (feedback[i].second == 1)
        {
            // letter is for sure in that position, could be in other positions too
            // remove all letters from the set corresponding to position i and keep only the green letter there
            // don't alter other sets
            positions[i].clear();
            positions[i].insert(feedback[i].first);
            lettersInWord.insert(feedback[i].first);
        }
        // yellow letter
        if (feedback[i].second == 2)
        {
            // letter not in that position, but is elsewhere
            // remove that specific letter from position i's possibilities
            positions[i].erase(feedback[i].first);
            lettersInWord.insert(feedback[i].first);
        }
        // grey letter
        if (feedback[i].second == 3)
        {
            /* this is to account for the case in which one letter is colored green/yellow and grey in a guess, meaning that
            the guess contains an excess of the letter but the letter does appear at least once. rather than delete the letter
            from all positions because it is grey, if it has been colored yellow/green before, it only removes it from that
            position colored grey */

            // if letter has never been colored yellow or green before, can safely remove from all sets
            if (lettersInWord.count(feedback[i].first) == 0)
            {
                for (int j = 0; j < wordLength; j++)
                    positions[j].erase(feedback[i].first);
            }
            // else if has been yellow or green before, only remove from this position
            else
                positions[i].erase(feedback[i].first);
        }
    }
}

string Trie::guessNoFeedback()
{
    return findWord();
}

string Trie::generateGuess(vector<pair<char, int>> feedback)
{
    updateSets(feedback);
    return findWord();
}

bool Trie::isEmpty(TrieNode* current)
{
    // got through children
    for (int i = 0; i < 26; i++)
    {
        // if not null, return false -- not empty
        if (current->children[i])
            return false;
    }
    return true;
}

void Trie::remove(string key)
{
    removeHelper(root, key);
}

Trie::TrieNode* Trie::removeHelper(TrieNode* current, string key, int depth)
{
    // empty tree
    if (!current)
        return nullptr;

    // at end of word
    if (depth == key.size())
    {
        // should no longer be end of word
        if (current->endOfWord)
            current->endOfWord = false;

        // if it is not a prefix of any other words - can safely delete
        if (isEmpty(current))
        {
            delete current;
            current = nullptr;
        }

        return current;
    }

    // traverse until at end of word
    int index = key[depth] - 'A';
    current->children[index] = removeHelper(current->children[index], key, depth + 1);

    // if no children and not end of other word, delete
    if (isEmpty(current) && !current->endOfWord)
    {
        delete current;
        current = nullptr;
    }

    return current;
}

bool Trie::containsAllLeters(string key)
{
    int matches[lettersInWord.size()];

    int level = 0;
    // go through all yellow and green letters
    for (auto iter = lettersInWord.begin(); iter != lettersInWord.end(); iter++)
    {
        // go through word
        for (int i = 0; i < key.size(); i++)
        {
            // if match, mark it
            if (key[i] == *iter)
                matches[level] = 1;
        }
        level++;
    }
    // go through array of matches
    for (auto element : matches)
    {
        // if no match, return false
        if (element != 1)
            return false;
    }
    return true;
}

string Trie::findWordHelper(TrieNode* current, char str[], int level)
{
    // at end of word, return string
    if (current->endOfWord)
    {
        str[level] = '\0';
        return str;
    }
    // included if statement to not through exception is level >= wordlength
    if (level < wordLength)
    {
        // go through alphabet
        for (int i = 0; i < 26; i++)
        {
            // find highest frequency letter for that position and check if it is a possible letter for that position
            // and check if that letter will lead to an actual word
            if ((positions[level].count(sortedFreq[level][i].second) != 0) && (current->children[sortedFreq[level][i].second - 'A']))
            {
                // add the letter
                str[level] = sortedFreq[level][i].second;
                // find best guess
                string guess = findWordHelper(current->children[sortedFreq[level][i].second - 'A'], str, level + 1);
                // if found valid word and that word contains all the previously marked yellow and green letters, return it
                if (guess != "return" && containsAllLeters(guess))
                    return guess;
            }
        }
    }
    // "return" represents if was unable to find a word for that branch -- signal to go up a level
    return "return";
}

string Trie::findWord()
{
    char str[wordLength + 1];
    return findWordHelper(root, str, 0);
}