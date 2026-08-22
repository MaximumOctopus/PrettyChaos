//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2026
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

	p1->PatternLive.DrawMode = DrawModeOption::kGradient;

	p2->PatternLive.DrawMode = DrawModeOption::kSingleColour;
	p2->PatternLive.GridColourOff = 0xffffff;
    p2->PatternLive.GridColourOn = 0x00448822;

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


void PaletteHandler::ShiftPaletteLeft(int index)
{
    Palettes[index]->ShiftLeft();
}


void PaletteHandler::ShiftPaletteRight(int index)
{
	Palettes[index]->ShiftRight();
}


int PaletteHandler::DrawModeToInt(DrawModeOption dmo)
{
	switch (dmo)
	{
	case DrawModeOption::kSingleColour:
		return 0;
	case DrawModeOption::kGradient:
		return 1;
	case DrawModeOption::kGrid:
		return 2;
	case DrawModeOption::kGridGradient:
		return 3;
	}

    return 0;
}


DrawModeOption PaletteHandler::IntToDrawMode(int dmo)
{
	switch (dmo)
	{
	case 0:
		return DrawModeOption::kSingleColour;
	case 1:
		return DrawModeOption::kGradient;
	case 2:
		return DrawModeOption::kGrid;
	case 3:
		return DrawModeOption::kGridGradient;
	}

	return DrawModeOption::kSingleColour;
}
