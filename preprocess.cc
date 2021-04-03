#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using std::string;

std::vector<string> create_trigram(string word);

/**
 * Reads the file dictionary.txt and creates and writes to the file words.txt
 * The resuted file includes the words from 
   the dictionary and their trigrams 
**/
void writeTofile(string filename)
{

  std::fstream infile(filename);
  std::ofstream outfile("words.txt");
  string line;

  while (std::getline(infile, line))
  {
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);

    if (line.size() > 3)
    {
      outfile << line << " ";
      auto trigrams = create_trigram(line);
      outfile << trigrams.size() << " ";
      for (string s : trigrams)
      {
        outfile << s << " ";
      }
    }
    else
    {
      outfile << line << " "
              << "0";
    }

    outfile << std::endl;
  }
}

/**
 * Creates a sortet list of trigram of a word
 * @param word from the dictionary
 * @return a vector containing the trigrams of a word
 * **/
std::vector<string> create_trigram(string word)
{
  std::vector<string> vec;

  for (size_t i = 0; i <= word.length() - 3; i++)
  {

    string result = word.substr(i, 3);
    vec.push_back(result);
  }
  std::sort(vec.begin(), vec.end());
  return vec;
}

int main()
{
  writeTofile("dictionary.txt");
}