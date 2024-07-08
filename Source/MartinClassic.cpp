//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
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
#include "MartinClassic.h"


Martin::Martin() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;
	AcceptsVarD = true;

	QuickParamterMode = 2;  // 2 = A+B+C

	AcceptsZoom = false;

	Var.a = 45;
	Var.b = 2;
	Var.c = -300;
	Var.d = 1;

	// we need a LOT of iterations here because we're not calculating a function on a per pixel basis,
    // but bouncing around the screen hitting pixels as we go
	max_iterations = 1000000;

	Name = L"Martin";

	RenderModes.push_back(L"Average");
	RenderModes.push_back(L"Time");
	RenderModes.push_back(L"Distance");

	NameA = L"a";
	NameB = L"b";
	NameC = L"c";
	NameD = L"Zoom";

    ResetView();
}


Martin::~Martin()
{
}


void Martin::PreRender(bool preview)
{
	if (preview) SwapDimensions();

	Render(-1, -1);

	if (preview) SwapDimensions();
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

	int delta = std::floor((double)max_iterations / __PaletteCount);
	int count = 0;
	int index = 0;

    // maximum distance from the centre of the image
	int maxdim = std::floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			FractalData[y * Width + x].a = 0;

			ptr[x].rgbtRed = Palette[__PaletteInfinity].r;
			ptr[x].rgbtGreen = Palette[__PaletteInfinity].g;
			ptr[x].rgbtBlue = Palette[__PaletteInfinity].b;
		}
	}

	for (int i = 0; i < max_iterations; i++)
	{
		int x = std::floor((Var.d * (long double)xold) + ((long double)Width / 2));
		int y = std::floor((Var.d * (long double)yold) + ((long double)Height / 2));

		if (x < Width && y < Height && x >= 0 && y >= 0)
		{
			switch (RenderMode)
			{
			case __RMAverage:
				FractalData[y * Width + x].a++;
				break;
			case __RMTime:
			{
				ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

				ptr[x].rgbtRed = Palette[index].r;
				ptr[x].rgbtGreen = Palette[index].g;
				ptr[x].rgbtBlue = Palette[index].b;

				count++;

				if (count == delta)
				{
					index++;
					count = 0;
				}
				break;
			}
			case __RMDistance:
				int index = std::floor((std::sqrt(xold * xold + yold * yold) / maxdim) * __PaletteCount);

				ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

				ptr[x].rgbtRed = Palette[index].r;
				ptr[x].rgbtGreen = Palette[index].g;
				ptr[x].rgbtBlue = Palette[index].b;
				break;
			}
		}

		xnew = yold - Sign(xold) * std::sqrt(std::abs(Var.b * xold - Var.c));
		ynew = Var.a - xold;
		xold = xnew;
		yold = ynew;
	}

	if (RenderMode == __RMAverage)
	{
		int max = 0;
		int min = max_iterations + 1;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			for (int x = 0; x < Width; x++)
			{
				if (FractalData[ydotwidth + x].a > max) max = FractalData[ydotwidth + x].a;
				if (FractalData[ydotwidth + x].a < min && FractalData[ydotwidth + x].a != 0) min = FractalData[ydotwidth + x].a;
			}
		}

		TRGBTriple *ptr;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

			for (int x = 0; x < Width; x++)
			{
				if (FractalData[ydotwidth + x].a == 0)
				{
					ptr[x].rgbtRed = Palette[__PaletteInfinity].r;
					ptr[x].rgbtGreen = Palette[__PaletteInfinity].g;
					ptr[x].rgbtBlue = Palette[__PaletteInfinity].b;
				}
				else
				{
					int it = FractalData[ydotwidth + x].a - min;

					int index = std::round(std::pow((long double)it / ((long double)max - (long double)min), n_coeff) * __PaletteCount);

					ptr[x].rgbtRed = Palette[index].r;
					ptr[x].rgbtGreen = Palette[index].g;
					ptr[x].rgbtBlue = Palette[index].b;
				}
			}
		}
	}

	CalculateRenderTime();
}


void Martin::ResetView()
{
	int x_min = std::floor(-(double)Width / (2 * Var.d));
	int x_max = std::floor((double)Width / (2 * Var.d));

	int y_min = std::floor(-(double)Height / (2 * Var.d));
	int y_max = std::floor((double)Height / (2 * Var.d));

    SetView(x_min, x_max, y_min, y_max);
}


void Martin::ResetAll()
{
	Var.a = 45;
	Var.b = 2;
	Var.c = -300;
	Var.d = 1;

	max_iterations = 1000000;

	ResetView();
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
