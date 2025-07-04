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

#include <Vcl.ExtCtrls.hpp>


static const int modeRGB = 0;
static const int modeHSV = 1;


struct CombinedColour
{
	int R = 0;
	int G = 0;
	int B = 0;

	int H = 0;
	int S = 0;
	int V = 0;
};


class PaletteKey
{

public:

	int Colour = 0;             // BGR format
	CombinedColour SuperColour;
	int Position = 0;

    int NormalisedPosition = 0;

	int Method = 0;
	int SubMethod = 1;
	int Mode = modeRGB;			// 0 = RGB, 1 = HSV
	int SubParameterR = 0;
	int SubParameterG = 0;
	int SubParameterB = 0;

	bool Locked = false;

	void Reverse()
	{
        Position = 500 - Position;
	}
};