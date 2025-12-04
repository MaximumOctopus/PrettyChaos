//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// based on code from "Computers and Chaos" for the Amiga by Conrad Bessant
// https://www.jolinton.co.uk/Mathematics/Hopalong_Fractals/Text.pdf
// also know as Hopalong fractals
// http://www.lantersoft.ch/experiments/hopalong/


#include <algorithm>
#include <string>

#include "Constants.h"
#include "Fast.h"
#include "MartinClassic.h"


Martin::Martin() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;
	AcceptsVarD = true;

	QPM = QuickParameterMode::kABPlusFine;

	AcceptsZoom = false;

	// we need a LOT of iterations here because we're not calculating a function on a per pixel basis,
	// but bouncing around the screen hitting pixels as we go
	Defaults.Set(1, 1000000, 4, 45, 2, -300, 1, 0);

	Name = L"Martin";

	RenderModes.push_back(L"Average");
	RenderModes.push_back(L"Time");
	RenderModes.push_back(L"Distance");

	NameA = L"a";
	NameB = L"b";
	NameC = L"c";
	NameD = L"Zoom";

	ResetAll();
}


Martin::~Martin()
{
}


void Martin::PreRender(bool preview)
{
	if (preview)
	{
		SwapDimensions();

		Render(-1, -1);

		FinaliseRenderMartin(PreviewCanvas);

		SwapDimensions();
	}
	else
	{
		Render(-1, -1);

		FinaliseRenderMartin(RenderCanvas);
	}

	CalculateRenderTime();
}


void Martin::RenderSS(int hstart, int hend)
{
}


void Martin::Render(int hstart, int hend)
{
	StartTime = std::chrono::system_clock::now();

	long double xold = 0;
	long double yold = 0;
	long double xnew = 0;
	long double ynew = 0;

	int delta = Fast::Floor((double)max_iterations / pp->ColourCount);
	int count = 0;
	int index = 0;

	// maximum distance from the centre of the image
	int maxdim = Fast::Floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

   	ClearFractalDataA(-1);

	for (int i = 0; i < max_iterations; i++)
	{
		int x = Fast::Floor((Var.d * (long double)xold) + ((long double)Width / 2));
		int y = Fast::Floor((Var.d * (long double)yold) + ((long double)Height / 2));

		if (x < Width && y < Height && x >= 0 && y >= 0)
		{
			switch (RenderMode)
			{
			case __RMMartinAverage:
				FractalData[y * Width + x].a++;
				break;
			case __RMMartinTime:
			{
				FractalData[y * Width + x].a = index;

				count++;

				if (count == delta)
				{
					index++;
					count = 0;
				}
				break;
			}
			case __RMMartinDistance:
				int index = Fast::Floor((std::sqrt(xold * xold + yold * yold) / maxdim) * pp->ColourCount);

				FractalData[y * Width + x].a = index;
				break;
			}
		}

		xnew = yold - Sign(xold) * std::sqrt(std::abs(Var.b * xold - Var.c));
		ynew = Var.a - xold;
		xold = xnew;
		yold = ynew;
	}
}


void Martin::RenderMorph(int hstart, int hend)
{
}


void Martin::ResetView()
{
	int x_min = std::floor(-(double)Width / (2 * Var.d));
	int x_max = std::floor((double)Width / (2 * Var.d));

	int y_min = std::floor(-(double)Height / (2 * Var.d));
	int y_max = std::floor((double)Height / (2 * Var.d));

    SetView(x_min, x_max, y_min, y_max);
}


std::wstring Martin::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; a: " + std::to_wstring(Var.a) + L"; b " + std::to_wstring(Var.b) + L"; c: " + std::to_wstring(Var.c) + L"; Zoom " + std::to_wstring(Var.d) +
		   L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring Martin::Description()
{
	return L"Martin: " + std::to_wstring(Var.a) + L", " + std::to_wstring(Var.b) + L", " +std::to_wstring(Var.c);
}


std::wstring Martin::HistoryEntry()
{
	return L"Martin: " + std::to_wstring(Var.a) + L", " + std::to_wstring(Var.b) + L", " +std::to_wstring(Var.c);
}


void Martin::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Martin fractal\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    a          : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    b          : " + std::to_wstring(Var.b) + L"\n");
	ofile << Formatting::to_utf8(L"    c          : " + std::to_wstring(Var.c) + L"\n");
	ofile << Formatting::to_utf8(L"    zoom       : " + std::to_wstring(Var.d) + L"\n");
}
