
#include <functional>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class CTreeNode
{
public:

	CTreeNode(std::ifstream&);
	CTreeNode();
public:
	CTreeNode *left ;
	CTreeNode *right;
	int Page;
	string EngWord;
	string ItalWord ;
};

class CBinTree
{
public:
	CTreeNode* root;

public:
	CBinTree();
	void insert(CTreeNode*, CTreeNode*);
	void showDictionary();
	void addWord();
	void deleteWord(string);
	void findbyEngWord(string);
	CTreeNode* minValueNode(CTreeNode* node);
	void findNode(CTreeNode*, string, int);
	CTreeNode* deleteWord(CTreeNode*, string);
	CBinTree(string);
};


