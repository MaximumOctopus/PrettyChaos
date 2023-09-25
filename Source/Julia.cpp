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
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

	Var.a = -0.7;
	Var.b = 0.27015;

	Name = L"Julia Set";

	RenderModes.push_back(L"Average");

	ResetView();
}


Julia::~Julia()
{
}


void Julia::Render()
{
	StartTime = std::chrono::system_clock::now();

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			double p = xmin + (double)x * (xmax - xmin) / (double)Width;    // real part
			double q = ymin + (double)y * (ymax - ymin) / (double)Height;   // imaginary part

			int it = 0;

			double w = 0;

			while (p * p + q * q <= 4 && it < max_iterations)
			{
				w = p * p - q * q + Var.a;
				q = 2 * p * q + Var.b;

				p = w;

				it++;
			}

			Iteration[y * Width + x] = it;
		}
	}

	if (RenderMode == 0)
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
			for (int x = 0; x < Width; x++)
			{
				if (Iteration[y * Width + x] == 0)
				{
					Canvas[y * Width + x] = PaletteInfinity;
				}
				else
				{
					int it = Iteration[y * Width + x] - min;

					int index = std::round(std::pow((double)it / ((double)max - (double)min), n_coeff) * 500);

					Canvas[y * Width + x] = Palette[index];
				}
			}
		}
	}

	CalculateRenderTime();
}


void Julia::ResetView()
{
	ymin = -2.0;
	ymax =  2.0;
	xmin = -2.0;
	xmax =  2.0;
}
