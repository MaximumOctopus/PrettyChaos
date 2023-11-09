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
#include "Dragon.h"
#include "Julia.h"
#include "JuliaCubic.h"
#include "JuliaQuartic.h"
#include "JuliaQuintic.h"
#include "JuliaNtic.h"
#include "Mandelbrot.h"
#include "MartinClassic.h"
#include "MartinAdditive.h"
#include "MartinPositive.h"
#include "MartinSinusoidal.h"


FractalHandler::FractalHandler()
{
	Fractal* dn = new Dragon();
	Fractal* ja = new Julia();
	Fractal* jc = new JuliaCubic();
	Fractal* jq = new JuliaQuartic();
	Fractal* jn = new JuliaQuintic();
	Fractal* jx = new JuliaNtic();
	Fractal* mt = new Mandelbrot();
	Fractal* mc = new Martin();
	Fractal* ma = new MartinAdditive();
	Fractal* mp = new MartinPositive();
	Fractal* ms = new MartinSinusoidal();

	Fractals.push_back(dn);
	Fractals.push_back(ja);
	Fractals.push_back(jc);
	Fractals.push_back(jq);
	Fractals.push_back(jn);
	Fractals.push_back(jx);
	Fractals.push_back(mt);
	Fractals.push_back(mc);
	Fractals.push_back(ma);
	Fractals.push_back(mp);
	Fractals.push_back(ms);
}


FractalHandler::~FractalHandler()
{
	for (int t = 0; t < Fractals.size(); t++)
	{
		delete Fractals[t];
	}

    Fractals.clear();
}
