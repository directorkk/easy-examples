#include "EnumFont.h"

namespace{
	EnumFont *g_pEnum = NULL;
}

int CALLBACK gEnumTheFonts(LOGFONT *lpLF, TEXTMETRIC *lpTM, DWORD dwTyp, LPARAM lpData)
{
	if(g_pEnum) return g_pEnum->EnumTheFonts(lpLF, lpTM, dwTyp, lpData);
	else return -1;
}

EnumFont::EnumFont()
{
	g_pEnum = this;
}

int CALLBACK EnumFont::EnumTheFonts(LOGFONT *lpLF, TEXTMETRIC *lpTM, DWORD dwTyp, LPARAM lpData)
{
	m_fontList.push_back(lpLF->lfFaceName);
	return 1;
}

std::vector<std::string> EnumFont::GetFonts()
{
	return m_fontList;
}

void EnumFont::StartEnumFonts()
{
	HWND hDesktopWindow = GetDesktopWindow();
	HDC tmphDC = GetDC(hDesktopWindow);
	HDC hDC = CreateCompatibleDC(tmphDC);
	ReleaseDC(hDesktopWindow,tmphDC);

	HRESULT result = EnumFonts(hDC, NULL, (FONTENUMPROC)gEnumTheFonts, NULL);

	DeleteDC(hDC);
}