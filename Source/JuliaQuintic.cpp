//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Julia_set

#include <Vcl.Graphics.hpp>
#include <string>
#include <thread>

#include "ColourUtility.h"
#include "Constants.h"
#include "JuliaQuintic.h"


JuliaQuintic::JuliaQuintic() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

	MultiThread = true;

    bailout_radius = 4;

	Var.a = -0.79;
	Var.b = 0.15;

	Name = L"Julia Set (Quintic)";

	RenderModes.push_back(L"Escape time");
	RenderModes.push_back(L"Continuous");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance from origin");
	RenderModes.push_back(L"Two-tone");
	RenderModes.push_back(L"Three-tone");
	RenderModes.push_back(L"Four-tone");
	RenderModes.push_back(L"Five-tone");

	NameA = L"real";
	NameB = L"imaginary";

	ResetView();
}


JuliaQuintic::~JuliaQuintic()
{
}


void JuliaQuintic::MultiThreadRender()
{
	StartTime = std::chrono::system_clock::now();

	int h_delta = std::round((double)Height / 4);

	std::thread t1(Render, 0, h_delta);
	std::thread t2(Render, h_delta, 2 * h_delta);
	std::thread t3(Render, 2 * h_delta, 3 * h_delta);
	std::thread t4(Render, 3 * h_delta, Height);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

    FinaliseRender();

	CalculateRenderTime();
}


void JuliaQuintic::Render(int hstart, int hend)
{
	max_d = 0;

	// maximum distance from the centre of the image
	int maxdim = std::floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			double p = xmin + (double)x * (xmax - xmin) / (double)Width;    // real part
			double q = ymin + (double)y * (ymax - ymin) / (double)Height;   // imaginary part

			int it = 0;

			double w = 0;

			while (p * p + q * q <= bailout_radius && it < max_iterations)
			{
				double atan2pq = 5 * std::atan2(q, p);
				double pow25 = std::pow(p * p + q * q, 2.5);

				w = pow25 * std::cos(atan2pq) + Var.a;
				q = pow25 * std::sin(atan2pq) + Var.b;
				p = w;

				it++;
			}

			switch (RenderMode)
			{
			case __RMEscapeTime:
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
					double log_zn = std::log(p * p + q * q) / 2;
					double nu = std::log(log_zn / std::log(2)) / std::log(2);

					double itnew = it + 1 - nu;

					if (itnew < 0) itnew = 0;

					itnew = std::pow((std::floor(itnew) / max_iterations), n_coeff) * __PaletteCount;

					it = std::floor(itnew);

					Iteration[ydotwidth + x] = ColourUtility::LinearInterpolate(Palette[it],
																				Palette[it + 1],
																				itnew - (std::floor(itnew)));
				}
				else
				{
					Iteration[ydotwidth + x] = Palette[__PaletteInfinity];
				}

				break;
			}
			case __RMDistance:
			{
				Data[ydotwidth + x] = std::sqrt(std::pow(p + q, 2));

				if (Data[ydotwidth + x] > max_d) max_d = Data[y * Width + x];

				Iteration[ydotwidth + x] = it;
				break;
			}
			case __RMDistanceOrigin:
				int nx = std::floor(x - (Width / 2));
				int ny = std::floor(y - (Height / 2));

				int index = std::floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((double)it / max_iterations, n_coeff)) * __PaletteCount);

				Iteration[ydotwidth + x] = Palette[index];
				break;
			}
		}
	}
}


void JuliaQuintic::FinaliseRender()
{
	switch (RenderMode)
	{
	case __RMEscapeTime:
	{
		int max = 0;
		int min = max_iterations + 1;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			for (int x = 0; x < Width; x++)
			{
				if (Iteration[ydotwidth + x] > max) max = Iteration[ydotwidth + x];
				if (Iteration[ydotwidth + x] < min && Iteration[ydotwidth + x] != 0) min = Iteration[ydotwidth + x];
			}
		}

		TRGBTriple *ptr;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

			for (int x = 0; x < Width; x++)
			{
				if (Iteration[ydotwidth + x] == 0)
				{
					ptr[x].rgbtRed = PaletteInfintyR;
					ptr[x].rgbtGreen = PaletteInfintyG;
					ptr[x].rgbtBlue = PaletteInfintyB;
				}
				else
				{
					int it = Iteration[ydotwidth + x] - min;

					int index = std::round(std::pow((double)it / ((double)max - (double)min), n_coeff) * __PaletteCount);

					ptr[x].rgbtRed = Palette[index] & 0x0000ff;
					ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
					ptr[x].rgbtBlue = Palette[index] >> 16;
				}
			}
		}
		break;
	}
	case __RMContinuous:
	case __RMDistanceOrigin:
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
	case __RMDistance:                                                                     // distance II
		ColourDistanceII(max_d);
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


void JuliaQuintic::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);
}


void JuliaQuintic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Julie Set (Quintic)\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    r bailout  : " + std::to_wstring(bailout_radius) + L"\n\n");
	ofile << Formatting::to_utf8(L"    real       : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    imaginary  : " + std::to_wstring(Var.b) + L"\n\n");

	ofile << Formatting::to_utf8(L"    x min      : " + std::to_wstring(xmin) + L"\n");
	ofile << Formatting::to_utf8(L"    x max      : " + std::to_wstring(xmax) + L"\n");
	ofile << Formatting::to_utf8(L"    y min      : " + std::to_wstring(ymin) + L"\n");
	ofile << Formatting::to_utf8(L"    y max      : " + std::to_wstring(ymax) + L"\n");
}
