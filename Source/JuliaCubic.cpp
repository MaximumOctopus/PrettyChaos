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
		for (int x = 0; x < Width; x++)
		{
			double p = xmin + (double)x * (xmax - xmin) / (double)Width;    // real part
			double q = ymin + (double)y * (ymax - ymin) / (double)Height;   // imaginary part

			int it = 0;

			double w = 0;

			while (p * p + q * q <= bailout_radius && it < max_iterations)
			{
				w = std::pow(p * p + q * q, 1.5) * std::cos(3 * std::atan2(q, p)) + Var.a;
				q = std::pow(p * p + q * q, 1.5) * std::sin(3 * std::atan2l(q, p)) + Var.b;
				p = w;

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
					double log_zn = std::log(p * p + q * q) / 2;
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
				Data[y * Width + x] = std::sqrt(std::pow(p + q, 2));

				if (Data[y * Width + x] > max_d) max_d = Data[y * Width + x];

				Iteration[y * Width + x] = it;
				break;
			}
			case 3:
				int nx = std::floor(x - (Width / 2));
				int ny = std::floor(y - (Height / 2));

				int index = std::floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((double)it / max_iterations, n_coeff)) * __PaletteCount);
				Canvas[y * Width + x] = index;

				break;
			}
		}
	}

	switch (RenderMode)
	{
	case 0:
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
					Canvas[y * Width + x] = __PaletteInfinity;
				}
				else
				{
					int it = Iteration[y * Width + x] - min;

					int index = std::round(std::pow((double)it / ((double)max - (double)min), n_coeff) * __PaletteCount);

					Canvas[y * Width + x] = index;
				}
			}
		}
		break;
	}
	case 2:                                                                     // distance II
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


void JuliaCubic::ColourDistanceII(double max_d)
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


void JuliaCubic::ResetView()
{
	ymin = -2.0;
	ymax =  2.0;
	xmin = -2.0;
	xmax =  2.0;
}


void JuliaCubic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Julie Set (Cubic)\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + std::to_wstring(RenderMode) + L"\n");
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
