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

#include "Palette.h"


class PaletteHandler
{

public:

	std::vector<Palette*> Palettes;

	PaletteHandler();
	~PaletteHandler();
};
