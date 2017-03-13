#include "EnumFont.h"
#include <iostream>

int main(int argc, char** argv)
{
	EnumFont *enumFont = new EnumFont();
	enumFont->StartEnumFonts();

	std::vector<std::string> fonts = enumFont->GetFonts();
	for(unsigned int i=0 ; i<fonts.size() ; i++){
		std::cout << fonts[i].c_str() << std::endl;
	}

	return 0;
}