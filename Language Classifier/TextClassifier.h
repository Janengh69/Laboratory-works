/*************************************
*file: TextClassifier.h
*author: Dorosh Karyna
*written: 25.05.2019
*last modified: 29.05.2019
**************************************/
#include <iostream>
#include <vector>
#include <map>
#include<regex>
#include <fstream>
#include <string>

//score for no match in frequency map
#define MAX_SCORE 150

#define LOWER_NGRAM_LEN	2
#define UPPER_NGRAM_LEN	5
//Category and text length have to be equal and limited
#define CATEGORY_LEN 1000

typedef std::vector<std::pair<std::string, unsigned long>> frequency_map;

class TextClassifier {
public:
	TextClassifier() { setCategory("Unknown"); }
	TextClassifier(const std::string category) { setCategory(category); }

	frequency_map freqs() { return _freqs; }

	std::string category() { return _category; }

	void setCategory(std::string cat) { _category = cat; }

	void learn(std::istream& in);

	void dumpProfile(std::ostream& out);

	void learnfromDump(std::istream& in);

	long int score(const TextClassifier &);

private:
	//internal frequency map
	frequency_map _freqs;
	//internal name of classifer
	std::string _category;
};
bool sorting_method(std::pair<std::string, int> tmp1, std::pair<std::string, int> tmp2);