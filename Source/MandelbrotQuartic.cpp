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
// z -> z^4 + c
// z^4 = a^4 - 6a^2b^2 + b^4 + i(4a^3b - 4ab^3)


#include <string>
#include <thread>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "MandelbrotQuartic.h"


MandelbrotQuartic::MandelbrotQuartic() : Fractal()
{
	Name = L"Mandelbrot z^4";

	NumIterationsPerPixel = new int[2001];
	for (int z = 0; z < 2001; z++) NumIterationsPerPixel[z] = 0;

   	AcceptsABC = true;
	AcceptsVarA = true;
	AcceptsVarB = true;

	MultiThread = true;

	Defaults.Set(1, 1000, 4, 0, 0, 0, 0);

	AcceptsABCSpectificRenderModeBegin = 4;
	AcceptsABCSpectificRenderModeEnd = 5;

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

	ResetAll();
}


MandelbrotQuartic::~MandelbrotQuartic()
{
	delete NumIterationsPerPixel;
}



bool MandelbrotQuartic::MultiThreadRender(bool preview, bool super_sample)
{
    max_d = 0;

	StartTime = std::chrono::system_clock::now();

	if (preview) SwapDimensions();

	if (RenderMode == __RMMandelbrotEscapeTime)
	{
		for (int z = 0; z < max_iterations; z++) NumIterationsPerPixel[z] = 0;
	}

	if (super_sample)
	{
		int h_delta = std::round((double)Height / 10);

		std::thread t1(RenderSS, 0, h_delta);
		std::thread t2(RenderSS, h_delta, 2 * h_delta);
		std::thread t3(RenderSS, 2 * h_delta, 3 * h_delta);
		std::thread t4(RenderSS, 3 * h_delta, 4 * h_delta);
		std::thread t5(RenderSS, 4 * h_delta, 5 * h_delta);
		std::thread t6(RenderSS, 5 * h_delta, 6 * h_delta);
		std::thread t7(RenderSS, 6 * h_delta, 7 * h_delta);
		std::thread t8(RenderSS, 7 * h_delta, 8 * h_delta);
		std::thread t9(RenderSS, 8 * h_delta, 9 * h_delta);
		std::thread t10(RenderSS, 9 * h_delta, Height);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();
		t9.join();
		t10.join();
	}
	else
	{
		int h_delta = std::round((double)Height / 5);

		std::thread t1(Render, 0, h_delta);
		std::thread t2(Render, h_delta, 2 * h_delta);
		std::thread t3(Render, 2 * h_delta, 3 * h_delta);
		std::thread t4(Render, 3 * h_delta, 4 * h_delta);
		std::thread t5(Render, 4 * h_delta, Height);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
	}

	if (preview)
	{
		FinaliseRenderMandelbrot(PreviewCanvas, max_d);

		SwapDimensions();
	}
	else
	{
		FinaliseRenderMandelbrot(RenderCanvas, max_d);
	}

	CalculateRenderTime();

    return true;
}


void MandelbrotQuartic::RenderSS(int hstart, int hend)
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

				Data[y * Width + x] = 10000000000000;
				long double x1 = 0;
				long double y1 = 0;
				long double x1squared = 0;
				long double y1squared = 0;
				long double m = 0;

				while (x1squared + y1squared <= bailout_radius && it < max_iterations)
				{
					m = x1squared * x1squared - (6 * x1squared * y1squared) + (y1squared * y1squared) + p;
					y1 = 4 * x1squared * x1 * y1 - (4 * x1 * y1 * y1squared) + q;

					x1 = m;

					x1squared = x1 * x1;
					y1squared = y1 * y1;

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
						long double log_zn = std::log(x1squared + y1squared) / 2;
						long double nu = std::log(log_zn / std::log(2)) / std::log(2);

						long double itnew = it + 1 - nu;

						it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
						long double it_d = (long double)it + 1 - nu;

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

						if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];
					}
					FractalData[ydotwidth + x].a += it;
					break;
				}
				case __RMMandelbrotDistanceII:
				{
					if (it < max_iterations)
					{
						Data[ydotwidth + x] = std::sqrt(std::pow(x1squared + y1squared, 2));

						if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];
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


void MandelbrotQuartic::Render(int hstart, int hend)
{
	for (int y = hstart; y < hend; y++)
	{
		int ydotwidth = y * Width;

		long double q = ymin + (long double)y * (ymax - ymin) / (long double)Height;   // imaginary part

		for (int x = 0; x < Width; x++)
		{
			long double p = xmin + (long double)x * (xmax - xmin) / (long double)Width;    // real part

			int it = 0;

			Data[y * Width + x] = 10000000000000;
			long double x1 = 0;
			long double y1 = 0;
			long double x1squared = 0;
			long double y1squared = 0;
			long double m = 0;

			while (x1squared + y1squared <= bailout_radius && it < max_iterations)
			{
				m = x1squared * x1squared - (6 * x1squared * y1squared) + (y1squared * y1squared) + p;
				y1 = 4 * x1squared * x1 * y1 - (4 * x1 * y1 * y1squared) + q;

				x1 = m;

				x1squared = x1 * x1;
				y1squared = y1 * y1;

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
					long double log_zn = std::log(x1squared + y1squared) / 2;
					long double nu = std::log(log_zn / std::log(2)) / std::log(2);

					long double itnew = it + 1 - nu;

					it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
					long double it_d = (long double)it + 1 - nu;

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
					Data[ydotwidth + x] = std::sqrt((x1 + y1) * (x1 + y1));

					if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];
				}
				FractalData[ydotwidth + x].a = it;
				break;
			}
			case __RMMandelbrotDistanceII:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(std::pow(x1squared + y1squared, 2));

					if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];
				}
				FractalData[ydotwidth + x].a = it;
				break;
			}
			}
		}
	}
}


void MandelbrotQuartic::ResetView()
{
	SetView(-2.00, 2.00, -1.6, 1.6);

	Var.a = xmin + ((xmax - xmin) / 2);     // set orbit trap position to centre of view
	Var.b = ymin + ((ymax - ymin) / 2);     //
}


std::wstring MandelbrotQuartic::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; orbit x: " + std::to_wstring(Var.a) + L"; orbit y " + std::to_wstring(Var.b) +
		   L"; bailout radius: " + std::to_wstring(bailout_radius) + L"; max iterations: " + std::to_wstring(max_iterations) +
		   L"; coeff n: " + std::to_wstring(n_coeff);
}


std::wstring MandelbrotQuartic::Description()
{
	return L"Mandelbrot (z^4): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


std::wstring MandelbrotQuartic::HistoryEntry()
{
	return L"Mandelbrot (z^4): " +  Formatting::LDToStr(xmin) + L", " + Formatting::LDToStr(xmax) + L" / " + Formatting::LDToStr(ymin) + L", " + Formatting::LDToStr(ymax);
}


void MandelbrotQuartic::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"MandelbrotQuartic fractal\n");
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
