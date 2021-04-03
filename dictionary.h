#ifndef DICTIONARY_H
#define DICTIONARY_H
#define SIZE 25

#include <string>
#include <vector>
#include <unordered_set>
#include "word.h"

class Dictionary
{
public:
	Dictionary();
	/**
	 * checks if a word belongs to a dictioney then it is not missspelled
	 * @param word to check
	 * @return true if the word is present in the disctionary
 	**/
	bool contains(const std::string &word) const;
     /**
	  * find sugesstiongs for missspelled word
	  * @param word written by user
	  * @return vector of suggested
	**/
	std::vector<std::string> get_suggestions(const std::string &word) const;

private:
	std::unordered_set<std::string> words_set;
	std::vector<Word> words[SIZE];
    /**/
	void add_trigram_suggestions(std::vector<std::string> &suggestions, const std::string &word) const;
	int distance(const std::string &w1, const std::string &w2) const;
	void rank_suggestions(std::vector<std::string> &suggestions, const std::string &word) const;

	/* trims the the list of suggestions to only 5 top suggestions */
	void trim_suggestions(std::vector<std::string> &suggestions) const;
};

#endif
