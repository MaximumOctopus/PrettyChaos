//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <algorithm>
#include <string>

#include "Newton.h"


Newton::Newton() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;

	Var.a = 45;
	Var.b = 2;
	Var.c = -300;

	max_iterations = 10000;

	Name = L"Newton";

	RenderModes.push_back(L"Average");
}


Newton::~Newton()
{
}


void Newton::RenderSS(int hs, int he)
{
}


void Newton::Render(int hs, int he)
{
	StartTime = std::chrono::system_clock::now();

    // to do!!

	CalculateRenderTime();
}


void Newton::ResetView()
{

}
