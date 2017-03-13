#ifndef _ENUMFONT_H_
#define _ENUMFONT_H_

#include <vector>
#include <algorithm>
#include <Windows.h>

class EnumFont{
public:
	EnumFont();

	std::vector<std::string> GetFonts();
	void StartEnumFonts();

	int CALLBACK EnumTheFonts(LOGFONT *lpLF, TEXTMETRIC *lpTM, DWORD dwTyp, LPARAM lpData);

private:
	std::vector<std::string> m_fontList;
};



#endif
