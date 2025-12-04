//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Julia_set

#include <string>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "JuliaNtic.h"


JuliaNtic::JuliaNtic() : Fractal()
{
	AcceptsABC = true;
	AcceptsMorph = true;
	AcceptsVarA = true;
	AcceptsVarB = true;
	AcceptsVarC = true;

	QPM = QuickParameterMode::kABPlusFine;

	Defaults.Set(1, 1000, 4, 0.89, -0.19, 6, 0, 0);

	MultiThread = true;

	Name = L"Julia Set (n-tic)";

	RenderModes.push_back(L"Escape time");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance from origin");
	RenderModes.push_back(L"Two-tone");
	RenderModes.push_back(L"Three-tone");
	RenderModes.push_back(L"Four-tone");
	RenderModes.push_back(L"Five-tone");

	NameA = L"real";
	NameB = L"imaginary";
	NameC = L"n";

	ResetAll();
}


JuliaNtic::~JuliaNtic()
{
}


bool JuliaNtic::MultiThreadRender(bool preview, bool super_sample, bool morph)
{
	// nothing to render, point isn't valid
	if (PointGoesToInfinity(Var.a, Var.b))
	{
		return false;
	}

	StartTime = std::chrono::system_clock::now();

	if (preview) SwapDimensions();

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


void JuliaNtic::RenderSS(int hstart, int hend)
{
	long double halfn = Var.c / 2;

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			for (int ss = 0; ss < supersamples; ss++)
			{
				long double p = xmin + ((long double)x + (0.5 - (rand() / (RAND_MAX + 1.0)))) * (xmax - xmin) / (long double)Width;    // real part
				long double q = ymin + ((long double)y + (0.5 - (rand() / (RAND_MAX + 1.0)))) * (ymax - ymin) / (long double)Height;   // imaginary part

				int it = 0;

				while (p * p + q * q <= bailout_radius && it < max_iterations)
				{
					long double atan2pq = Var.c * std::atan2(q, p);
					long double pow25 = std::pow(p * p + q * q, halfn);

					p = pow25 * std::cos(atan2pq) + Var.a;
					q = pow25 * std::sin(atan2pq) + Var.b;

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
					int nx = Fast::Floor(x - (Width / 2));
					int ny = Fast::Floor(y - (Height / 2));

					int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

					FractalData[ydotwidth + x] += pp->Colours[index];
					break;
				}
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void JuliaNtic::RenderSSMorph(int hstart, int hend)
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

				while (p * p + q * q <= bailout_radius && it < max_iterations)
				{
					long double atan2pq = Var.c * std::atan2(q, p);
					long double pow25 = std::pow(p * p + q * q, halfn);

					p = pow25 * std::cos(atan2pq) + vara;
					q = pow25 * std::sin(atan2pq) + varb;

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
					int nx = Fast::Floor(x - (Width / 2));
					int ny = Fast::Floor(y - (Height / 2));

					int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

					FractalData[ydotwidth + x] += pp->Colours[index];
					break;
				}
			}

			FractalData[ydotwidth + x] >>= supersamplenormalistioncoefficient;
		}
	}
}


void JuliaNtic::Render(int hstart, int hend)
{
	long double halfn = Var.c / 2;

	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			long double p = xmin + (long double)x * (xmax - xmin) / (long double)Width;    // real part
			long double q = ymin + (long double)y * (ymax - ymin) / (long double)Height;   // imaginary part

			int it = 0;

			while (p * p + q * q <= bailout_radius && it < max_iterations)
			{
				long double atan2pq = Var.c * std::atan2(q, p);
				long double pown = std::pow(p * p + q * q, halfn);

				p = pown * std::cos(atan2pq) + Var.a;
				q = pown * std::sin(atan2pq) + Var.b;

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
				int nx = Fast::Floor(x - (Width / 2));
				int ny = Fast::Floor(y - (Height / 2));

				int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

				FractalData[ydotwidth + x] = pp->Colours[index];
				break;
			}
		}
	}
}


void JuliaNtic::RenderMorph(int hstart, int hend)
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

			while (p * p + q * q <= bailout_radius && it < max_iterations)
			{
				long double atan2pq = Var.c * std::atan2(q, p);
				long double pown = std::pow(p * p + q * q, halfn);

				p = pown * std::cos(atan2pq) + vara;
				q = pown * std::sin(atan2pq) + varb;

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
				int nx = Fast::Floor(x - (Width / 2));
				int ny = Fast::Floor(y - (Height / 2));

				int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

				FractalData[ydotwidth + x] = pp->Colours[index];
				break;
			}
		}
	}
}


void JuliaNtic::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);
}


std::wstring JuliaNtic::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; real: " + std::to_wstring(Var.a) + L"; imaginary " + std::to_wstring(Var.b) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring JuliaNtic::Description()
{
	return L"Julia (z^n)" +  Formatting::LDToStr((int)Var.c) + L"): " + Formatting::LDToStr(Var.a) + L" + " + Formatting::LDToStr(Var.b) + L"i; " + Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


std::wstring JuliaNtic::HistoryEntry()
{
	return L"Julia (z^n)" +  Formatting::LDToStr((int)Var.c) + L"): " + Formatting::LDToStr(Var.a) + L" + " + Formatting::LDToStr(Var.b) + L"i; " + Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


void JuliaNtic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Julia Set (z^n)\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    r bailout  : " + std::to_wstring(bailout_radius) + L"\n\n");
	ofile << Formatting::to_utf8(L"    real       : " + std::to_wstring(Var.a) + L"\n");
	ofile << Formatting::to_utf8(L"    imaginary  : " + std::to_wstring(Var.b) + L"\n");
	ofile << Formatting::to_utf8(L"    n          : " + std::to_wstring(Var.c) + L"\n\n");

	ofile << Formatting::to_utf8(L"    x min      : " + Formatting::LDToStr(xmin) + L"\n");
	ofile << Formatting::to_utf8(L"    x max      : " + Formatting::LDToStr(xmax) + L"\n");
	ofile << Formatting::to_utf8(L"    y min      : " + Formatting::LDToStr(ymin) + L"\n");
	ofile << Formatting::to_utf8(L"    y max      : " + Formatting::LDToStr(ymax) + L"\n");
}
