#include "CBinTree.h"

void findByEngWord(CBinTree& tree) {
	cout << "Please enter word in english : ";
	string word = "";
	cin.ignore(9000, '\n');
	getline(cin, word);
	tree.findbyEngWord(word);
}

void addWord(CBinTree& tree) {

	tree.addWord();
};

void delWord(CBinTree& tree) {
	cout << "Please enter EngWord that u want to delete : ";
	string engWord = " ";
	cin.ignore(9000, '\n');
	getline(cin, engWord);
	cout << engWord;
	tree.deleteWord(engWord);
}
void showDictionary(CBinTree& tree) {
	tree.showDictionary();
}

bool menu(CBinTree& tree) {

	cout << "\n\t\t\tWellcome to the dictionary" << endl;
	cout <<"Please choose option and press ENTER" << endl;
	cout<< "\t1. Add a new word to the dictionary" << endl;
	cout<< "\t2. Find a word in English" << endl;
	cout<< "\t3. Show all books in library" << endl;
	cout << "\t4. Delete the word" << endl;
	cout<< "\t5. Exit\n";
	cout<<	"Your choice: ";

	int choice = 0;
	cin >> choice;

	switch (choice) {
	case 1: tree.addWord(); break;
	case 2: findByEngWord(tree); break;
	case 3: showDictionary(tree); break;
	case 4: delWord(tree); break;
	case 5: return false;
	}
	return true;
}

int main()
{
	CBinTree tree("dictionary.csv");
	while (menu(tree)) {
		//system("cls");
	}
	return 0;
}

