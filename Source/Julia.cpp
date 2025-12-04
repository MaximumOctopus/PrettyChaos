//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <string>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "Julia.h"


Julia::Julia() : Fractal()
{
	AcceptsABC = true;
	AcceptsMorph = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

	MultiThread = true;

	Defaults.Set(1, 1000, 4, -0.7, 0.27015, 0, 0, 0);

	QPM = QuickParameterMode::kABPlusFine;

	Name = L"Julia Set";

	RenderModes.push_back(L"Escape time");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance from origin");
	RenderModes.push_back(L"Two-tone");
	RenderModes.push_back(L"Three-tone");
	RenderModes.push_back(L"Four-tone");
	RenderModes.push_back(L"Five-tone");
	RenderModes.push_back(L"Continuous");

	NameA = L"real";
	NameB = L"imaginary";

	ResetAll();
}


Julia::~Julia()
{
}


bool Julia::MultiThreadRender(bool preview, bool super_sample, bool morph)
{
	// nothing to render, point isn't valid
	if (PointGoesToInfinity(Var.a, Var.b))
	{
		return false;
	}

	if (preview) SwapDimensions();

	StartTime = std::chrono::system_clock::now();

	// maximum distance from the centre of the image
	int maxdim = Fast::Floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

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
		FinaliseRenderJulia(PreviewCanvas);

		SwapDimensions();
	}
	else
	{
		FinaliseRenderJulia(RenderCanvas);
	}

	CalculateRenderTime();

	return true;
}


void Julia::Render(int hstart, int hend)
{
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
				w = p * p - q * q + Var.a;
				q = 2 * p * q + Var.b;

				p = w;

				it++;
			}

			switch (RenderMode)
			{
			case __RMJuliaEscapeTime:
			case __RMJuliaTwoTone:
			case __RMJuliaThreeTone:
			case __RMJuliaFourTone:
			case __RMJuliaFiveTone:
			{
				FractalData[ydotwidth + x].a = it;
				break;
			}
			case __RMJuliaDistance:
			{
				Data[ydotwidth + x] = std::sqrt((p + q) * (p + q));

				FractalData[ydotwidth + x].a = it;

				break;
			}
			case __RMJuliaDistanceOrigin:
			{
				int nx = Fast::Floor(x - (Width / 2));
				int ny = Fast::Floor(y - (Height / 2));

				int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

				FractalData[ydotwidth + x] = pp->Colours[index];
				break;
			}
			case __RMJuliaContinuous:
			{
				if (it < max_iterations)
				{
					long double log_zn = std::log(p * p + q * q) / 0.60205999132796239042747778944899;    // 2 * log(2)
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
					FractalData[ydotwidth + x] = pp2->SingleColour;
				}

				break;
			}
			}
		}
	}
}


void Julia::RenderMorph(int hstart, int hend)
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
			long double p = xmin + (long double)x * (xmax - xmin) / (long double)Width;    // real part
			long double q = ymin + (long double)y * (ymax - ymin) / (long double)Height;   // imaginary part

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

			long double w = 0;

			while (p * p + q * q <= bailout_radius && it < max_iterations)
			{
				w = p * p - q * q + vara;
				q = 2 * p * q + varb;

				p = w;

				it++;
			}

			switch (RenderMode)
			{
			case __RMJuliaEscapeTime:
			case __RMJuliaTwoTone:
			case __RMJuliaThreeTone:
			case __RMJuliaFourTone:
			case __RMJuliaFiveTone:
			{
				FractalData[ydotwidth + x].a = it;
				break;
			}
			case __RMJuliaDistance:
			{
				Data[ydotwidth + x] = std::sqrt((p + q) * (p + q));

				FractalData[ydotwidth + x].a = it;

				break;
			}
			case __RMJuliaDistanceOrigin:
			{
				int nx = Fast::Floor(x - (Width / 2));
				int ny = Fast::Floor(y - (Height / 2));

				int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

				FractalData[ydotwidth + x] = pp->Colours[index];
				break;
			}
			case __RMJuliaContinuous:
			{
				if (it < max_iterations)
				{
					long double log_zn = std::log(p * p + q * q) / 0.60205999132796239042747778944899;    // 2 * log(2)
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
					FractalData[ydotwidth + x] = pp2->SingleColour;
				}

				break;
			}
			}
		}
	}
}


void Julia::RenderSS(int hstart, int hend)
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

				long double w = 0;

				while (p * p + q * q <= bailout_radius && it < max_iterations)
				{
					w = p * p - q * q + Var.a;
					q = 2 * p * q + Var.b;

					p = w;

					it++;
				}

				switch (RenderMode)
				{
				case __RMJuliaEscapeTime:
				case __RMJuliaTwoTone:
				case __RMJuliaThreeTone:
				case __RMJuliaFourTone:
				case __RMJuliaFiveTone:
				{
					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMJuliaDistance:
				{
					Data[ydotwidth + x] = std::sqrt((p + q) * (p + q));

					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMJuliaDistanceOrigin:
				{
					int nx = Fast::Floor(x - (Width / 2));
					int ny = Fast::Floor(y - (Height / 2));

					int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

					FractalData[ydotwidth + x] += pp->Colours[index];
					break;
				}
				case __RMJuliaContinuous:
				{
					if (it < max_iterations)
					{
						long double log_zn = std::log(p * p + q * q) / 0.60205999132796239042747778944899;    // 2 * log(2)
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
						FractalData[ydotwidth + x] += pp2->SingleColour;
					}

					break;
				}
				}
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void Julia::RenderSSMorph(int hstart, int hend)
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

				long double w = 0;

				while (p * p + q * q <= bailout_radius && it < max_iterations)
				{
					w = p * p - q * q + vara;
					q = 2 * p * q + varb;

					p = w;

					it++;
				}

				switch (RenderMode)
				{
				case __RMJuliaEscapeTime:
				case __RMJuliaTwoTone:
				case __RMJuliaThreeTone:
				case __RMJuliaFourTone:
				case __RMJuliaFiveTone:
				{
					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMJuliaDistance:
				{
					Data[ydotwidth + x] = std::sqrt((p + q) * (p + q));

					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMJuliaDistanceOrigin:
				{
					int nx = Fast::Floor(x - (Width / 2));
					int ny = Fast::Floor(y - (Height / 2));

					int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

					FractalData[ydotwidth + x] += pp->Colours[index];
					break;
				}
				case __RMJuliaContinuous:
				{
					if (it < max_iterations)
					{
						long double log_zn = std::log(p * p + q * q) / 0.60205999132796239042747778944899;    // 2 * log(2)
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
						FractalData[ydotwidth + x] += pp2->SingleColour;
					}

					break;
				}
				}
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void Julia::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);
}


std::wstring Julia::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; real: " + std::to_wstring(Var.a) + L"; imaginary " + std::to_wstring(Var.b) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring Julia::Description()
{
	return L"Julia (z^2): " + Formatting::LDToStr(Var.a) + L" + " + Formatting::LDToStr(Var.b) + L"i; " + Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


std::wstring Julia::HistoryEntry()
{
	return L"Julia (z^2): " + Formatting::LDToStr(Var.a) + L" + " + Formatting::LDToStr(Var.b) + L"i; " + Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


void Julia::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Julia Set (z^2)\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    r bailout  : " + std::to_wstring(bailout_radius) + L"\n\n");
	ofile << Formatting::to_utf8(L"    a          : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    b          : " + std::to_wstring(Var.b) + L"\n\n");

	ofile << Formatting::to_utf8(L"    x min      : " + Formatting::LDToStr(xmin) + L"\n");
	ofile << Formatting::to_utf8(L"    x max      : " + Formatting::LDToStr(xmax) + L"\n");
	ofile << Formatting::to_utf8(L"    y min      : " + Formatting::LDToStr(ymin) + L"\n");
	ofile << Formatting::to_utf8(L"    y max      : " + Formatting::LDToStr(ymax) + L"\n");
}
