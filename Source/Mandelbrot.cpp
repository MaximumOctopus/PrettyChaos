//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Orbit_trap

#include <string>
#include <thread>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "Mandelbrot.h"


Mandelbrot::Mandelbrot() : Fractal()
{
	Name = L"Mandelbrot";

   	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

	MultiThread = true;
    ThreadCount  = 5;

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

	ResetView();
}


Mandelbrot::~Mandelbrot()
{
}



bool Mandelbrot::MultiThreadRender(bool preview)
{
    max_d = 0;

	StartTime = std::chrono::system_clock::now();

	if (preview) SwapDimensions();

	if (RenderMode == __RMEscapeTime)
	{
		NumIterationsPerPixel = new int[max_iterations];
		for (int z = 0; z < max_iterations; z++) NumIterationsPerPixel[z] = 0;
	}

	int h_delta = std::round((double)Height / 5);

	std::thread t1(Render, 0, h_delta);
	std::thread t2(Render, h_delta, 2 * h_delta);
	std::thread t3(Render, 2 * h_delta, 3 * h_delta);
	std::thread t4(Render, 3 * h_delta, 4 * h_delta);
	std::thread t5(Render, 4 * h_delta, Height);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	FinaliseRender();

	CalculateRenderTime();

	if (RenderMode == __RMEscapeTime)
	{
		delete[] NumIterationsPerPixel;
	}

	if (preview) SwapDimensions();

    return true;
}


void Mandelbrot::Render(int hstart, int hend)
{
	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		long double q = ymin + (long double)y * (ymax - ymin) / (long double)Height;   // imaginary part

		for (int x = 0; x < Width; x++)
		{
			long double p = xmin + (long double)x * (xmax - xmin) / (long double)Width;    // real part

			int it = 0;

			Data[y * Width + x] = 10000000000000;
			long double x1 = 0;
			long double y1 = 0;
			long double x2 = 0;
			long double y2 = 0;
			long double w = 0;

			while (x2 + y2 <= bailout_radius && it < max_iterations)
			{
				x1 = x2 - y2 + p;
				y1 = w - x2 - y2 + q;

				x2 = x1 * x1;
				y2 = y1 * y1;

				w = (x1 + y1) * (x1 + y1);

				if (RenderMode == __RMOrbitTrap || RenderMode == __RMOrbitTrapFilled)
				{
					long double cr = x1 - Var.a;
					long double ci = y1 - Var.b;

					long double magnitude = std::sqrt(cr * cr + ci * ci);

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
			case __RMOrbitTrap:
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
					long double log_zn = std::log(x1 * x1 + y1 * y1) / 2;
					long double nu = std::log(log_zn / std::log(2)) / std::log(2);

					long double itnew = it + 1 - nu;

					it = std::pow((std::floor(itnew) / max_iterations), n_coeff) * __PaletteCount;
					long double it_d = (long double)it + 1 - nu;

					Iteration[ydotwidth + x] = ColourUtility::LinearInterpolate(Palette[it],
																  Palette[it + 1],
																  it_d - (std::floorl(it_d)));
				}
				else
				{
					Iteration[ydotwidth + x] = Palette[__PaletteInfinity];
				}

				break;
			}
			case __RMDistance:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(w);

					if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];
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
				}
				Iteration[ydotwidth + x] = it;
				break;
			}
			}
		}
	}


}


void Mandelbrot::FinaliseRender()
{
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

		TRGBTriple *ptr;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

			for (int x = 0; x < Width; x++)
			{
				long double c = 0;

				for (int i = 0; i < Iteration[ydotwidth + x]; i++)
				{
					c += (long double)NumIterationsPerPixel[i] / (long double)total;
				}

				if (Iteration[ydotwidth + x] != max_iterations)
				{
					int index = Fast::Floor(std::pow(c, n_coeff) * __PaletteCount);

					ptr[x].rgbtRed = Palette[index] & 0x0000ff;
					ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
					ptr[x].rgbtBlue = Palette[index] >> 16;
				}
				else
				{
					ptr[x].rgbtRed = PaletteInfintyR;
					ptr[x].rgbtGreen = PaletteInfintyG;
					ptr[x].rgbtBlue = PaletteInfintyB;
				}
			}
		}
		break;
	}
	case __RMContinuous:
		TRGBTriple *ptr;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

			for (int x = 0; x < Width; x++)
			{
				ptr[x].rgbtRed = Iteration[ydotwidth + x] & 0x0000ff;
				ptr[x].rgbtGreen = Iteration[ydotwidth + x] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Iteration[ydotwidth + x] >> 16;
			}
		}
		break;
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

	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			if (fill)
			{
				if (Iteration[ydotwidth + x] != max_iterations)
				{
					int index =  std::floor(std::pow((Data[ydotwidth + x] / maxx), n_coeff) * __PaletteCount);

					ptr[x].rgbtRed = Palette[index] & 0x0000ff;
					ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
					ptr[x].rgbtBlue = Palette[index] >> 16;
				}
				else
				{
					ptr[x].rgbtRed = PaletteInfintyR;
					ptr[x].rgbtGreen = PaletteInfintyG;
					ptr[x].rgbtBlue = PaletteInfintyB;
				}
			}
			else
			{
				int index =  std::floor(std::pow((Data[ydotwidth + x] / maxx), n_coeff) * __PaletteCount);

				ptr[x].rgbtRed = Palette[index] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[index] >> 16;
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
	SetView(-2.00, 0.47, -0.988, 0.988);

	Var.a = xmin + ((xmax - xmin) / 2);     // set orbit trap position to centre of view
	Var.b = ymin + ((ymax - ymin) / 2);     //
}


void Mandelbrot::ResetAll()
{
	bailout_radius = 4;

	n_coeff = 1;
	max_iterations = 1000;
	bailout_radius = 256;

	ResetView();
}


std::wstring Mandelbrot::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; orbit x: " + std::to_wstring(Var.a) + L"; orbit y " + std::to_wstring(Var.b) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
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
