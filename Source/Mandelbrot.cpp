//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Orbit_trap

#include <string>

#include "ColourUtility.h"
#include "Constants.h"
#include "Mandelbrot.h"


Mandelbrot::Mandelbrot() : Fractal()
{
	Name = L"Mandelbrot";

   	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

    bailout_radius = 4;

	AcceptsABCSpectificRenderModeBegin = 4;
	AcceptsABCSpectificRenderModeEnd = 5;

	RenderModes.push_back(L"Escape time");
	RenderModes.push_back(L"Continuous");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance II");
	RenderModes.push_back(L"Orbit Trap");
	RenderModes.push_back(L"Orbit Trap (filled)");
	RenderModes.push_back(L"Two-tone");
	RenderModes.push_back(L"Three-tone");
	RenderModes.push_back(L"Four-tone");
	RenderModes.push_back(L"Five-tone");

	NameA = L"orbit x";
	NameB = L"orbit y";

	Var.a = xmin + ((xmax - xmin) / 2);     // set orbit trap position to centre of view
	Var.b = ymin + ((ymax - ymin) / 2);     //

	ResetView();
}


Mandelbrot::~Mandelbrot()
{
}


void Mandelbrot::Render()
{
	double max_d = 0;

	StartTime = std::chrono::system_clock::now();

	if (RenderMode == __RMEscapeTime)
	{
		NumIterationsPerPixel = new int[max_iterations];
		for (int z = 0; z < max_iterations; z++) NumIterationsPerPixel[z] = 0;
	}

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			double p = xmin + (double)x * (xmax - xmin) / (double)Width;    // real part
			double q = ymin + (double)y * (ymax - ymin) / (double)Height;   // imaginary part

			int it = 0;

			Data[y * Width + x] = 10000000000000;
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

				if (RenderMode == __RMOrbitTrap || RenderMode == __RMOrbitTrapFilled)
				{
					double cr = x1 - Var.a;
					double ci = y1 - Var.b;

					double magnitude = std::sqrt(cr * cr + ci * ci);

					if (magnitude < Data[ydotwidth + x])
					{
						Data[ydotwidth + x] = magnitude;
					}
				}

				it++;
			}

			switch (RenderMode)
			{
			case __RMEscapeTime:
			case __RMOrbitTrapFilled:
	 	    case __RMTwoTone:
			case __RMThreeTone:
			case __RMFourTone:
			case __RMFiveTone:
			{
				Iteration[ydotwidth + x] = it;
				break;
			}
			case __RMContinuous:
			{
				if (it < max_iterations)
				{
					double log_zn = std::log(x1 * x1 + y1 * y1) / 2;
					double nu = std::log(log_zn / std::log(2)) / std::log(2);

					double itnew = it + 1 - nu;

					it = std::pow((std::floor(itnew) / max_iterations), n_coeff) * __PaletteCount;
					double it_d = (double)it + 1 - nu;

					Canvas[ydotwidth + x] = ColourUtility::LinearInterpolate(Palette[it],
																			 Palette[it + 1],
																			 it_d - (std::floorl(it_d)));
				}
				else
				{
					Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
				}

				break;
			}
			case __RMDistance:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(w);

					if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];

					Iteration[ydotwidth + x] = it;
				}
				Iteration[ydotwidth + x] = it;
				break;
			}
			case __RMDistanceII:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(std::pow(x2 + y2, 2));

					if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];

					Iteration[ydotwidth + x] = it;
				}
				Iteration[ydotwidth + x] = it;

				break;
			}
			}
		}
	}

	switch (RenderMode)
	{
	case __RMEscapeTime:
	{
		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			for (int x = 0; x < Width; x++)
			{
				NumIterationsPerPixel[Iteration[ydotwidth + x]]++;
			}
		}

		int total = 0;

		for (int i = 0; i < max_iterations; i++)
		{
			total += NumIterationsPerPixel[i];
		}

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			for (int x = 0; x < Width; x++)
			{
				double c = 0;

				for (int i = 0; i < Iteration[ydotwidth + x]; i++)
				{
					c += (double)NumIterationsPerPixel[i] / (double)total;
				}

				int index = std::round(std::pow(c, n_coeff) * __PaletteCount);

				if (Iteration[ydotwidth + x] != max_iterations)
				{
					Canvas[ydotwidth + x] = Palette[index];
				}
				else
				{
					Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
				}
			}
		}
		break;
	}
	case __RMDistance:                                                                     // distance I
		ColourDistanceI(max_d);
		break;
	case __RMDistanceII:                                                                     // distance II
		ColourDistanceII(max_d);
		break;
	case __RMOrbitTrap:
		OrbitTrap(false);
		break;
	case __RMOrbitTrapFilled:
		OrbitTrap(true);
		break;
	case __RMTwoTone:                                                                     // two-tone
		ColourNTone(2);
		break;
	case __RMThreeTone:                                                                     // three-tone
		ColourNTone(3);
		break;
	case __RMFourTone:                                                                     // four-tone
		ColourNTone(4);
		break;
	case __RMFiveTone:                                                                     // five-tone
		ColourNTone(5);
		break;
	}

	CalculateRenderTime();

	if (RenderMode == __RMEscapeTime)
		delete[] NumIterationsPerPixel;
}


void Mandelbrot::ColourNTone(int n)
{
	int* colours = new int[n];

	colours[0] = Palette[0];
	colours[n - 1] = Palette[499];

	if (n > 2)
	{
		int delta = std::floor(__PaletteCount / (n - 1));

		for (int t = 1; t < n - 1; t++)
		{
			colours[t] = Palette[delta * t];
		}
	}

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			if (Iteration[ydotwidth + x] != max_iterations)
			{
				Canvas[ydotwidth + x] = colours[Iteration[ydotwidth + x] % n];
			}
			else
			{
				Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
			}
		}
	}

	delete[] colours;
}


void Mandelbrot::ColourDistanceI(double max_d)
{
	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			if (Iteration[ydotwidth + x] != max_iterations)
			{
				int index = std::floor(std::pow((Data[ydotwidth + x] / max_d), n_coeff) * __PaletteCount);

				Canvas[ydotwidth + x] = Palette[index];
			}
			else
			{
				Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
			}
		}
	}
}


void Mandelbrot::ColourDistanceII(double max_d)
{
	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			if (Iteration[ydotwidth + x] != max_iterations)
			{
				int index = std::floor(std::pow((Data[ydotwidth + x] / max_d), n_coeff) * __PaletteCount);

				Canvas[ydotwidth + x] = Palette[index];
			}
			else
			{
				Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
			}
		}
	}
}


void Mandelbrot::OrbitTrap(bool fill)
{
	double maxx = 0;

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Data[y * Width + x] > maxx)
			{
				maxx = Data[y * Width + x];
			}
		}
	}

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			if (fill)
			{
				if (Iteration[ydotwidth + x] != max_iterations)
				{
					int index =  std::floor(std::pow((Data[ydotwidth + x] / maxx), n_coeff) * __PaletteCount);

					Canvas[ydotwidth + x] = Palette[index];
				}
				else
				{
					Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
				}
			}
			else
			{
				int index =  std::floor(std::pow((Data[ydotwidth + x] / maxx), n_coeff) * __PaletteCount);

				Canvas[ydotwidth + x] = Palette[index];
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
	SetView(-2.00, 0.47, -1.22, 1.22);
}


void Mandelbrot::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Mandelbrot fractal\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    r bailout  : " + std::to_wstring(bailout_radius) + L"\n\n");

	ofile << Formatting::to_utf8(L"    x min      : " + std::to_wstring(xmin) + L"\n");
	ofile << Formatting::to_utf8(L"    x max      : " + std::to_wstring(xmax) + L"\n");
	ofile << Formatting::to_utf8(L"    y min      : " + std::to_wstring(ymin) + L"\n");
	ofile << Formatting::to_utf8(L"    y max      : " + std::to_wstring(ymax) + L"\n");

	if (RenderMode == __RMOrbitTrap || RenderMode == __RMOrbitTrapFilled)
	{
		ofile << Formatting::to_utf8(L"    Orbit x    : " + std::to_wstring(Var.a) + L"\n");
		ofile << Formatting::to_utf8(L"    Orbit y    : " + std::to_wstring(Var.b) + L"\n");
	}
}
