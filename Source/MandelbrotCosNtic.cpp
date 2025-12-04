//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Orbit_trap
// z -> Cos(z^n + c)


#include <string>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "MandelbrotCosNtic.h"


MandelbrotCosNtic::MandelbrotCosNtic() : Fractal()
{
	Name = L"Mandelbrot Cos(z^n)";

	NumIterationsPerPixel = new int[2001];
	for (int z = 0; z < 2001; z++) NumIterationsPerPixel[z] = 0;

	AcceptsABC = true;
    AcceptsMorph = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;

	Defaults.Set(1, 100, 4, 0, 0, 5, 0, 0);

	MultiThread = true;

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
	NameC = L"n";

	ResetAll();
}


MandelbrotCosNtic::~MandelbrotCosNtic()
{
	delete NumIterationsPerPixel;
}


bool MandelbrotCosNtic::MultiThreadRender(bool preview, bool super_sample, bool morph)
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


void MandelbrotCosNtic::RenderSS(int hstart, int hend)
{
	long double halfn = Var.c / 2;

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
				long double m = 0;

				while (x2 + y2 <= bailout_radius && it < max_iterations)
				{
					long double atan2pq = Var.c * std::atan2(y1, x1);
					long double pown = std::pow(x2 + y2, halfn);

					m = pown * std::cos(atan2pq) + p;
					y1 = pown * std::sin(atan2pq) + q;

					x1 = std::cos(m) * std::cosh(y1);
					y1 = -(std::sin(m) * std::sinh(y1));

					x2 = x1 * x1;
					y2 = y1 * y1;

					if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
					{
						long double cr = p - Var.a;
						long double ci = q - Var.b;

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
				case __RMMandelbrotEscapeTime:
				case __RMMandelbrotOrbitTrap:
				case __RMMandelbrotOrbitTrapFilled:
				case __RMMandelbrotTwoTone:
				case __RMMandelbrotThreeTone:
				case __RMMandelbrotFourTone:
				case __RMMandelbrotFiveTone:
				{
					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMMandelbrotContinuous:
				{
					if (it < max_iterations)
					{
						long double log_zn = std::log(x2 + y2) / 0.60205999132796239042747778944899;    // 2 * log(2)
						long double nu = 1 - std::log2(log_zn);

						long double itnew = it + nu;

						it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
						long double it_d = (long double)it + nu;

						FractalData[ydotwidth + x] += ColourUtility::LinearInterpolate(pp->Colours[it],
																					   pp->Colours[it + 1],
																					   it_d - (std::floorl(it_d)));
					}
					else
					{
						FractalData[ydotwidth + x].a = -1;
					}

					break;
				}
				case __RMMandelbrotDistance:
				{
					if (it < max_iterations)
					{
						Data[ydotwidth + x] = std::sqrt((x1 + y1) * (x1 + y1));
					}
					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMMandelbrotDistanceII:
				{
					if (it < max_iterations)
					{
						Data[ydotwidth + x] = std::sqrt(x2 + y2 * x2 + y2);
					}
					FractalData[ydotwidth + x].a += it;
					break;
				}
				}
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void MandelbrotCosNtic::RenderSSMorph(int hstart, int hend)
{
	long double halfn = Var.c / 2;

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
				long double m = 0;

				while (x2 + y2 <= bailout_radius && it < max_iterations)
				{
					long double atan2pq = Var.c * std::atan2(y1, x1);
					long double pown = std::pow(x2 + y2, halfn);

					m = pown * std::cos(atan2pq) + p;
					y1 = pown * std::sin(atan2pq) + q;

					x1 = std::cos(m) * std::cosh(y1);
					y1 = -(std::sin(m) * std::sinh(y1));

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

				switch (RenderMode)
				{
				case __RMMandelbrotEscapeTime:
				case __RMMandelbrotOrbitTrap:
				case __RMMandelbrotOrbitTrapFilled:
				case __RMMandelbrotTwoTone:
				case __RMMandelbrotThreeTone:
				case __RMMandelbrotFourTone:
				case __RMMandelbrotFiveTone:
				{
					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMMandelbrotContinuous:
				{
					if (it < max_iterations)
					{
						long double log_zn = std::log(x2 + y2) / 0.60205999132796239042747778944899;    // 2 * log(2)
						long double nu = 1 - std::log2(log_zn);

						long double itnew = it + nu;

						it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
						long double it_d = (long double)it + nu;

						FractalData[ydotwidth + x] += ColourUtility::LinearInterpolate(pp->Colours[it],
																					   pp->Colours[it + 1],
																					   it_d - (std::floorl(it_d)));
					}
					else
					{
						FractalData[ydotwidth + x].a = -1;
					}

					break;
				}
				case __RMMandelbrotDistance:
				{
					if (it < max_iterations)
					{
						Data[ydotwidth + x] = std::sqrt((x1 + y1) * (x1 + y1));
					}
					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMMandelbrotDistanceII:
				{
					if (it < max_iterations)
					{
						Data[ydotwidth + x] = std::sqrt(x2 + y2 * x2 + y2);
					}
					FractalData[ydotwidth + x].a += it;
					break;
				}
				}
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void MandelbrotCosNtic::Render(int hstart, int hend)
{
	long double halfn = Var.c / 2;

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
			long double m = 0;

			while (x2 + y2 <= bailout_radius && it < max_iterations)
			{
				long double atan2pq = Var.c * std::atan2(y1, x1);
				long double pown = std::pow(x2 + y2, halfn);

				m = pown * std::cos(atan2pq) + p;
				y1 = pown * std::sin(atan2pq) + q;

				x1 = std::cos(m) * std::cosh(y1);
				y1 = -(std::sin(m) * std::sinh(y1));

				x2 = x1 * x1;
				y2 = y1 * y1;

				if (RenderMode == __RMMandelbrotOrbitTrap || RenderMode == __RMMandelbrotOrbitTrapFilled)
				{
					long double cr = p - Var.a;
					long double ci = q - Var.b;

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
			case __RMMandelbrotEscapeTime:
			case __RMMandelbrotOrbitTrap:
			case __RMMandelbrotOrbitTrapFilled:
			case __RMMandelbrotTwoTone:
			case __RMMandelbrotThreeTone:
			case __RMMandelbrotFourTone:
			case __RMMandelbrotFiveTone:
			{
				FractalData[ydotwidth + x].a = it;
				break;
			}
			case __RMMandelbrotContinuous:
			{
				if (it < max_iterations)
				{
					long double log_zn = std::log(x2 + y2) / 0.60205999132796239042747778944899;    // 2 * log(2)
					long double nu = 1 - std::log2(log_zn);

					long double itnew = it + nu;

					it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
					long double it_d = (long double)it + nu;

					FractalData[ydotwidth + x] = ColourUtility::LinearInterpolate(pp->Colours[it],
																				  pp->Colours[it + 1],
																				  it_d - (std::floorl(it_d)));
				}
				else
				{
					FractalData[ydotwidth + x].a = -1;
				}

				break;
			}
			case __RMMandelbrotDistance:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt((x1 + x2) * (x1 + x2));
				}

				FractalData[ydotwidth + x].a = it;
				break;
			}
			case __RMMandelbrotDistanceII:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(x2 + y2 * x2 + y2);
				}

				FractalData[ydotwidth + x].a = it;
				break;
			}
			}
		}
	}
}


void MandelbrotCosNtic::RenderMorph(int hstart, int hend)
{
	long double halfn = Var.c / 2;

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
			long double m = 0;

			while (x2 + y2 <= bailout_radius && it < max_iterations)
			{
				long double atan2pq = Var.c * std::atan2(y1, x1);
				long double pown = std::pow(x2 + y2, halfn);

				m = pown * std::cos(atan2pq) + p;
				y1 = pown * std::sin(atan2pq) + q;

				x1 = std::cos(m) * std::cosh(y1);
				y1 = -(std::sin(m) * std::sinh(y1));

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

			switch (RenderMode)
			{
			case __RMMandelbrotEscapeTime:
			case __RMMandelbrotOrbitTrap:
			case __RMMandelbrotOrbitTrapFilled:
			case __RMMandelbrotTwoTone:
			case __RMMandelbrotThreeTone:
			case __RMMandelbrotFourTone:
			case __RMMandelbrotFiveTone:
			{
				FractalData[ydotwidth + x].a = it;
				break;
			}
			case __RMMandelbrotContinuous:
			{
				if (it < max_iterations)
				{
					long double log_zn = std::log(x2 + y2) / 0.60205999132796239042747778944899;    // 2 * log(2)
					long double nu = 1 - std::log2(log_zn);

					long double itnew = it + nu;

					it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
					long double it_d = (long double)it + nu;

					FractalData[ydotwidth + x] = ColourUtility::LinearInterpolate(pp->Colours[it],
																				  pp->Colours[it + 1],
																				  it_d - (std::floorl(it_d)));
				}
				else
				{
					FractalData[ydotwidth + x].a = -1;
				}

				break;
			}
			case __RMMandelbrotDistance:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt((x1 + x2) * (x1 + x2));
				}

				FractalData[ydotwidth + x].a = it;
				break;
			}
			case __RMMandelbrotDistanceII:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(x2 + y2 * x2 + y2);
				}

				FractalData[ydotwidth + x].a = it;
				break;
			}
			}
		}
	}
}


void MandelbrotCosNtic::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);

	Var.a = xmin + ((xmax - xmin) / 2);     // set orbit trap position to centre of view
	Var.b = ymin + ((ymax - ymin) / 2);     //
    Var.c = 5;
}


std::wstring MandelbrotCosNtic::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; orbit x: " + std::to_wstring(Var.a) + L"; orbit y " + std::to_wstring(Var.b) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring MandelbrotCosNtic::Description()
{
	return L"Mandelbrot (Cos(z^n)): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


std::wstring MandelbrotCosNtic::HistoryEntry()
{
	return L"Mandelbrot (Cos(z^n)): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


void MandelbrotCosNtic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Mandelbrot Cos(z^n) fractal\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
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
