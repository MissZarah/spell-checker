#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include "dictionary.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/**
 * Checks if the word is peresent in the dictionary, then it is correctly spelled
 * If the word is misspelled suggestions are presented 
**/
void check_word(const string &word, const Dictionary &dict)
{
    if (dict.contains(word))
    {
        cout << "Correct." << endl;
    }
    else
    {
        vector<string> suggestions = dict.get_suggestions(word);
        if (suggestions.empty())
        {
            cout << "Wrong, no suggestions." << endl;
        }
        else
        {
            cout << "Wrong. Suggestions:" << endl;
            for (const auto &w : suggestions)
            {
                cout << "    " << w << endl;
            }
        }
    }
}
int main()
{
    Dictionary dict;
    string word;
    while (cin >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        check_word(word, dict);
    }
    return 0;
}
