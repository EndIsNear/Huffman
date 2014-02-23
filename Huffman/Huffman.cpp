#include "Huffman.h"
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <new>
#include "HuffTree.hpp"
#include "heap.hpp"
#include "Bitset.h"

#define READ_SIZE 4096

bool getBitsetForChar(const char ch, HuffNode* node, BitSet& bits)
{
	if (node->isLeaf)
	{
		return ch == node->val ? true : false;
	}
	if (getBitsetForChar(ch, node->pLeft, bits))
	{
		bits.addBit(0);
		return true;
	}
	if (getBitsetForChar(ch, node->pRight, bits))
	{
		bits.addBit(1);
		return true;
	}

}

void encodeBuffer(HuffNode* root, const unsigned char * src, BitSet& dest, size_t size)
{
	BitSet * map[256] = { NULL };
	for (size_t i = 0; i < size; ++i)
	{
		if (!map[(int)src[i]])
		{
			map[(int)src[i]] = new BitSet(1);
			getBitsetForChar(src[i], root, *map[(int)src[i]]);
		}
		for (int cnt = 0; cnt < (*map[(int)src[i]]).GetBitCount(); ++cnt)
		{
			dest.addBit((*map[(int)src[i]])[cnt]);
		}
	}
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

void initHeap(FILE * input, Heap<HuffNode*>& huffNodes)
{
	int cntChars[256] = { 0 };
	countChars(input, cntChars);

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
}

HuffNode* fromArrToTree(Heap<HuffNode*>& huffNodes)
{
	HuffNode* root = NULL;
	while (!huffNodes.IsEmpty())
	{
		root = new(HuffNode);
		root->pLeft = huffNodes.Pop();
		root->pRight = huffNodes.Pop();
		root->val = '\0';
		root->isLeaf = false;
		root->weigth = root->pLeft->weigth + root->pRight->weigth;
		if (!huffNodes.IsEmpty())
			huffNodes.Push(root, root->weigth);
	}
	return root;
}

HuffNode* buildTreeFromText(FILE * input)
{
	Heap<HuffNode*> huffNodes;

	initHeap(input, huffNodes);

	return fromArrToTree(huffNodes);
}

HuffNode* buildTreeFromArchive(FILE * input)
{
	Heap<HuffNode*> huffNodes;

	readFromFile(huffNodes, input);

	return fromArrToTree(huffNodes);
}

bool archive(const char * inputFile, const char* outputFile)
{
	FILE * input, *output;
	HuffNode * root;

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

	root = buildTreeFromText(input);
	
	//printHuff(root);
	fseek(input, 0, SEEK_END);
	size_t sizeOFFile = ftell(input);
	BitSet set(sizeOFFile);
	fseek(input, 0, SEEK_SET);
	unsigned char * buffer = new unsigned char[READ_SIZE];
	size_t readLen;
	while (readLen = fread(buffer, sizeof(unsigned char), READ_SIZE, input))
	{
		encodeBuffer(root, buffer, set, readLen);
	}
	fwrite(set.GetData(), sizeof(unsigned char),set.GetBitCount()/8 + 1 , output);

	deleteHuffTree(root);
	delete[] buffer;
	fclose(input);
	fclose(output);
	return true;
}

bool extract(const char* inputFile, const char* outputFile)
{
	FILE * input, *output;
	HuffNode * root;

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
	root = buildTreeFromArchive(input);


	deleteHuffTree(root);
	return false;
}