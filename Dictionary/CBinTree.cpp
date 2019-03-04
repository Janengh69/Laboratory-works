
#include "CBinTree.h"
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
#include <sstream>
#include <cstdlib> 

CTreeNode::CTreeNode(ifstream& file) {

	string engWord;
	string italWord;
	int page = 0;
	string tmp;
	getline(file, tmp);
	cout <<  tmp << endl;
	stringstream ss(tmp);
	string token;
	int counter = 0;
	while (getline(ss, token, ',')) {
		switch (counter)
		{
		case 0:
			this->EngWord = token;
			break;
		case 1:
			this->ItalWord = token;

			break;
		case 2:
			 this->Page = stoi(token);
			break;
		default:
			break;
		}
		counter++;
	}
}

CTreeNode::CTreeNode()
{
	CTreeNode *left = nullptr;
	CTreeNode *right = nullptr;
	int Page = 0;
	string EngWord = "";
	string ItalWord = "";
}
CBinTree::CBinTree()
{
	root = nullptr;
}
CBinTree::CBinTree(string filename) {

	ifstream file(filename);
	vector<CTreeNode*> nodes;
	while (!file.eof()) {
		CTreeNode* tmp = new CTreeNode(file);
		nodes.push_back(tmp);
	}
	random_shuffle(nodes.begin(), nodes.end());
	root = nodes[(nodes.size() - 1)];
	nodes.pop_back();

	vector<CTreeNode*>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); it++) {
		insert(root, *it);
	}
}
void CBinTree::showDictionary() {

	findNode(root, "", 1);
}

void CBinTree::findNode(CTreeNode *root, string name, int access) {

	if (root == NULL || root == nullptr)
		return;
	if (access == 1) {
		cout << root->EngWord << " " << root->ItalWord << " " << root->Page << endl;
	}
	else
		if (access == 0) {
			if ((root->EngWord.compare(name))) {
				cout << root->ItalWord << " " << root->Page << endl;
				return;
			}
		}
	findNode(root->left, name, access);
	findNode(root->right, name, access);
}

void CBinTree::findbyEngWord(string EngWord) {

	findNode(root, EngWord, 0);
}


void CBinTree::deleteWord(string EngWord) {

	root = deleteWord(root, EngWord);
}

CTreeNode* CBinTree::minValueNode(CTreeNode* node)
{
	CTreeNode* current = node;

	while (current->left != NULL)
		current = current->left;
	return current;
}

CTreeNode* CBinTree::deleteWord(CTreeNode* rt, string key)
{
	if (rt == NULL) return rt;
	if (key.compare(root->EngWord) > 0)
		rt->left = deleteWord(rt->left, key);

	else if (key.compare(rt->EngWord) < 0)
		rt->right = deleteWord(rt->right, key);
	else
	{
		if (rt->left == NULL)
		{
			CTreeNode *temp = rt->right;
			delete rt;
			return temp;
		}
		else if (rt->right == NULL)
		{
			CTreeNode *temp = rt->left;
			delete rt;
			return temp;
		}
		CTreeNode* temp = minValueNode(rt->right);

		rt->EngWord = temp->EngWord;
		rt->right = deleteWord(rt->right, temp->EngWord);
	}
	return rt;
}

void CBinTree::insert(CTreeNode* rt, CTreeNode* node) {
	if (rt->EngWord > node->EngWord) {
		if (rt->left != NULL || rt->left != nullptr) insert(rt->left, node);
		else rt->left = node;
	}
	else
		if (node->EngWord > rt->EngWord) {
			if (rt->right != NULL || rt->right != nullptr) insert(rt->right, node);
			else rt->right = node;
		}
}

void CBinTree::addWord() {

	string engWord;
	string italWord;
	int page = 0;

	CTreeNode *node = new CTreeNode();
	std::cout << "Write the engWord name: " << std::flush;
	std::cin.ignore();
	std::getline(std::cin, engWord);
	std::cout << "Write the italWord: " << std::flush;
	std::getline(std::cin, italWord);
	std::cout << "Write the page: " << std::flush;
	std::cin >> page;
	node->EngWord = engWord;
	node->ItalWord = italWord;
	node->Page = page;
	if (root != nullptr)
		insert(root, node);
	else
		root = node;
}