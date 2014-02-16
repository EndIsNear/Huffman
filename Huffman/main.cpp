#include <iostream>

#include "Utils.h"

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		std::cout << "Too few arguments!" << std::endl;
	}
	else if (argc > 4)
	{
		std::cout << "Too many arguments!" << std::endl;
	}
	else
	{
		if (!strcmp(argv[1], "-a")) //arhivirane
		{
			archive(argv[2], argv[3]);
			
		}
		else if(!strcmp(argv[1], "-u"))//razarhivirane
		{
			extract(argv[2], argv[3]);
		}
		else //error
		{
			std::cout << "1st argument should be \"-a\" or \"-u\"!" << std::endl;
		}
	}
	return 0;
}