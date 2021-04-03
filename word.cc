#include <string>
#include <vector>
#include "word.h"

using std::string;
using std::vector;

Word::Word(const string &word, const vector<string> &trigram) : word(word), trigram(trigram) {}

string Word::get_word() const
{
	return word;
}

unsigned int Word::get_matches(const vector<string> &anotherWordTrigram) const
{

	int count = 0;

	for (const std::string &w1 : anotherWordTrigram)
	{
		for (const std::string &w2 : trigram)
		{

			if (w1 == w2)
			{
				count++;
			}
			else if (w1 < w2)
			{
				break;
			}
		}
	}

	return count;
}
