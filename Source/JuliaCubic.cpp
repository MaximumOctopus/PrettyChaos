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
#include "JuliaCubic.h"


JuliaCubic::JuliaCubic() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

	QuickParamterMode = 1;	// A+B + fine control

	MultiThread = true;
    ThreadCount  = 4;

	bailout_radius = 4;

	Var.a = -0.7;
	Var.b = 0.27015;

	Name = L"Julia Set (Cubic)";

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


JuliaCubic::~JuliaCubic()
{
}


bool JuliaCubic::MultiThreadRender(bool preview)
{
	// nothing to render, point isn't valid
	if (PointGoesToInfinity(Var.a, Var.b))
	{
		return false;
	}

	StartTime = std::chrono::system_clock::now();

	if (preview) SwapDimensions();

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

	if (preview) SwapDimensions();

    return true;
}


void JuliaCubic::Render(int hstart, int hend)
{
	max_d = 0;

	// maximum distance from the centre of the image
	int maxdim = std::floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			long double p = xmin + (long double)x * (xmax - xmin) / (long double)Width;    // real part
			long double q = ymin + (long double)y * (ymax - ymin) / (long double)Height;   // imaginary part

			int it = 0;

			long double w = 0;

			while (p * p + q * q <= bailout_radius && it < max_iterations)
			{
				long double atan2pq = 3 * std::atan2(q, p);
				long double pow15 = std::pow(p * p + q * q, 1.5);

				w = pow15 * std::cos(atan2pq) + Var.a;
				q = pow15 * std::sin(atan2pq) + Var.b;
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
					long double log_zn = std::log(p * p + q * q) / 2;
					long double nu = std::log(log_zn / std::log(2)) / std::log(2);

					long double itnew = it + 1 - nu;

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

				int index = std::floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * __PaletteCount);

				Iteration[ydotwidth + x] = Palette[index];
				break;
			}
		}
	}
}


void JuliaCubic::FinaliseRender()
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

					int index = std::round(std::pow((long double)it / ((long double)max - (long double)min), n_coeff) * __PaletteCount);

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


void JuliaCubic::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);
}


void JuliaCubic::ResetAll()
{
	bailout_radius = 4;

	Var.a = -0.7;
	Var.b = 0.27015;

	n_coeff = 1;
	max_iterations = 1000;
	bailout_radius = 256;

	ResetView();
}


std::wstring JuliaCubic::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; real: " + std::to_wstring(Var.a) + L"; imaginary " + std::to_wstring(Var.b) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


void JuliaCubic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Julie Set (Cubic)\n");
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
