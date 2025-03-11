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

// also know as Hopalong fractals
// http://www.lantersoft.ch/experiments/hopalong/


#include <algorithm>
#include <string>

#include "Constants.h"
#include "Fast.h"
#include "MartinSinusoidal.h"


MartinSinusoidal::MartinSinusoidal() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;
	AcceptsVarD = true;

	QPM = QuickParameterMode::kABC;

	AcceptsZoom = false;

	// we need a LOT of iterations here because we're not calculating a function on a per pixel basis,
	// but bouncing around the screen hitting pixels as we go
	Defaults.Set(1, 1000000, 4, 15, 30, 4, 1);

	Name = L"Martin (Sinusoidal)";

	RenderModes.push_back(L"Average");
	RenderModes.push_back(L"Time");
	RenderModes.push_back(L"Distance");

	NameA = L"a";
	NameB = L"b";
	NameC = L"c";
	NameD = L"Zoom";

	ResetAll();
}


MartinSinusoidal::~MartinSinusoidal()
{
}


void MartinSinusoidal::PreRender(bool preview)
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


void MartinSinusoidal::RenderSS(int hstart, int hend)
{
}


void MartinSinusoidal::Render(int hstart, int hend)
{
	StartTime = std::chrono::system_clock::now();

	long double xold = 0;
	long double yold = 0;
	long double xnew = 0;
	long double ynew = 0;

	int delta = Fast::Floor((double)max_iterations / __PaletteCount);
	int count = 0;
	int index = 0;

    // maximum distance from the centre of the image
	int maxdim = Fast::Floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

	ClearFractalDataA();

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
				int index = Fast::Floor((std::sqrt(xold * xold + yold * yold) / maxdim) * __PaletteCount);

				FractalData[y * Width + x].a = index;
				break;
			}
		}

		xnew = yold + std::sin(Var.b * xold - Var.c);
		ynew = Var.a - xold;
		xold = xnew;
		yold = ynew;
	}

	CalculateRenderTime();
}


void MartinSinusoidal::ResetView()
{
	int x_min = std::floor(-(double)Width / (2 * Var.d));
	int x_max = std::floor((double)Width / (2 * Var.d));

	int y_min = std::floor(-(double)Height / (2 * Var.d));
	int y_max = std::floor((double)Height / (2 * Var.d));

	SetView(x_min, x_max, y_min, y_max);
}


std::wstring MartinSinusoidal::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; a: " + std::to_wstring(Var.a) + L"; b " + std::to_wstring(Var.b) + L"; c: " + std::to_wstring(Var.c) + L"; Zoom " + std::to_wstring(Var.d) +
		   L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring MartinSinusoidal::Description()
{
	return L"Martin (Sinusoidal): " + std::to_wstring(Var.a) + L", " + std::to_wstring(Var.b) + L", " +std::to_wstring(Var.c);
}


void MartinSinusoidal::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Martin (Sinusoidal) fractal\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n\n");
	ofile << Formatting::to_utf8(L"    a          : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    b          : " + std::to_wstring(Var.b) + L"\n");
	ofile << Formatting::to_utf8(L"    c          : " + std::to_wstring(Var.c) + L"\n");
	ofile << Formatting::to_utf8(L"    zoom       : " + std::to_wstring(Var.d) + L"\n");
}
