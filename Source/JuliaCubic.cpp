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

#include "JuliaCubic.h"


JuliaCubic::JuliaCubic() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

    bailout_radius = 4;

	Var.a = -0.7;
	Var.b = 0.27015;

	Name = L"JuliaCubic Set";

	RenderModes.push_back(L"Escape time");
	RenderModes.push_back(L"Continuous");
	RenderModes.push_back(L"Two-tone");
	RenderModes.push_back(L"Three-tone");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance from origin");

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

	if (RenderMode == 4) Distances = new double[Width * Height];

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
					double log_zn = std::log(p * p + q * q) / 2;
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
				Distances[y * Width + x] = std::sqrt(std::pow(p + q, 2));

				if (Distances[y * Width + x] > max_d) max_d = Distances[y * Width + x];

				Iteration[y * Width + x] = it;
				break;
			}
			case 5:
				int nx = std::floor(x - (Width / 2));
				int ny = std::floor(y - (Height / 2));

				int index = std::floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((double)it / max_iterations, n_coeff)) * 500);
				Canvas[y * Width + x] = Palette[index];

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
		break;
	}
	case 2:                                                                     // two-tone
		ColourTwoTone();
		break;
	case 3:                                                                     // three-tone
		ColourThreeTone();
		break;
	case 4:                                                                     // distance II
		ColourDistanceII(max_d);
		break;
	}

	CalculateRenderTime();
}


void JuliaCubic::ColourTwoTone()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
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
	}
}


void JuliaCubic::ColourThreeTone()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
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
	}
}


void JuliaCubic::ColourDistanceII(double max_d)
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


void JuliaCubic::ResetView()
{
	ymin = -2.0;
	ymax =  2.0;
	xmin = -2.0;
	xmax =  2.0;
}
