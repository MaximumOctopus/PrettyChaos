//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
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
#include "JuliaCos.h"
#include "JuliaSinCos.h"
#include "Mandelbrot.h"
#include "MandelbrotCubic.h"
#include "MandelbrotQuartic.h"
#include "MandelbrotNtic.h"
#include "MandelbrotCos.h"
#include "MandelbrotCosNtic.h"
#include "MartinClassic.h"
#include "MartinAdditive.h"
#include "MartinPositive.h"
#include "MartinSinusoidal.h"


FractalHandler::FractalHandler()
{
	Fractal* dn = new Dragon();
	Fractal* j1 = new Julia();
	Fractal* j2 = new JuliaCubic();
	Fractal* j3 = new JuliaQuartic();
	Fractal* j4 = new JuliaQuintic();
	Fractal* j5 = new JuliaNtic();
	Fractal* j6 = new JuliaCos();
	Fractal* j7 = new JuliaSinCos();
	Fractal* m1 = new Mandelbrot();
	Fractal* m2 = new MandelbrotCubic();
	Fractal* m3 = new MandelbrotQuartic();
	Fractal* m4 = new MandelbrotNtic();
	Fractal* m5 = new MandelbrotCos();
	Fractal* m6 = new MandelbrotCosNtic();
	Fractal* mf = new Martin();
	Fractal* ma = new MartinAdditive();
	Fractal* mp = new MartinPositive();
	Fractal* ms = new MartinSinusoidal();

	Fractals.push_back(j1);
	Fractals.push_back(j2);
	Fractals.push_back(j3);
	Fractals.push_back(j4);
	Fractals.push_back(j5);
	Fractals.push_back(j6);
	Fractals.push_back(j7);

	Fractals.push_back(m1);
	Fractals.push_back(m2);
	Fractals.push_back(m3);
	Fractals.push_back(m4);
	Fractals.push_back(m5);
	Fractals.push_back(m6);

	Fractals.push_back(mf);
	Fractals.push_back(ma);
	Fractals.push_back(mp);
	Fractals.push_back(ms);

	Fractals.push_back(dn);
}


FractalHandler::~FractalHandler()
{
	for (int t = 0; t < Fractals.size(); t++)
	{
		delete Fractals[t];
	}

    Fractals.clear();
}
