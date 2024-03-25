//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <string>
#include <thread>

#include "ColourUtility.h"
#include "Constants.h"
#include "Julia.h"


Julia::Julia() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

	MultiThread = true;

    bailout_radius = 4;

	Var.a = -0.7;
	Var.b = 0.27015;

	Name = L"Julia Set";

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


Julia::~Julia()
{
}


void Julia::MultiThreadRender()
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


void Julia::Render(int hstart, int hend)
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
				w = p * p - q * q + Var.a;
				q = 2 * p * q + Var.b;

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

					it = std::pow((std::floor(max_iterations - itnew) / max_iterations), n_coeff) * __PaletteCount;
					double it_d = (double)it + 1 - nu;

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
				Data[ydotwidth + x] = std::sqrt(std::pow(p + q, 2));

				if (Data[ydotwidth + x] > max_d) max_d = Data[y * Width + x];

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


void Julia::FinaliseRender()
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
					ptr[x].rgbtRed = Palette[__PaletteInfinity] & 0x0000ff;
					ptr[x].rgbtGreen = Palette[__PaletteInfinity] >> 8 & 0x0000ff;
					ptr[x].rgbtBlue = Palette[__PaletteInfinity] >> 16;
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
	case __RMDistance:
		ColourDistanceII(max_d);
		break;
	case __RMTwoTone:
		ColourNTone(2);
		break;
	case __RMThreeTone:
		ColourNTone(3);
		break;
	case __RMFourTone:
		ColourNTone(4);
		break;
	case __RMFiveTone:
		ColourNTone(5);
		break;
	}
}


void Julia::ColourNTone(int n)
{
	int* colours = new int[n];

	colours[0] = 0;
	colours[n - 1] = __PaletteCount - 1;

	if (n > 2)
	{
		int delta = std::floor(__PaletteCount / (n - 1));

		for (int t = 1; t < n - 1; t++)
		{
			colours[t] = Palette[delta * t];
		}
	}

	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			if (Iteration[ydotwidth + x] != max_iterations)
			{
				int colour = Palette[colours[Iteration[ydotwidth + x] % n]];
				ptr[x].rgbtRed = colour & 0x0000ff;
				ptr[x].rgbtGreen = colour >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = colour >> 16;
			}
			else
			{
				ptr[x].rgbtRed = Palette[__PaletteInfinity] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[__PaletteInfinity] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[__PaletteInfinity] >> 16;
			}
		}
	}

	delete[] colours;
}


void Julia::ColourDistanceII(double max_d)
{
	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			if (Iteration[y * Width + x] != max_iterations)
			{
				int index = std::floor(std::pow((Data[y * Width + x] / max_d), n_coeff) * __PaletteCount);

				ptr[x].rgbtRed = Palette[index] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[index] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[index] >> 16;
			}
			else
			{
				ptr[x].rgbtRed = Palette[__PaletteInfinity] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[__PaletteInfinity] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[__PaletteInfinity] >> 16;
			}
		}
	}
}


void Julia::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);
}


void Julia::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Julia Set\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    r bailout  : " + std::to_wstring(bailout_radius) + L"\n\n");
	ofile << Formatting::to_utf8(L"    a          : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    b          : " + std::to_wstring(Var.b) + L"\n\n");

	ofile << Formatting::to_utf8(L"    x min      : " + std::to_wstring(xmin) + L"\n");
	ofile << Formatting::to_utf8(L"    x max      : " + std::to_wstring(xmax) + L"\n");
	ofile << Formatting::to_utf8(L"    y min      : " + std::to_wstring(ymin) + L"\n");
	ofile << Formatting::to_utf8(L"    y max      : " + std::to_wstring(ymax) + L"\n");
}
