#pragma once
#include <fstream>
#include "Math.h"

class BitsChunk
{
private:
	unsigned sizein_bits;
	unsigned sizein_bytes;
	char* data;
public:
BitsChunk();
BitsChunk(std::ifstream& file, unsigned offset, unsigned size_inbits);
BitsChunk(BitsChunk&& other);
~BitsChunk();


//void reverse_data();

void read_bytes(std::ifstream& file,  unsigned offset);

unsigned get_sizein_bytes();
unsigned get_sizein_bits();
char* get_data();
int chunk_to_int();
};
