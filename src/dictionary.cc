#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <sstream>
#include "word.h"
#include "dictionary.h"

using std::string;
using std::vector;

Dictionary::Dictionary()
{

	std::ifstream infile("../resources/words.txt");
	string line;

	while (std::getline(infile, line))
	{
		std::stringstream ss(line);
		string word;
		ss >> word;
		words_set.insert(word);

		if (word.size() <= SIZE)
		{
			string number;
			ss >> number;
			string trigram;
			vector<string> vec;
			while (ss >> trigram)
			{
				vec.push_back(trigram);
			}
			words[word.length() - 1].push_back(Word(word, vec));
		}
	}
}

bool Dictionary::contains(const string &word) const
{

	auto found = std::find(words_set.begin(), words_set.end(), word);
	return found != words_set.end();
}

vector<string> Dictionary::get_suggestions(const string &word) const
{
	vector<string> suggestions;

	add_trigram_suggestions(suggestions, word);
	rank_suggestions(suggestions, word);
	trim_suggestions(suggestions);

	return suggestions;
}

void Dictionary::add_trigram_suggestions(std::vector<std::string> &suggestions, const std::string &word) const
{

	vector<string> trigrams;
	int len = word.size();
	if (len >= 3 && len <= SIZE)
	{
		for (int i = 0; i <= len - 3; i++)
		{
			string s = word.substr(i, 3);
			trigrams.push_back(s);
		}
	}
	std::sort(trigrams.begin(), trigrams.end());

	int i = 0;
	int j = 0;

	if (word.size() == SIZE)
	{
		i = word.size() - 2;
		j = word.size() - 1;
	}
	else
	{
		i = word.size() - 2;
		j = word.size();
	}

	for (int k = i; k <= j; k++)
	{
		for (const Word &w : words[k])
		{
			if (w.get_matches(trigrams) >= trigrams.size() / 2)
			{
				suggestions.push_back(w.get_word());
			}
		}
	}
}

int Dictionary::distance(const string &w1, const string &w2) const
{

	int m = w1.length();
	int n = w2.length();
	int cost = 0;
	int d[SIZE + 1][SIZE + 1];
	d[0][0] = 0;
	for (int i = 1; i <= m; i++)
		d[i][0] = i;
	for (int i = 1; i <= n; i++)
		d[0][i] = i;

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (w1[i - 1] == w2[j - 1])
				cost = 0;
			else
				cost = 1;

			d[i][j] = std::min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost});
		}
	}

	return d[m][n];
}

void Dictionary::rank_suggestions(std::vector<std::string> &suggestions, const std::string &word) const
{
	vector<std::pair<int, string>> pairs;

	for (const string &w : suggestions)
	{
		int dis = distance(word, w);
		pairs.push_back(std::make_pair(dis, w));
	}

	std::sort(pairs.begin(), pairs.end());
	suggestions.clear();

	for (const auto &pair : pairs)
	{
		suggestions.push_back(pair.second);
	}
}

void Dictionary::trim_suggestions(std::vector<std::string> &suggestions) const
{
	if (suggestions.size() > 5)
	{
		suggestions.resize(5);
	}
}
