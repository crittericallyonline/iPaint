#ifndef FONT_HPP
#define FONT_HPP

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"

#include <string>
#include <fstream>

class Font
{
public:
    Font(std::string fontFilePath);
	uint8_t* fontDataBuf;
    ~Font();
};

Font::Font(std::string fontFilePath)
{
	std::ifstream inputFileStream(fontFilePath, std::ios::binary);
	inputFileStream.seekg(0, std::ios::end);
	auto&& size = inputFileStream.tellg();
	inputFileStream.seekg(0, std::ios::beg);
	new uint8_t[static_cast<size_t>(size)];
	inputFileStream.read((char*)fontDataBuf, size);
}

Font::~Font()
{
	delete fontDataBuf;
}
#endif//FONT_HPP