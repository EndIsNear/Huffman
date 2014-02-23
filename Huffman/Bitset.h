#ifndef BITSET_H
#define BITSET_H
#include <cstdlib>
#include <cstring>

class BitSet 
{
	unsigned char * data;
	size_t bits, size;

	void Set(size_t index, bool val)
	{
		if (val)
			data[index / 8] = data[index / 8] | (1 << (7 - index % 8));
	}

public:
	BitSet(size_t size = 1024)
	{
		this->bits = 0;
		this->data = new unsigned char[size];
		memset(this->data, 0, size);
	}

	void addBit(short val)
	{
		this->Set(bits, val);
		this->bits++;
	}

	unsigned char * GetData()
	{
		return this->data;
	}

	bool isFull()
	{
		return this->size == this->bits * 8;
	}

	bool operator[](size_t index)
	{
		return !!(data[index / 8] & (1 << (7 - index % 8)));
	}

	size_t GetBitCount() const
	{
		return this->bits;
	}

	~BitSet() 
	{
		delete[] this->data;
	}
};

#endif //BITSET_H