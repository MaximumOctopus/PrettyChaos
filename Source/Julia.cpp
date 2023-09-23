//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <string>

#include "Julia.h"


Julia::Julia() : Fractal()
{
	ymin = -1.22;
	ymax = 1.22;
	xmin = -2.0;
	xmax = 0.47;
}


Julia::~Julia()
{
}


void Julia::Render()
{
	#ifdef _DEBUG
	int maxit = 0;
	int minit = 9999999;
	#endif

	StartTime = std::chrono::system_clock::now();

	int* NumIterationsPerPixel = new int[max_iterations];

	for (int z = 0; z < max_iterations; z++) NumIterationsPerPixel[z] = 0;




	CalculateRenderTime();

	delete[] NumIterationsPerPixel;

	#ifdef _DEBUG
	debug = L"min_it = " + std::to_wstring(minit) + L", max_it = " + std::to_wstring(maxit);
	#endif
}


void Julia::ResetView()
{
	ymin = -1.22;
	ymax =  1.22;
	xmin = -2.0;
	xmax =  0.47;
}
