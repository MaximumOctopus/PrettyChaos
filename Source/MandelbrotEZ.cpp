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
// z -> e^z + c
// e^z = e^a(cos b + isin(b))

#include <string>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "MandelbrotEZ.h"


MandelbrotEZ::MandelbrotEZ() : Fractal()
{
	Name = L"Mandelbrot e^z";

	NumIterationsPerPixel = new int[2001];
	for (int z = 0; z < 2001; z++) NumIterationsPerPixel[z] = 0;

	AcceptsMorph = true;
	HasTests = true;

	MultiThread = true;

	Defaults.Set(1, 450, 500, 0, 0, 0, 1000, 0);

	Parameters.push_back(RenderModeParameters(L"Escape time", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Continuous", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Distance", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Distance II", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Orbit Trap", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Orbit Trap (filled)", L"orbit x", L"orbit y", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Two-tone", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Three-tone", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Four-tone", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"Five-tone", L"", L"", L"", L"", L""));
	Parameters.push_back(RenderModeParameters(L"XOR", L"", L"", L"", L"Coeff", L""));
	Parameters.push_back(RenderModeParameters(L"XOR II", L"", L"", L"", L"Coeff", L""));
	Parameters.push_back(RenderModeParameters(L"XOR III", L"", L"", L"", L"Coeff", L""));
	Parameters.push_back(RenderModeParameters(L"Test", L"", L"", L"", L"", L""));

	Tests.push_back(L"Re(z)^2 + Im(z)^2 < n");
	Tests.push_back(L"||Re(z)^2| - |Im(z)^2|| < n");
	Tests.push_back(L"|Re(z)^2 - Im(z)^2| < n");
	Tests.push_back(L"Re(z)^2 * Im(z)^2 < n");
	Tests.push_back(L"|Re(z)^2| + |Im(z)^2| < n");

	MorphNameA = L"orbit x";
	MorphNameB = L"orbit y";

	ResetAll();
}


MandelbrotEZ::~MandelbrotEZ()
{
	delete NumIterationsPerPixel;
}



bool MandelbrotEZ::MultiThreadRender(bool preview, bool super_sample, bool morph)
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


void MandelbrotEZ::RenderSS(int hstart, int hend)
{
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
				long double expx = exp(x1);
				long double m = 0;

				while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
				{
					m = expx * cos(y1) + p;
					y1 = expx * sin(y1) + q;

					x1 = m;
					expx = exp(x1);

					x2 = x1 * x1;
					y2 = y1 * y1;

					if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
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

				MandelbrotColouriseSS(it, ydotwidth + x, x1, y1, x2, y2, p, q);
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void MandelbrotEZ::RenderSSMorph(int hstart, int hend)
{
	long double vara = Var.a;
	long double varb = Var.b;

	if (MorphType == 0)
	{
		if (MorphA) vara = Var.a + (hstart * Var.morph_a);
		if (MorphB) varb = Var.b + (hstart * Var.morph_b);
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

					if (MorphA) vara = Var.a + std::sqrt(xp * xp + yp * yp) * Var.morph_a;
					if (MorphB) varb = Var.b + std::sqrt(xp * xp + yp * yp) * Var.morph_b;
				}
				else if (MorphType == 2)
				{
					if (MorphA)	vara = Var.a + std::sqrt(p * p + q * q) * Var.morph_a;
					if (MorphB)	varb = Var.b + std::sqrt(p * p + q * q) * Var.morph_b;
				}

				int it = 0;

				Data[ydotwidth + x] = 10000000000000;
				long double x1 = 0;
				long double y1 = 0;
				long double x2 = 0;
				long double y2 = 0;
				long double expx = exp(x1);
				long double m = 0;

				while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
				{
					m = expx * cos(y1) + p;
					y1 = expx * sin(y1) + q;

					x1 = m;
					expx = exp(x1);

					x2 = x1 * x1;
					y2 = y1 * y1;

					if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
					{
						long double cr = x1 - vara;
						long double ci = y1 - varb;

						long double magnitude = std::sqrt(cr * cr + ci * ci);

						if (magnitude < Data[ydotwidth + x])
						{
							Data[ydotwidth + x] = magnitude;
						}
					}

					it++;
				}

				MandelbrotColouriseSS(it, ydotwidth + x, x1, y1, x2, y2, p, q);
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void MandelbrotEZ::Render(int hstart, int hend)
{
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
			long double expx = exp(x1);
			long double m = 0;

			while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
			{
				m = expx * cos(y1) + p;
				y1 = expx * sin(y1) + q;

				x1 = m;
				expx = exp(x1);

				x2 = x1 * x1;
				y2 = y1 * y1;

				if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
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

			MandelbrotColourise(it, ydotwidth + x, x1, y1, x2, y2, p, q);
		}
	}
}


void MandelbrotEZ::RenderMorph(int hstart, int hend)
{
	long double vara = Var.a;
	long double varb = Var.b;

	if (MorphType == 0)
	{
		if (MorphA) vara = Var.a + (hstart * Var.morph_a);
		if (MorphB) varb = Var.b + (hstart * Var.morph_b);
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

				if (MorphA) vara = Var.a + std::sqrt(xp * xp + yp * yp) * Var.morph_a;
				if (MorphB) varb = Var.b + std::sqrt(xp * xp + yp * yp) * Var.morph_b;
			}
			else if (MorphType == 2)
			{
				if (MorphA)	vara = Var.a + std::sqrt(p * p + q * q) * Var.morph_a;
				if (MorphB)	varb = Var.b + std::sqrt(p * p + q * q) * Var.morph_b;
			}

			int it = 0;

			Data[ydotwidth + x] = 10000000000000;
			long double x1 = 0;
			long double y1 = 0;
			long double x2 = 0;
			long double y2 = 0;
			long double expx = exp(x1);
			long double m = 0;

			while (MandelbrotTest(x1, y1, x2, y2) && it < max_iterations)
			{
				m = expx * cos(y1) + p;
				y1 = expx * sin(y1) + q;

				x1 = m;
				expx = exp(x1);

				x2 = x1 * x1;
				y2 = y1 * y1;

				if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
				{
					long double cr = x1 - vara;
					long double ci = y1 - varb;

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


void MandelbrotEZ::ResetView()
{
	SetView(-2.50, 5.00, -3.0, 3.0);

	Var.a = xmin + ((xmax - xmin) / 2);     // set orbit trap position to centre of view
	Var.b = ymin + ((ymax - ymin) / 2);     //
}


std::wstring MandelbrotEZ::GetParameters()
{
	return L"Mandelbrot (e^z): x " + Formatting::LDToStr(xmin) + L" <-> " + Formatting::LDToStr(xmax) + L", y " + Formatting::LDToStr(ymin) + L" <-> " + Formatting::LDToStr(ymax) +
		   L"; render mode: " + Parameters[RenderMode].Name +
		   L"; orbit x: " + std::to_wstring(Var.a) + L"; orbit y " + std::to_wstring(Var.b) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring MandelbrotEZ::Description()
{
	return L"MandelbrotEZ (e^z): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


std::wstring MandelbrotEZ::HistoryEntry()
{
	return L"MandelbrotEZ (e^z): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


void MandelbrotEZ::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Mandelbrot (e^z) fractal\n");
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
		ofile << Formatting::to_utf8(L"    Orbit x    : " + Formatting::LDToStr(Var.a) + L"\n");
		ofile << Formatting::to_utf8(L"    Orbit y    : " + Formatting::LDToStr(Var.b) + L"\n");
	}
}
