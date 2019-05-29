/************************************
*file: Test.cpp
*author: Karyna Dorosh KV-72
*written: 25.05.2019
*last modified: 29.05.2019
************************************/
#include "TextClassifier.h"
#include <Windows.h>
int main() {
	std::vector<std::string> lang = { "French", "English", "Italian", "Spanish"};
	std::vector<TextClassifier> TClassifiers;
	std::ifstream in;
	int NumberFile;
	TextClassifier TCTest;
	unsigned int min = 0;
	unsigned long curClassifier = 0;

	std::cout << "Enter number of test file from 1 to 4: ";
	std::cin >> NumberFile;
	switch (NumberFile) {
	case 1:
		in.open("test1.txt");
		break;
	case 2:
		in.open("test2.txt");
		break;
	case 3:
		in.open("test3.txt");
		break;
	case 4:
		in.open("test4.txt");
		break;
	default:
		std::cout << "\nThere is no file with such number" << std::endl;
		Sleep(2000);
		exit(1);
	}
	if (!in.is_open()) {
		std::cout << "\nFile is not found, sorry:( " << std::endl;
		Sleep(2000);
		exit(1);
	}
	std::cout << "\nLearning from test..." << std::endl;
	TCTest.learn(in);
	in.close();
	
	for (int i = 0; i < lang.size(); i++) {
		std::ifstream in(lang[i] + ".txt");
		std::ofstream out(lang[i] + "_dump.txt");
		if (!in.is_open() || !out.is_open()) {
			std::cout << "\nCannot find file" << std::endl;
			Sleep(2000);
			exit(1);
		}
		std::cout << "Learning " << lang[i] << std::endl;
		TClassifiers.push_back(TextClassifier(lang[i]));
		TClassifiers[i].learn(in);
		TClassifiers[i].dumpProfile(out);
		in.close();
		out.close();
	}
	unsigned long minCl = TClassifiers[0].score(TCTest);
	std::cout << lang[0] << " Distance = " << minCl << std::endl;
	for (int i = 1; i < lang.size(); i++) {
		curClassifier = TClassifiers[i].score(TCTest);
		std::cout << lang[i] << " Distance = " << curClassifier << std::endl;
		if (curClassifier < minCl) {
			minCl = curClassifier;
			min = i;
		}
	}
	std::cout << "\nThe language is  " << TClassifiers[min].category() << std::endl;
	system("pause");
	return 0;
}