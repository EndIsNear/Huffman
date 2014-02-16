#include "Utils.h"
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdio.h>
#include "BinaryTree.hpp"
bool archive(const char * inputName, const char* outputName)
{
    FILE * input,* output;
    input = fopen(inputName, "rb");
    if (!input)
    {
        std::cout << "Cannot open file for reading!" << std::endl;
        return false;
    }

    output = fopen(outputName, "rb");
    if (!output)
    {
        std::cout << "Cannot open file for writing!" << std::endl;
        return false;
    }


    fclose(input);
    fclose(output);
    return true;
}

bool extract(const char* input, const char* result)
{

	return false;
}
