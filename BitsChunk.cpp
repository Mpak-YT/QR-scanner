#include "BitsChunk.h"

BitsChunk::BitsChunk() {}

BitsChunk::BitsChunk(std::ifstream& file, unsigned offset, unsigned size_inbits)
{
	sizein_bits = size_inbits;
	sizein_bytes = nearest_multiple(size_inbits, 8)/8;
	data = (char*)calloc(sizein_bytes, sizeof(char));
	read_bytes(file, offset);
}

BitsChunk::BitsChunk(BitsChunk&& other)
	: sizein_bits(other.sizein_bits),
	sizein_bytes(other.sizein_bytes),
	data(other.data) 
{
	other.data = nullptr; // Исходный объект лишается ресурса
	other.sizein_bits = 0;
	other.sizein_bytes = 0;
}

BitsChunk :: ~BitsChunk() 
{
	free(data);
}

/*

void BitsChunk::reverse_data()
{
	char buffer;
	int i=size_inbytes;
	for(int j=0; j<size_inbyts/2; j++)
	{
		buffer = data[size_inbyts-i];
		data[size_inbyts-i] = data[i];
		data[i--] = buffer;
	}
}

*/



void BitsChunk::read_bytes(std::ifstream& file,  unsigned offset)
{
	file.seekg(offset, std::ios::beg); 
	
    //file.seek(file, (long)offset, SEEK_SET);
	//for(int i =0; i < sizein_bytes; i++)
		file.read(data, sizein_bytes);
}

//**********************     GETTERS     **********************//
unsigned BitsChunk::get_sizein_bits()
{
	return sizein_bits;
}
unsigned BitsChunk::get_sizein_bytes()
{
	return sizein_bytes;
}
char* BitsChunk::get_data() 
{
	return data;
}

int BitsChunk::chunk_to_int()
{
	int result = 0;
	for(unsigned i = 0; i < sizein_bytes; i++)
		result += *(data+i)*exp<int>(256, i);
	return result;	
}