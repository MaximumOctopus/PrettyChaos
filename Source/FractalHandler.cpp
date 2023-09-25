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
}


FractalHandler::~FractalHandler()
{
	delete Fractals[2];
	delete Fractals[1];
	delete Fractals[0];

    Fractals.clear();
}
