//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2026
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Orbit_trap
// z -> z^n + c


#include <string>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "MandelbrotNtic.h"


MandelbrotNtic::MandelbrotNtic() : Fractal()
{
	Name = L"Mandelbrot z^n";

	NumIterationsPerPixel = new int[2001];
	for (int z = 0; z < 2001; z++) NumIterationsPerPixel[z] = 0;

	AcceptsMorph = true;
	HasTests = true;

	Defaults.Set(1, 100, 4, 0, 0, 5, 0, 0);

	MultiThread = true;

	Parameters.push_back(RenderModeParameters(L"Escape time", L"n", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Continuous", L"n", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Distance", L"n", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Distance II", L"n", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Orbit Trap", L"n", L"orbit x", L"orbit y", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Orbit Trap (filled)", L"n", L"orbit x", L"orbit y", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Two-tone", L"n", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Three-tone", L"n", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Four-tone", L"n", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Five-tone", L"n", L"", L"", L"", L""));

	Tests.push_back(L"Re(z)^2 + Im(z)^2 < n");
	Tests.push_back(L"||Re(z)^2| - |Im(z)^2|| < n");
	Tests.push_back(L"|Re(z)^2 - Im(z)^2| < n");
	Tests.push_back(L"Re(z)^2 * Im(z)^2 < n");
	Tests.push_back(L"|Re(z)^2| + |Im(z)^2| < n");

	MorphNameA = L"orbit x";
	MorphNameB = L"orbit y";

	ResetAll();
}


MandelbrotNtic::~MandelbrotNtic()
{
	delete NumIterationsPerPixel;
}



bool MandelbrotNtic::MultiThreadRender(bool preview, bool super_sample, bool morph)
{
	StartTime = std::chrono::system_clock::now();

	if (preview) SwapDimensions();

	if (RenderMode == __RMMandelbrotEscapeTime)
	{
		for (int z = 0; z < max_iterations; z++) NumIterationsPerPixel[z] = 0;
	}

	if (super_sample)
	{
		if (morph)
		{
			MTSSMorph();
		}
		else
		{
			MTSS();
		}
	}
	else
	{
		if (morph)
		{
			MTMorph();
		}
		else
		{
			MT();
		}
	}

	if (preview)
	{
		FinaliseRenderMandelbrot(PreviewCanvas);

		SwapDimensions();
	}
	else
	{
		FinaliseRenderMandelbrot(RenderCanvas);
	}

	CalculateRenderTime();

	return true;
}


void MandelbrotNtic::RenderSS(int hstart, int hend)
{
	long double halfn = Var.a / 2;

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			FractalData[ydotwidth + x].Clear();

			for (int ss = 0; ss < supersamples; ss++)
			{
				long double p = xmin + ((long double)x + (0.5 - (rand() / (RAND_MAX + 1.0)))) * (xmax - xmin) / (long double)Width;    // real part
				long double q = ymin + ((long double)y + (0.5 - (rand() / (RAND_MAX + 1.0)))) * (ymax - ymin) / (long double)Height;   // imaginary part

				int it = 0;

				Data[ydotwidth + x] = 10000000000000;
				long double x1 = 0;
				long double y1 = 0;
				long double x2 = 0;
				long double y2 = 0;

				while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
				{
					long double atan2pq = Var.a * std::atan2(y1, x1);
					long double pown = exp(halfn * log(x2 + y2));

					x1 = pown * std::cos(atan2pq) + p;
					y1 = pown * std::sin(atan2pq) + q;

					x2 = x1 * x1;
					y2 = y1 * y1;

					if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
					{
						long double cr = p - Var.b;
						long double ci = q - Var.c;

						long double magnitude = std::sqrt(cr * cr + ci * ci);

						if (magnitude < Data[ydotwidth + x])
						{
							Data[ydotwidth + x] = magnitude;
						}
					}

					it++;
				}

				MandelbrotColourise(it, ydotwidth + x, x1, y1, x2, y2, p, q);
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void MandelbrotNtic::RenderSSMorph(int hstart, int hend)
{
	long double halfn = Var.a / 2;

	long double vara = Var.b;
	long double varb = Var.c;

	if (MorphType == 0)
	{
		if (MorphA) vara = Var.b + (hstart * Var.morph_a);
		if (MorphB) varb = Var.c + (hstart * Var.morph_b);
	}

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		if (MorphType == 0)
		{
			if (MorphA) vara += Var.morph_a;
			if (MorphB) varb += Var.morph_b;
		}

		for (int x = 0; x < Width; x++)
		{
			FractalData[ydotwidth + x].Clear();

			for (int ss = 0; ss < supersamples; ss++)
			{
				long double deltax = 0.5 - (rand() / (RAND_MAX + 1.0));
				long double deltay = 0.5 - (rand() / (RAND_MAX + 1.0));

				long double p = xmin + ((long double)x + deltax) * (xmax - xmin) / (long double)Width;    // real part
				long double q = ymin + ((long double)y + deltay) * (ymax - ymin) / (long double)Height;   // imaginary part

				if (MorphType == 1)
				{
					long double xp = std::abs(((long double)Width / 2) - (long double)x + deltax);
					long double yp = std::abs(((long double)Height / 2) - (long double)y + deltay);

					if (MorphA) vara = Var.b + std::sqrt(xp * xp + yp * yp) * Var.morph_a;
					if (MorphB) varb = Var.c + std::sqrt(xp * xp + yp * yp) * Var.morph_b;
				}
				else if (MorphType == 2)
				{
					if (MorphA)	vara = Var.b + std::sqrt(p * p + q * q) * Var.morph_a;
					if (MorphB)	varb = Var.c + std::sqrt(p * p + q * q) * Var.morph_b;
				}

				int it = 0;

				Data[ydotwidth + x] = 10000000000000;
				long double x1 = 0;
				long double y1 = 0;
				long double x2 = 0;
				long double y2 = 0;

				while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
				{
					long double atan2pq = Var.a * std::atan2(y1, x1);
					long double pown = exp(halfn * log(x2 + y2));

					x1 = pown * std::cos(atan2pq) + p;
					y1 = pown * std::sin(atan2pq) + q;

					x2 = x1 * x1;
					y2 = y1 * y1;

					if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
					{
						long double cr = p - vara;
						long double ci = q - varb;

						long double magnitude = std::sqrt(cr * cr + ci * ci);

						if (magnitude < Data[ydotwidth + x])
						{
							Data[ydotwidth + x] = magnitude;
						}
					}

					it++;
				}

				MandelbrotColourise(it, ydotwidth + x, x1, y1, x2, y2, p, q);
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void MandelbrotNtic::Render(int hstart, int hend)
{
	long double halfn = Var.a / 2;

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		long double q = ymin + (long double)y * (ymax - ymin) / (long double)Height;   // imaginary part

		for (int x = 0; x < Width; x++)
		{
			long double p = xmin + (long double)x * (xmax - xmin) / (long double)Width;    // real part

			int it = 0;

			Data[ydotwidth + x] = 10000000000000;
			long double x1 = 0;
			long double y1 = 0;
			long double x2 = 0;
			long double y2 = 0;

			while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
			{
				long double atan2pq = Var.a * std::atan2(y1, x1);
				long double pown = exp(halfn * log(x2 + y2));

				x1 = pown * std::cos(atan2pq) + p;
				y1 = pown * std::sin(atan2pq) + q;

				x2 = x1 * x1;
				y2 = y1 * y1;

				if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
				{
					long double cr = p - Var.b;
					long double ci = q - Var.c;

					long double magnitude = std::sqrt(cr * cr + ci * ci);

					if (magnitude < Data[ydotwidth + x])
					{
						Data[ydotwidth + x] = magnitude;
					}
				}

				it++;
			}

			MandelbrotColourise(it, ydotwidth + x, x1, y1, x2, y2, p, q);
		}
	}
}


void MandelbrotNtic::RenderMorph(int hstart, int hend)
{
	long double halfn = Var.a / 2;

	long double vara = Var.b;
	long double varb = Var.c;

	if (MorphType == 0)
	{
		if (MorphA) vara = Var.b + (hstart * Var.morph_a);
		if (MorphB) varb = Var.c + (hstart * Var.morph_b);
	}

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		if (MorphType == 0)
		{
			if (MorphA) vara += Var.morph_a;
			if (MorphB) varb += Var.morph_b;
		}

		long double q = ymin + (long double)y * (ymax - ymin) / (long double)Height;   // imaginary part

		for (int x = 0; x < Width; x++)
		{
			long double p = xmin + (long double)x * (xmax - xmin) / (long double)Width;    // real part

			if (MorphType == 1)
			{
				long double xp = std::abs(((long double)Width / 2) - (long double)x);
				long double yp = std::abs(((long double)Height / 2) - (long double)y);

				if (MorphA) vara = Var.b + std::sqrt(xp * xp + yp * yp) * Var.morph_a;
				if (MorphB) varb = Var.c + std::sqrt(xp * xp + yp * yp) * Var.morph_b;
			}
			else if (MorphType == 2)
			{
				if (MorphA)	vara = Var.b + std::sqrt(p * p + q * q) * Var.morph_a;
				if (MorphB)	varb = Var.c + std::sqrt(p * p + q * q) * Var.morph_b;
			}

			int it = 0;

			Data[ydotwidth + x] = 10000000000000;
			long double x1 = 0;
			long double y1 = 0;
			long double x2 = 0;
			long double y2 = 0;

			while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
			{
				long double atan2pq = Var.a * std::atan2(y1, x1);
				long double pown = exp(halfn * log(x2 + y2));

				x1 = pown * std::cos(atan2pq) + p;
				y1 = pown * std::sin(atan2pq) + q;

				x2 = x1 * x1;
				y2 = y1 * y1;

				if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
				{
					long double cr = p - vara;
					long double ci = q - varb;

					long double magnitude = std::sqrt(cr * cr + ci * ci);

					if (magnitude < Data[ydotwidth + x])
					{
						Data[ydotwidth + x] = magnitude;
					}
				}

				it++;
			}

			MandelbrotColourise(it, ydotwidth + x, x1, y1, x2, y2, p, q);
		}
	}
}


void MandelbrotNtic::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);

	Var.a = 5;
	Var.b = xmin + ((xmax - xmin) / 2);     // set orbit trap position to centre of view
	Var.c = ymin + ((ymax - ymin) / 2);     //
}


std::wstring MandelbrotNtic::GetParameters()
{
	return L"Mandelbrot (z^n): x " + Formatting::LDToStr(xmin) + L" <-> " + Formatting::LDToStr(xmax) + L", y " + Formatting::LDToStr(ymin) + L" <-> " + Formatting::LDToStr(ymax) +
		   L"; render mode: " + Parameters[RenderMode].Name +
		   L"; ^n: " + std::to_wstring(Var.a) + L"; orbit x: " + std::to_wstring(Var.b) + L"; orbit y " + std::to_wstring(Var.c) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring MandelbrotNtic::Description()
{
	return L"Mandelbrot (z^n): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


std::wstring MandelbrotNtic::HistoryEntry()
{
	return L"Mandelbrot (z^n): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


void MandelbrotNtic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Mandelbrot (z^n) fractal\n");
   	ofile << Formatting::to_utf8(L"    ^n         : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + Parameters[RenderMode].Name + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    r bailout  : " + std::to_wstring(bailout_radius) + L"\n\n");

	ofile << Formatting::to_utf8(L"    x min      : " + Formatting::LDToStr(xmin) + L"\n");
	ofile << Formatting::to_utf8(L"    x max      : " + Formatting::LDToStr(xmax) + L"\n");
	ofile << Formatting::to_utf8(L"    y min      : " + Formatting::LDToStr(ymin) + L"\n");
	ofile << Formatting::to_utf8(L"    y max      : " + Formatting::LDToStr(ymax) + L"\n");

	if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
	{
		ofile << Formatting::to_utf8(L"    Orbit x    : " + Formatting::LDToStr(Var.b) + L"\n");
		ofile << Formatting::to_utf8(L"    Orbit y    : " + Formatting::LDToStr(Var.c) + L"\n");
	}
}

