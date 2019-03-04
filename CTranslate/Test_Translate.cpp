/*!
 * file: Test_Translate.cpp
 * Tests for Ctransalte class
 * written: 19/02/2019
 * last modified: 21/02/2019
 * created: Dorosh Karuna KV-72
 */
#include "CTranslate.h"

int main() {
	CTranslate temp;
	std::vector<CTranslate> vs;

	char filename[] = "input.csv";
	temp.LoadFromCSV(filename, vs);

	std::cout << "jump in Italian will be ";
	TranslateEng(vs, "jump");

	std::cout << "\nDictionary with deleted word lazy: " << std::endl;
	DelByEng(vs, "lazy");
	ListAll(vs);

	SortByIta(vs);
	std::cout << "\n\nSorted be Italian words: \n";
	ListAll(vs);

	std::cout << "Pigro in English will be ";
	TranslateIta(vs, "pigro");

	SortByEng(vs);
	std::cout << "Sorted be Eng words: \n";
	ListAll(vs);

	std::cout << "\n\nDictionary with deleted word marrone: " << std::endl;
	DelByIta(vs, "marrone");
	ListAll(vs);


	std::cout << std::endl;
	system("pause");
	return 0;
}