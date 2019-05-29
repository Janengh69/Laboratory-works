/************************************
*file: TextClassifier.cpp
*author: Karyna Dorosh KV-72
*written: 25.06.2019
*last modified: 29.05.2019
************************************/
#include "TextClassifier.h"

void TextClassifier::learn(std::istream & in) {

	std::map<std::string, unsigned long> NGramMap;
	const std::regex re("[\\w\']+");
	std::smatch result;
	std::string temp_buff = "";
	std::map<std::string, unsigned long>::iterator it_map;

	while (in >> temp_buff) {
		if (regex_search(temp_buff, result, re)) {
			temp_buff = result.str(0);
			if (!temp_buff.empty()) {
				int NgramLen = LOWER_NGRAM_LEN;
				while (NgramLen <= UPPER_NGRAM_LEN) {
					std::string word = "_" + temp_buff;
					int i = 0;
					while ( i < word.length()) {
						std::string temp = (word + "____").substr(i, NgramLen);
						if (NGramMap.count(temp) == 0) {
							if (NGramMap.size() >= CATEGORY_LEN) {
								i++;
								continue;
							}
							NGramMap.insert(std::pair<std::string, unsigned long>(temp, 1));
						}
						else {
							auto iter = NGramMap.find(temp);
							iter->second++;
						}
						i++;
					}
					NgramLen++;
				}
			}
		}
	}
	
	it_map = NGramMap.begin();
	while(it_map != NGramMap.end()){
		_freqs.push_back(*it_map);
		it_map++;
	}
	sort(_freqs.begin(), _freqs.end(), &sorting_method);
}

bool sorting_method(std::pair<std::string, int> tmp1, std::pair<std::string, int> tmp2) { return tmp1.second > tmp2.second; }

void TextClassifier::dumpProfile(std::ostream & out){
	out << "Dump: " << _category << std::endl;
	for (auto freq : _freqs)
		out << freq.first << " " << freq.second << std::endl;
}

void TextClassifier::learnfromDump(std::istream & in){
	int numb;
	std::string NGram_str;
	char temp_buff[256];
	std::pair<std::string, unsigned long> tempNGram;
	in.getline(temp_buff, 256);
	while (in >> NGram_str && in >> numb) {
		tempNGram.first = NGram_str;
		tempNGram.second = numb;
		_freqs.push_back(tempNGram);
	}
}

long int TextClassifier::score(const TextClassifier &score_with) {
	long int score = 0;
	bool matches_found = false;
	int counter1 = 0;
	for (auto freq : _freqs) {
		int counter2 = 0;
		matches_found = false;
		for (auto j : score_with._freqs) {
			if (freq.first == j.first) {
				score += abs(counter1 - counter2);
				matches_found = true;
				break;
			}
			counter2++;
		}
		if (!matches_found)
			score += MAX_SCORE;
		counter1++;
	}
	return score;
}