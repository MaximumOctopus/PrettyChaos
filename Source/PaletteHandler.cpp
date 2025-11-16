//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <fstream>
#include <Windows.h>

#include "PaletteHandler.h"
#include "Utility.h"

PaletteHandler *GPaletteHandler;


PaletteHandler::PaletteHandler()
{
	Palette* p1 = new Palette(500, L"Main");
	Palette* p2 = new Palette(500, L"Background");

	Palettes.push_back(p1);
    Palettes.push_back(p2);
}


PaletteHandler::~PaletteHandler()
{
	delete Palettes[1];
	delete Palettes[0];
}


void PaletteHandler::UpdatePaletteList(const std::wstring path)
{
	AvailablePalettes.clear();

	std::wstring tmp = path + L"*";

	WIN32_FIND_DATAW file;

	HANDLE search_handle = FindFirstFileW(tmp.c_str(), &file);

	if (search_handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
			}
			else
			{
				std::wstring s = file.cFileName;

				AvailablePalettes.push_back(Utility::RemoveExtension(s));
			}

		} while (FindNextFileW(search_handle, &file));

		FindClose(search_handle);
	}
}
