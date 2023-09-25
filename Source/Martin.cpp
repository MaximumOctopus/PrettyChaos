//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <algorithm>
#include <string>

#include "Martin.h"


Martin::Martin() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;

	Var.a = 45;
	Var.b = 2;
	Var.c = -300;

	max_iterations = 1000000;

	Name = L"Martin";

	RenderModes.push_back(L"Average");
	RenderModes.push_back(L"Time");
	RenderModes.push_back(L"Distance");
}


Martin::~Martin()
{
}


void Martin::Render()
{
	StartTime = std::chrono::system_clock::now();

	double xold = 0;
	double yold = 0;
	double xnew = 0;
	double ynew = 0;

	int delta = std::floor((double)max_iterations / 500);
	int count = 0;
	int index = 0;

    // maximum distance from the centre of the image
	int maxdim = std::floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

	for (int y = 0; y < 640; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			Iteration[y * Width + x] = 0;
			Canvas[y * Width + x] = 0;
		}
	}

	for (int i = 0; i < max_iterations; i++)
	{
		int x = std::floor((double)xold + ((double)Width / 2));
		int y = std::floor((double)yold + ((double)Height / 2));
		if (x < Width && y < Height && x >= 0 && y >= 0)
		{
			switch (RenderMode)
			{
			case 0:
				Iteration[y * Width + x]++;
				break;
			case 1:
			{
				Canvas[y * Width + x] = Palette[index];

				count++;

				if (count == delta)
				{
					index++;
					count = 0;
				}
				break;
			}
			case 2:
				int index = std::floor((std::sqrt(xold * xold + yold * yold) / maxdim) * 500);
				Canvas[y * Width + x] = Palette[index];
				break;
			}
		}

		xnew = yold - Sign(xold) * std::sqrt(std::abs(Var.b * xold - Var.c));
		ynew = Var.a - xold;
		xold = xnew;
		yold = ynew;
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


void Martin::ResetView()
{

}
