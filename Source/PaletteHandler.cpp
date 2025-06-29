//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include "PaletteHandler.h"

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
