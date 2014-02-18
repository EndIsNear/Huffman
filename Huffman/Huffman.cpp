#include "Huffman.h"
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "BinaryTree.hpp"

#define READ_SIZE 1024

struct TreeVal
{
	TreeVal(){}
	TreeVal(char _val, int _weigth)
	{
		val = _val;
		weigth = _weigth;
	}
	char val;
	size_t weigth;
};

int compareTrees(const void* left, const void* right)
{
	TreeVal leftVal = ((BinaryTree<TreeVal>*)left)->GetRoot;
		//, rightVal = ((BinaryTree<TreeVal>*)right)->GetRoot;

	//if (leftVal.weigth < rightVal.weigth)
	//	return -1;
	//if (leftVal.weigth == rightVal.weigth)
	//	return 0;
	//if (leftVal.weigth > rightVal.weigth)
	//	return 1;
}

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

bool buildHuffTree(FILE* input, BinaryTree<TreeVal>& tree)
{
	int chars[256] = { 0 };
	int cnt = 0;

	countChars(input, chars);
	//for (int i = 0; i < 256; ++i)
	//{
	//	std::cout << (char)i << " : " << chars[i] << std::endl;
	//}
	for (int i = 0; i < 256; ++i)
	{
		if (chars[i] > 0)
		{
			++cnt;
		}
	}
	BinaryTree<TreeVal>* nodes = new BinaryTree<TreeVal>[cnt];
	if (!nodes)
	{
		return false;
	}
	for (int i = 0, nodeCnt = 0; i < 256; ++i)
	{
		if (chars[i] > 0)
		{
			nodes[nodeCnt].initRoot(TreeVal(chars[i], i));
			++nodeCnt;
		}
	}
	qsort(nodes, cnt, sizeof(TreeVal), compareTrees);
	return true;
}

bool archive(const char * inputFile, const char* outputFile)
{
    FILE * input,* output;
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
	BinaryTree<TreeVal> huffmanTree;
	buildHuffTree(input, huffmanTree);


    fclose(input);
    fclose(output);
    return true;
}

bool extract(const char* inputFile, const char* outputFile)
{

	return false;
}
