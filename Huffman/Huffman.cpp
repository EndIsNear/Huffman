#include "Huffman.h"
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <new>
#include "HuffTree.hpp"
#include "heap.hpp"

#define READ_SIZE 1024

void countChars(FILE* input, int* chars)
{
	char buffer[READ_SIZE] = { 0 };
	size_t readSize = 0;
	while (readSize = fread(buffer, sizeof(char), READ_SIZE, input))
	{
		for (size_t cnt = 0; cnt < readSize; ++cnt)
		{
			++chars[buffer[cnt]];
		}
	}
}

HuffNode* buildTree(int * cntChars)
{
	Heap<HuffNode*> huffNodes;
	HuffNode* root = NULL;

	for (int i = 0, cnt = 0; i < 256; ++i)
	{
		if (cntChars[i] > 0)
		{
			HuffNode * tmp;
			tmp = new HuffNode(cntChars[i], NULL, NULL, (char)i);
			
			huffNodes.Push(tmp, cntChars[i]);
			++cnt;
		}
	}

	while (!huffNodes.IsEmpty())
	{
		root = new(HuffNode);
		root->pLeft = huffNodes.Pop();
		root->pRight = huffNodes.Pop();
		root->val = '\0';
		root->weigth = root->pLeft->weigth + root->pRight->weigth;
		if (!huffNodes.IsEmpty())
			huffNodes.Push(root, root->weigth);
	}
	return root;
}

bool archive(const char * inputFile, const char* outputFile)
{
	FILE * input, *output;
	int cntChars[256] = { 0 };
	HuffNode * root;
	size_t size;


	input = fopen(inputFile, "rb");
	if (!input)
	{
		std::cout << "Cannot open file for reading!" << std::endl;
		return false;
	}

	output = fopen(outputFile, "wb");
	if (!output)
	{
		std::cout << "Cannot open file for writing!" << std::endl;
		return false;
	}

	countChars(input, cntChars);
	root = buildTree(cntChars);
	printHuff(root);

	fclose(input);
	fclose(output);
	return true;
}

bool extract(const char* inputFile, const char* outputFile)
{

	return false;
}