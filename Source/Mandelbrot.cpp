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

#include "Constants.h"
#include "Mandelbrot.h"


Mandelbrot::Mandelbrot() : Fractal()
{
	Name = L"Mandelbrot";

	RenderModes.push_back(L"Escape time");
	RenderModes.push_back(L"Continuous");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance II");
	RenderModes.push_back(L"Two-tone");
	RenderModes.push_back(L"Three-tone");
	RenderModes.push_back(L"Four-tone");
	RenderModes.push_back(L"Five-tone");

	NameA = L"real";
	NameB = L"imaginary";

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

					it = std::pow((std::floor(itnew) / max_iterations), n_coeff) * __PaletteCount;
					double it_d = (double)it + 1 - nu;

					Canvas[y * Width + x] = it;
					Data[y * Width + x] = it_d - (std::floorl(it_d));
				}
				else
				{
					Canvas[y * Width + x] = __PaletteInfinity;
				}

				break;
			}
			case 2:
			{
				if (it < max_iterations)
				{
					Data[y * Width + x] = std::sqrt(w);

					if (Data[y * Width + x] > max_d) max_d = Data[y * Width + x];

					Iteration[y * Width + x] = it;
				}
				Iteration[y * Width + x] = it;
				break;
			}
			case 3:
			{
				if (it < max_iterations)
				{
					Data[y * Width + x] = std::sqrt(std::pow(x2 + y2, 2));

					if (Data[y * Width + x] > max_d) max_d = Data[y * Width + x];

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

				int index = std::round(std::pow(c, n_coeff) * __PaletteCount);

				if (Iteration[y * Width + x] != max_iterations)
				{
					Canvas[y * Width + x] = index;
				}
				else
				{
					Canvas[y * Width + x] = __PaletteInfinity;
				}
			}
		}
		break;
	}
	case 2:                                                                     // distance I
		ColourDistanceI(max_d);
		break;
	case 3:                                                                     // distance II
		ColourDistanceII(max_d);
		break;
	case 4:                                                                     // two-tone
		ColourNTone(2);
		break;
	case 5:                                                                     // three-tone
		ColourNTone(3);
		break;
	case 6:                                                                     // four-tone
		ColourNTone(4);
		break;
	case 7:                                                                     // five-tone
		ColourNTone(5);
		break;
	}

	CalculateRenderTime();

	if (RenderMode == 0)
		delete[] NumIterationsPerPixel;
}


void Mandelbrot::ColourNTone(int n)
{
	int* colours = new int[n];

	colours[0] = 0;
	colours[n - 1] = 499;

	if (n > 2)
	{
		int delta = std::floor(__PaletteCount / (n - 1));

		for (int t = 1; t < n - 1; t++)
		{
			colours[t] = delta * t;
		}
	}

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Iteration[y * Width + x] != max_iterations)
			{
				Canvas[y * Width + x] = colours[Iteration[y * Width + x] % n];
			}
			else
			{
				Canvas[y * Width + x] = __PaletteInfinity;
			}
		}
	}

	delete[] colours;
}


void Mandelbrot::ColourDistanceI(double max_d)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Iteration[y * Width + x] != max_iterations)
			{
				int index = std::floor(std::pow((Data[y * Width + x] / max_d), n_coeff) * __PaletteCount);

				Canvas[y * Width + x] = index;
			}
			else
			{
				Canvas[y * Width + x] = __PaletteInfinity;
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
				int index = std::floor(std::pow((Data[y * Width + x] / max_d), n_coeff) * __PaletteCount);

				Canvas[y * Width + x] = index;
			}
			else
			{
				Canvas[y * Width + x] = __PaletteInfinity;
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


void Mandelbrot::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Mandelbrot fractal\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + std::to_wstring(RenderMode) + L"\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    r bailout  : " + std::to_wstring(bailout_radius) + L"\n\n");

	ofile << Formatting::to_utf8(L"    x min      : " + std::to_wstring(xmin) + L"\n");
	ofile << Formatting::to_utf8(L"    x max      : " + std::to_wstring(xmax) + L"\n");
	ofile << Formatting::to_utf8(L"    y min      : " + std::to_wstring(ymin) + L"\n");
	ofile << Formatting::to_utf8(L"    y max      : " + std::to_wstring(ymax) + L"\n");
}
