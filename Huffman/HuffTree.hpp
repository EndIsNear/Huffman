#ifndef HUFF_TREE_HPP
#define HUFF_TREE_HPP
#include <cstdlib>
#include <iostream>
#include "heap.hpp"

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
		isLeaf = true;
	}
	char val;
	int weigth;
	HuffNode *pLeft, *pRight;
	bool isLeaf;
};

size_t writeNodes(HuffNode* root, FILE * output)
{
	if (root->isLeaf)
		return fwrite(root, sizeof(HuffNode), 1, output) > 0 ? 1 : 0;
	else
		return writeNodes(root->pLeft, output) + writeNodes(root->pRight, output);
}

void writeToFile(HuffNode* root, FILE * output)
{
	fseek(output, 0, SEEK_SET);
	size_t size = 0;
	fwrite(&size, sizeof(size_t), 1, output);
	size = writeNodes(root, output);
	fseek(output, 0, SEEK_SET);
	fwrite(&size, sizeof(size_t), 1, output);
	fseek(output, sizeof(size)+size * sizeof(HuffNode), SEEK_SET);
}

void readFromFile(Heap<HuffNode*>& huffNodes, FILE * input)
{
	fseek(input, 0, SEEK_SET);
	size_t size;
	HuffNode * tmp;

	fread(&size, sizeof(size), 1, input);
	for (size_t i = 0; i < size; ++i)
	{
		tmp = new HuffNode;
		fread(tmp, sizeof(HuffNode), 1, input);
		huffNodes.Push(tmp, tmp->weigth);
	}
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