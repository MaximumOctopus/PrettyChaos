//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>

#define NOMINMAX
#include <windows.h>
#include <string.h>

#include "Utility.h"


namespace Utility
{
	static const std::wstring ShortDays[7] = { L"Sun", L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat" };
	static const std::wstring Months[12] = { L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec" };

	std::wstring GetOpenFileName(int mode)
	{
		OPENFILENAME ofn = { 0 };
		TCHAR szFile[260] = { 0 };
		// Initialize remaining fields of OPENFILENAME structure
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = 0;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		switch (mode)
		{
		case 0:
			ofn.lpstrFilter = _T("PrettyChaos project files\0*.prttychs\0");
			break;
		case 1:
			ofn.lpstrFilter = _T("PNG image files\0*.png\0");
			break;
		case 2:
			ofn.lpstrFilter = _T("Palette files\0*.palette\0");
			break;
		case 3:
			ofn.lpstrFilter = _T("Text files\0*.txt\0");
			break;
		}
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn) == TRUE)
		{
			return std::wstring(&ofn.lpstrFile[0]);
		}

		return L"";
	}

	std::wstring GetSaveFileName(int mode)
	{
		OPENFILENAME ofn = { 0 };
		TCHAR szFile[260] = { 0 };
		// Initialize remaining fields of OPENFILENAME structure
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = 0;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		switch (mode)
		{
		case 0:
			ofn.lpstrFilter = _T("PrettyChaos project files\0*.prttychs\0");
			break;
		case 1:
			ofn.lpstrFilter = _T("PNG image files\0*.png\0");
			break;
		case 2:
			ofn.lpstrFilter = _T("Palette files\0*.palette\0");
			break;
		case 3:
			ofn.lpstrFilter = _T("Text files\0*.txt\0");
			break;
		}
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = 0;

		if (GetSaveFileName(&ofn) == TRUE)
		{
			return std::wstring(&ofn.lpstrFile[0]);
		}

		return L"";
	}

	int CurrentYear()
	{
		struct tm newtime;
		time_t now = time(0);
		#ifdef _CONSOLE
		localtime_s(&newtime, &now);
		#else
		localtime_s(&now, &newtime);	// C++ builder wants the parameters the other way around?!
		#endif

		return newtime.tm_year + 1900;
	}
	
	
	std::wstring GetFileExtension(const std::wstring& file_name)
	{
		size_t index = file_name.rfind(L".");

		if (index != std::wstring::npos)
		{
			std::wstring ext = file_name.substr(index + 1);

			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

			return ext;
		}
		else
		{
			return L"";
		}
	}


	std::wstring ProcessFileName(const std::wstring& file_name)
	{
		if (file_name.find(L"$") != std::wstring::npos)
		{
			std::wstring pfn = file_name;

			struct tm newtime;
			time_t now = time(0);
			#ifdef _CONSOLE
			localtime_s(&newtime, &now);
			#else
			localtime_s(&now, &newtime);	// C++ builder wants the parameters the other way around?!
			#endif

			int mm = newtime.tm_mon + 1;
			int dd = newtime.tm_mday;

			// =========================================================================
			// == System ===============================================================
			// =========================================================================

			if (file_name.find(L"$PC") != std::wstring::npos)
			{
				//pfn = ReplaceString(pfn, L"$PC", WindowsUtility::GetComputerNetName());
			}

			if (file_name.find(L"$User") != std::wstring::npos)
			{
				//pfn = ReplaceString(pfn, L"$User", WindowsUtility::GetUserFromWindows());
			}

			// =========================================================================
			// == Date =================================================================
			// =========================================================================

			if (file_name.find(L"$yyyy") != std::wstring::npos)
			{
				pfn = ReplaceString(pfn, L"$yyyy", std::to_wstring(newtime.tm_year + 1900));
			}

			if (file_name.find(L"$YY") != std::wstring::npos)
			{ 
				std::wstring yy = std::to_wstring(newtime.tm_year + 1900);

				pfn = ReplaceString(pfn, L"$YY", yy.substr(2, 2));
			}

			// =========================================================================

			if (file_name.find(L"$mm") != std::wstring::npos)
			{
				std::wstring mmm = std::to_wstring(mm);

				if (mm < 10)
				{
					mmm = L"0" + mmm;
				}
			
				pfn = ReplaceString(pfn, L"$mm", mmm);
			}

			if (file_name.find(L"$MM") != std::wstring::npos)
			{
				pfn = ReplaceString(pfn, L"$MM", Months[mm]);
			}

			// =========================================================================

			if (file_name.find(L"$dd") != std::wstring::npos)
			{
				std::wstring ddd = std::to_wstring(dd);

				if (dd < 10)
				{
					ddd = L"0" + ddd;
				}
				
				pfn = ReplaceString(pfn, L"$dd", ddd);
			}

			if (file_name.find(L"$DD") != std::wstring::npos)
			{
				pfn = ReplaceString(pfn, L"$DD", ShortDays[newtime.tm_wday]);
			}

			// =========================================================================
			// == Time =================================================================
			// =========================================================================

			if (file_name.find(L"$Th") != std::wstring::npos)
			{
				std::wstring hhh = std::to_wstring(newtime.tm_hour);

				if (newtime.tm_hour < 10)
				{
					hhh = L"0" + hhh;
				}

				pfn = ReplaceString(pfn, L"$Th", hhh);
			}

			// =========================================================================

			if (file_name.find(L"Tm") != std::wstring::npos)
			{
				std::wstring mmm = std::to_wstring(newtime.tm_min);
			
				if (newtime.tm_min < 10)
				{
					mmm = L"0" + mmm;
				}

				pfn = ReplaceString(pfn, L"$Tm", mmm);
			}

			// =========================================================================

			if (file_name.find(L"Ts") != std::wstring::npos)
			{
				std::wstring sss = std::to_wstring(newtime.tm_sec);

				if (newtime.tm_sec < 10)
				{
					sss = L"0" + sss;
				}
			
				pfn = ReplaceString(pfn, L"$Ts", sss);
			}

			// =========================================================================

			return pfn;
		}

		return file_name;
	}


	std::wstring ReplaceString(const std::wstring subject, const std::wstring& search, const std::wstring& replace)
	{
		std::wstring output = subject;

		size_t pos = 0;

		while ((pos = output.find(search, pos)) != std::wstring::npos)
		{
			output.replace(pos, search.length(), replace);

			pos += replace.length();
		}

		return output;
	}
}