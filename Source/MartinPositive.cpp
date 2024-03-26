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

// also know as Hopalong fractals
// http://www.lantersoft.ch/experiments/hopalong/


#include <algorithm>
#include <string>

#include "Constants.h"
#include "MartinPositive.h"


MartinPositive::MartinPositive() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;
	AcceptsVarD = true;

	AcceptsZoom = false;

	Var.a = 45;
	Var.b = 2;
	Var.c = -300;
	Var.d = 1;

	// we need a LOT of iterations here because we're not calculating a function on a per pixel basis,
	// but bouncing around the screen hitting pixels as we go
	max_iterations = 1000000;

	Name = L"Martin (Positive)";

	RenderModes.push_back(L"Average");
	RenderModes.push_back(L"Time");
	RenderModes.push_back(L"Distance");

	NameA = L"a";
	NameB = L"b";
	NameC = L"c";
	NameD = L"Zoom";

    ResetView();
}


MartinPositive::~MartinPositive()
{
}


void MartinPositive::Render(int hstart, int hend)
{
	StartTime = std::chrono::system_clock::now();

	double xold = 0;
	double yold = 0;
	double xnew = 0;
	double ynew = 0;

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
			Iteration[y * Width + x] = 0;

			ptr[x].rgbtRed = Palette[__PaletteInfinity] & 0x0000ff;
			ptr[x].rgbtGreen = Palette[__PaletteInfinity] >> 8 & 0x0000ff;
			ptr[x].rgbtBlue = Palette[__PaletteInfinity] >> 16;
		}
	}

	for (int i = 0; i < max_iterations; i++)
	{
		int x = std::floor((Var.d * (double)xold) + ((double)Width / 2));
		int y = std::floor((Var.d * (double)yold) + ((double)Height / 2));

		if (x < Width && y < Height && x >= 0 && y >= 0)
		{
			switch (RenderMode)
			{
			case __RMAverage:
				Iteration[y * Width + x]++;
				break;
			case __RMTime:
			{
				ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);
				ptr[x].rgbtRed = Palette[index] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[index] >> 16;

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
				ptr[x].rgbtRed = Palette[index] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[index] >> 16;
				break;
			}
		}

		xnew = yold + Sign(xold) * std::sqrt(std::abs(Var.b * xold - Var.c));
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
			for (int x = 0; x < Width; x++)
			{
				if (Iteration[y * Width + x] > max) max = Iteration[y * Width + x];
				if (Iteration[y * Width + x] < min && Iteration[y * Width + x] != 0) min = Iteration[y * Width + x];
			}
		}

		for (int y = 0; y < Height; y++)
		{
			ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

			for (int x = 0; x < Width; x++)
			{
				if (Iteration[y * Width + x] == 0)
				{
					ptr[x].rgbtRed = PaletteInfintyR;
					ptr[x].rgbtGreen = PaletteInfintyG;
					ptr[x].rgbtBlue = PaletteInfintyB;
				}
				else
				{
					int it = Iteration[y * Width + x] - min;

					int index = std::round(std::pow((double)it / ((double)max - (double)min), n_coeff) * __PaletteCount);

					ptr[x].rgbtRed = Palette[index] & 0x0000ff;
					ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
					ptr[x].rgbtBlue = Palette[index] >> 16;
				}
			}
		}
	}

	CalculateRenderTime();
}


void MartinPositive::ResetView()
{
	int x_min = std::floor(-(double)Width / (2 * Var.d));
	int x_max = std::floor((double)Width / (2 * Var.d));

	int y_min = std::floor(-(double)Height / (2 * Var.d));
	int y_max = std::floor((double)Height / (2 * Var.d));

	SetView(x_min, x_max, y_min, y_max);
}


void MartinPositive::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Martin (Positive) fractal\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    a          : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    b          : " + std::to_wstring(Var.b) + L"\n");
	ofile << Formatting::to_utf8(L"    c          : " + std::to_wstring(Var.c) + L"\n");
	ofile << Formatting::to_utf8(L"    zoom       : " + std::to_wstring(Var.d) + L"\n");
}
