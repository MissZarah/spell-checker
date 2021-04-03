#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>

class Word {
public:
	/* Creates a word with the sorted trigrams */
	Word(const std::string& word, const std::vector<std::string>& trigram);
	
	/* Returns the word */
	std::string get_word() const;
	
	/* Returns how many of the trigrams in anotherWordTrigram vector that are present
	 in this word's trigram vector */
	unsigned int get_matches(const std::vector<std::string>& anotherWordTrigram) const;

private: 
     
	 std::string word;
	 std::vector<std::string> trigram;
   
};

#endif
