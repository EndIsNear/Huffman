#ifndef HUFF_TREE_HPP
#define HUFF_TREE_HPP
#include <cstdlib>
#include <iostream>

struct HuffNode
{
	HuffNode()
	{
		pLeft = pRight = NULL;
	}
	HuffNode(int _weigth, HuffNode* _left = NULL, HuffNode* _right = NULL, char _val = '\0')
	{
		val = _val;
		weigth = _weigth;
		pLeft = NULL;
		pRight = NULL;
	}
	char val;
	int weigth;
	HuffNode *pLeft, *pRight;
};

int compareNodes(const void* left, const void* right)
{
	return ((HuffNode*)left)->weigth - ((HuffNode*)right)->weigth;
}

void printHuff(HuffNode* root)
{
	if (root == NULL)
		return;
	std::cout << "([" << root->val << ":" << root->weigth << "]";
	if (root->pLeft || root->pRight)
	{
		printHuff(root->pLeft);
		std::cout << ",";
		printHuff(root->pRight);
	}
	std::cout << ")";
}


void deleteHuffTree(HuffNode* root)
{
	if (root == NULL)
		return;
	deleteHuffTree(root->pLeft);
	deleteHuffTree(root->pRight);
	delete root;
}

#endif //HUFF_TREE_HPP