//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include "FractalHandler.h"

#include "Constants.h"
#include "Julia.h"
#include "JuliaCubic.h"
#include "Mandelbrot.h"
#include "Martin.h"


FractalHandler::FractalHandler()
{
	Fractal* ja = new Julia();
	Fractal* jc = new JuliaCubic();
	Fractal* mt = new Mandelbrot();
	Fractal* mn = new Martin();

	Fractals.push_back(ja);
	Fractals.push_back(jc);
	Fractals.push_back(mt);
	Fractals.push_back(mn);

	for (int t = 0; t < __PaletteCount; t++)
	{
		int colour = std::floor(((double)t / __PaletteCount) * 255);

		Palette[t] = colour + (colour << 8) + (colour << 16);
	}

	Palette[__PaletteInfinity] = 0x000000;
}


FractalHandler::~FractalHandler()
{
	delete Fractals[3];
	delete Fractals[2];
	delete Fractals[1];
	delete Fractals[0];

    Fractals.clear();
}
