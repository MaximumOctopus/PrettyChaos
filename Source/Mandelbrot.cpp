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

#include "Mandelbrot.h"


Mandelbrot::Mandelbrot() : Fractal()
{
	Name = L"Mandelbrot";

	RenderModes.push_back(L"Escape time");
	RenderModes.push_back(L"Continuous");
	RenderModes.push_back(L"Two-tone");
	RenderModes.push_back(L"Three-tone");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance II");

	ResetView();
}


Mandelbrot::~Mandelbrot()
{
}


void Mandelbrot::Render()
{
	double max_d = 0;

	StartTime = std::chrono::system_clock::now();

	if (RenderMode == 0)
	{
		NumIterationsPerPixel = new int[max_iterations];
		for (int z = 0; z < max_iterations; z++) NumIterationsPerPixel[z] = 0;
	}

	if (RenderMode == 3 || RenderMode == 4) Distances = new double[Width * Height];

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			double p = xmin + (double)x * (xmax - xmin) / (double)Width;    // real part
			double q = ymin + (double)y * (ymax - ymin) / (double)Height;   // imaginary part

			int it = 0;

			double x1 = 0;
			double y1 = 0;
			double x2 = 0;
			double y2 = 0;
			double w = 0;

			while (x2 + y2 <= bailout_radius && it < max_iterations)
			{
				x1 = x2 - y2 + p;
				y1 = w - x2 - y2 + q;

				x2 = x1 * x1;
				y2 = y1 * y1;

				w = (x1 + y1) * (x1 + y1);

				it++;
			}

			switch (RenderMode)
			{
			case 0:
			case 2:
			case 3:
			{
				Iteration[y * Width + x] = it;
				break;
			}
			case 1:
			{
				if (it < max_iterations)
				{
					double log_zn = std::log(x1 * x1 + y1 * y1) / 2;
					double nu = std::log(log_zn / std::log(2)) / std::log(2);

					double itnew = it + 1 - nu;

					it = std::pow((std::floor(itnew) / max_iterations), n_coeff) * 500;
					double it_d = (double)it + 1 - nu;

					Canvas[y * Width + x] = LinearInterpolate(Palette[it], Palette[it + 1], it_d - (std::floorl(it_d)));
				}
				else
				{
					Canvas[y * Width + x] = PaletteInfinity;
				}

				break;
			}
			case 4:
			{
				if (it < max_iterations)
				{
					Distances[y * Width + x] = std::sqrt(w);

					if (Distances[y * Width + x] > max_d) max_d = Distances[y * Width + x];

					Iteration[y * Width + x] = it;
				}
				Iteration[y * Width + x] = it;
				break;
			}
			case 5:
			{
				if (it < max_iterations)
				{
					Distances[y * Width + x] = std::sqrt(std::pow(x2 + y2, 2));

					if (Distances[y * Width + x] > max_d) max_d = Distances[y * Width + x];

					Iteration[y * Width + x] = it;
				}
				Iteration[y * Width + x] = it;
				break;
			}
			}
		}
	}

	switch (RenderMode)
	{
	case 0:
	{
		for (int y = 0; y < Height; y++)
		{
			for (int x = 0; x < Width; x++)
			{
				NumIterationsPerPixel[Iteration[y * Width + x]]++;
			}
		}

		int total = 0;

		for (int i = 0; i < max_iterations; i++)
		{
			total += NumIterationsPerPixel[i];
		}

		for (int y = 0; y < Height; y++)
		{
			for (int x = 0; x < Width; x++)
			{
				double c = 0;

				for (int i = 0; i < Iteration[y * Width + x]; i++)
				{
					c += (double)NumIterationsPerPixel[i] / (double)total;
				}

				int index = std::round(std::pow(c, n_coeff) * 500);

				if (Iteration[y * Width + x] != max_iterations)
				{
					Canvas[y * Width + x] = Palette[index];
				}
				else
				{
					Canvas[y * Width + x] = PaletteInfinity;
				}
			}
		}
		break;
	}
	case 2:                                                                     // two-tone
		ColourTwoTone();
		break;
	case 3:                                                                     // three-tone
		ColourThreeTone();
		break;
	case 4:                                                                     // distance I
		ColourDistanceI(max_d);
		break;
	case 5:                                                                     // distance II
		ColourDistanceII(max_d);
		break;
	}

	CalculateRenderTime();

	if (RenderMode == 0)
		delete[] NumIterationsPerPixel;
}


void Mandelbrot::ColourTwoTone()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Iteration[y * Width + x] != max_iterations)
			{
				if (Iteration[y * Width + x] % 2 == 0)
				{
					Canvas[y * Width + x] = Palette[0];
				}
				else if (Iteration[y * Width + x] % 2 == 1)
				{
					Canvas[y * Width + x] = Palette[499];
				}
			}
			else
			{
				Canvas[y * Width + x] = PaletteInfinity;
			}
		}
	}
}


void Mandelbrot::ColourThreeTone()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Iteration[y * Width + x] != max_iterations)
			{
				switch (Iteration[y * Width + x] % 3)
				{
				case 0:
					Canvas[y * Width + x] = Palette[0];
					break;
				case 1:
					Canvas[y * Width + x] = Palette[249];
					break;
				case 2:
					Canvas[y * Width + x] = Palette[499];
					break;
				}
			}
			else
			{
				Canvas[y * Width + x] = PaletteInfinity;
			}
		}
	}
}


void Mandelbrot::ColourDistanceI(double max_d)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Iteration[y * Width + x] != max_iterations)
			{
				int index = std::floor(std::pow((Distances[y * Width + x] / max_d), n_coeff) * 500);

				Canvas[y * Width + x] = Palette[index];
			}
			else
			{
				Canvas[y * Width + x] = PaletteInfinity;
			}
		}
	}
}


void Mandelbrot::ColourDistanceII(double max_d)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Iteration[y * Width + x] != max_iterations)
			{
				int index = std::floor(std::pow((Distances[y * Width + x] / max_d), n_coeff) * 500);

				Canvas[y * Width + x] = Palette[index];
			}
			else
			{
				Canvas[y * Width + x] = PaletteInfinity;
			}
		}
	}
}


void Mandelbrot::Preview()
{
	//
}


void Mandelbrot::ResetView()
{
	ymin = -1.22;
	ymax =  1.22;
	xmin = -2.00;
	xmax =  0.47;
}
