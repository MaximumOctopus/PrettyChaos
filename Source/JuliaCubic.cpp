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

#include "ColourUtility.h"
#include "Constants.h"
#include "JuliaCubic.h"


JuliaCubic::JuliaCubic() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

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


void JuliaCubic::Render()
{
	double max_d = 0;

	StartTime = std::chrono::system_clock::now();

	// maximum distance from the centre of the image
	int maxdim = std::floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

	for (int y = 0; y < Height; y++)
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
				w = std::pow(p * p + q * q, 1.5) * std::cos(3 * std::atan2(q, p)) + Var.a;
				q = std::pow(p * p + q * q, 1.5) * std::sin(3 * std::atan2(q, p)) + Var.b;
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

					Canvas[ydotwidth + x] = ColourUtility::LinearInterpolate(Palette[it],
																			 Palette[it + 1],
																			 itnew - (std::floor(itnew)));
				}
				else
				{
					Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
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

				Canvas[ydotwidth + x] = Palette[index];

				break;
			}
		}
	}

	switch (RenderMode)
	{
	case __RMEscapeTime:
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
			int ydotwidth = y * Width;

			for (int x = 0; x < Width; x++)
			{
				if (Iteration[ydotwidth + x] == 0)
				{
					Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
				}
				else
				{
					int it = Iteration[ydotwidth + x] - min;

					int index = std::round(std::pow((double)it / ((double)max - (double)min), n_coeff) * __PaletteCount);

					Canvas[ydotwidth + x] = Palette[index];
				}
			}
		}
		break;
	}
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

	CalculateRenderTime();
}


void JuliaCubic::ColourNTone(int n)
{
	int* colours = new int[n];

	colours[0] = 0;
	colours[n - 1] = 499;

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
				Canvas[ydotwidth + x] = Palette[colours[Iteration[ydotwidth + x] % n]];
			}
			else
			{
				Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
			}
		}
	}

	delete[] colours;
}


void JuliaCubic::ColourDistanceII(double max_d)
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


void JuliaCubic::ResetView()
{
	SetView(-2.00, 2.00, -2.00, 2.00);
}


void JuliaCubic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Julie Set (Cubic)\n");
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
