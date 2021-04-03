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
	 * Checks if a word belongs to a dictioney then it is not missspelled
	 * @param word to check
	 * @return true if the word is present in the disctionary
 	**/
	bool contains(const std::string &word) const;

	/**
	  * Find sugesstiongs for missspelled word
	  * @param word written by user
	  * @return vector of suggested spell corrections
	**/
	std::vector<std::string> get_suggestions(const std::string &word) const;

private:
	std::unordered_set<std::string> words_set;

	// Ignore words longer than 25 letters
	std::vector<Word> words[SIZE];

	/*The words which contain at least half of the “trigrams” of the misspelled word are kept*/
	void add_trigram_suggestions(std::vector<std::string> &suggestions, const std::string &word) const;

	/* Calculate the “Levenshtein distance” from the misspelled word to the candidate word*/
	int distance(const std::string &w1, const std::string &w2) const;

	/*Rank the suggestion from closest to the word to furthest*/
	void rank_suggestions(std::vector<std::string> &suggestions, const std::string &word) const;

	/* Trims the the list of suggestions to only 5 top suggestions */
	void trim_suggestions(std::vector<std::string> &suggestions) const;
};

#endif
