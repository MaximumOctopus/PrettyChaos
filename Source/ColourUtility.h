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

#include <algorithm>
#include <string>
#include <System.hpp>

#include "Colour.h"


namespace ColourUtility
{
	System::UnicodeString BGRtoRGBHex(int);

	void BGRtoHSV(int rgb, int &H, int &S, int &V);
	void RGBtoHSV(int rgb, int &H, int &S, int &V);
	void HSVtoRGB(int H, int S, int V, int &R, int &G, int &B);

	int RandomBGR();
    int RandomBGRFromBGR(int);

	Colour LinearInterpolate(const Colour&, const Colour&, double);
}
