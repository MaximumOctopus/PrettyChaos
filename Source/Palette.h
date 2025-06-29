//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include <vector>

#include "Colour.h"
#include "PaletteKey.h"


class Palette
{
	int GradientKeyAt(int);
	int GetNextGradientKey(int);
	int GetKeyType(const std::wstring);

	void NormaliseKeys();

public:

	std::wstring Description = L"";

	int *PaletteR = nullptr;
	int *PaletteG = nullptr;
	int *PaletteB = nullptr;

	int ColourCount = 0;

	std::wstring FileName = L"";        // file name of last load/save

	bool IsRendering = false;

	bool Interleve = false;
	bool InterleveReverse = false;
	int InterleveMode = 0;

	int Steps = 1;
	double Log = 1;
	bool ColourSpace = true;            // false is b/w

	bool TempGradientDirection = false;
	bool TempIsGradient = true;
	Colour TempSingleColour;

	bool GradientDirection = false;     // horizontal
	bool IsGradient = false;
	Colour SingleColour;

	Colour *Colours = nullptr;

	int SelectedKey = 0;

	TBitmap* Gradient;

	std::vector<PaletteKey> Keys;

	Palette(int, const std::wstring);
	~Palette();

	void Clear(bool);

	void SetSize(int);

	void Render();

	void CopyPublic();

	bool Align();

	bool Load(const std::wstring);
	bool Save(const std::wstring);

	void SetFromTemp();
	void CopyToTemp();

	int AddNewKey(int, int, int, bool);
};