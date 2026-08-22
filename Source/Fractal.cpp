//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2026
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <Vcl.Dialogs.hpp>

#include <string>
#include <thread>

#include "Constants.h"
#include "Fast.h"
#include "Fractal.h"


Fractal::Fractal()
{
	FractalData = new Colour[1280 * 1024];
	Data = new long double[1280 * 1024];

	RenderCanvas = new TBitmap();
	RenderCanvas->PixelFormat = pf24bit;
	RenderCanvas->Width = 1280;
	RenderCanvas->Height = 1024;

	PreviewCanvas = new TBitmap();
	PreviewCanvas->PixelFormat = pf24bit;
	PreviewCanvas->Width = 200;
	PreviewCanvas->Height = 200;

	CopyCanvas = new TBitmap();
	CopyCanvas->PixelFormat = pf24bit;
	CopyCanvas->Width = 1280;
	CopyCanvas->Height = 1024;

    CreateRenderCanvases();
}


Fractal::~Fractal()
{
	delete [] FractalData;
	delete [] Data;
	delete RenderCanvas;
    delete PreviewCanvas;
	delete CopyCanvas;
}


void Fractal::SetFromProjectHistory(ProjectHistory ph)
{
	xmin = ph.xmin;
	xmax = ph.xmax;
	ymin = ph.ymin;
	ymax = ph.ymax;

	Var.a = ph.VarA;
	Var.b = ph.VarB;
	Var.c = ph.VarC;
	Var.d = ph.VarD;
    Var.e = ph.VarE;

	n_coeff = ph.Coeff;
	max_iterations = ph.MaxIterations;
    bailout_radius = ph.Bailout;
}


ProjectHistory Fractal::GetAsProject(int id)
{
	return ProjectHistory(id, HistoryEntry(),
						  xmin, xmax, ymin, ymax,
						  Var.a, Var.b, Var.c, Var.d, Var.e,
						  n_coeff, max_iterations, bailout_radius);
}


void Fractal::ClearFractalDataA(int value)
{
	for (int y = 0; y < Height * Width; y++)
	{
		FractalData[y].a = value;
	}
}


void Fractal::CalculateRenderTime()
{
	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = EndTime - StartTime;

	RenderTime = std::to_wstring(elapsed_seconds.count());
}


void Fractal::SwapDimensions()
{
	std::swap(Width, PreviewWidth);
    std::swap(Height, PreviewHeight);
}


bool Fractal::MultiThreadRender(bool preview, bool super_sample, bool morph)
{
	// handled by subclass
    return false;
}


void Fractal::MT()
{
	int h_delta = std::round((double)Height / 10);

	std::thread t1(Render, 0, h_delta);
	std::thread t2(Render, h_delta, 2 * h_delta);
	std::thread t3(Render, 2 * h_delta, 3 * h_delta);
	std::thread t4(Render, 3 * h_delta, 4 * h_delta);
	std::thread t5(Render, 4 * h_delta, 5 * h_delta);
	std::thread t6(Render, 5 * h_delta, 6 * h_delta);
	std::thread t7(Render, 6 * h_delta, 7 * h_delta);
	std::thread t8(Render, 7 * h_delta, 8 * h_delta);
	std::thread t9(Render, 8 * h_delta, 9 * h_delta);
	std::thread t10(Render, 9 * h_delta, Height);

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


void Fractal::MTSS()
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


void Fractal::MTSSMorph()
{
	int h_delta = std::round((double)Height / 10);

	std::thread t1(RenderSSMorph, 0, h_delta);
	std::thread t2(RenderSSMorph, h_delta, 2 * h_delta);
	std::thread t3(RenderSSMorph, 2 * h_delta, 3 * h_delta);
	std::thread t4(RenderSSMorph, 3 * h_delta, 4 * h_delta);
	std::thread t5(RenderSSMorph, 4 * h_delta, 5 * h_delta);
	std::thread t6(RenderSSMorph, 5 * h_delta, 6 * h_delta);
	std::thread t7(RenderSSMorph, 6 * h_delta, 7 * h_delta);
	std::thread t8(RenderSSMorph, 7 * h_delta, 8 * h_delta);
	std::thread t9(RenderSSMorph, 8 * h_delta, 9 * h_delta);
	std::thread t10(RenderSSMorph, 9 * h_delta, Height);

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


void Fractal::MTMorph()
{
	int h_delta = std::round((double)Height / 10);

	std::thread t1(RenderMorph, 0, h_delta);
	std::thread t2(RenderMorph, h_delta, 2 * h_delta);
	std::thread t3(RenderMorph, 2 * h_delta, 3 * h_delta);
	std::thread t4(RenderMorph, 3 * h_delta, 4 * h_delta);
	std::thread t5(RenderMorph, 4 * h_delta, 5 * h_delta);
	std::thread t6(RenderMorph, 5 * h_delta, 6 * h_delta);
	std::thread t7(RenderMorph, 6 * h_delta, 7 * h_delta);
	std::thread t8(RenderMorph, 7 * h_delta, 8 * h_delta);
	std::thread t9(RenderMorph, 8 * h_delta, 9 * h_delta);
	std::thread t10(RenderMorph, 9 * h_delta, Height);

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


void Fractal::PreRender(bool preview)
{
	// handled by subclass
}


void Fractal::Render(int hs, int he)
{
	// handled by subclass
}


void Fractal::RenderMorph(int hs, int he)
{
	// handled by subclass
}


void Fractal::RenderSS(int hs, int he)
{
	// handled by subclass
}


void Fractal::RenderSSMorph(int hs, int he)
{
    // handled by subclass
}


void Fractal::ResetView()
{
	// handled by subclass
}


void Fractal::ResetAll()
{
	ResetConfig();
	ResetView();
}


void Fractal::ResetConfig()
{
	n_coeff = Defaults.n_coeff;
	max_iterations = Defaults.max_iterations;
	bailout_radius = Defaults.bailout_radius;

	Var.a = Defaults.a;
	Var.b = Defaults.b;
	Var.c = Defaults.c;
	Var.d = Defaults.d;
	Var.e = Defaults.e;
}


void Fractal::SetView(long double _xmin, long double _xmax, long double _ymin, long double _ymax)
{
	xmin = _xmin;
	xmax = _xmax;

	ymin = _ymin;
	ymax = _ymax;

	x_resolution = (xmax - xmin) / Width;
	y_resolution = (ymax - ymin) / Height;

	HasChanged = true;
}


// sets the view to the correct aspect ratio based on the incoming co-ordinates
void Fractal::FitToView(long double _xmin, long double _xmax, long double _ymin, long double _ymax)
{
	if (Width > Height || Width == Height)
	{
		long double c_yaxis = _ymin + ((_ymax - _ymin) / 2); // centre point of y-axis

		long double x_coeff = (_xmax - _xmin) / (double)Width;

		long double y_range = x_coeff / (1 / (double)Height);      // gets new y range

		_ymin = c_yaxis - (y_range / 2);
		_ymax = c_yaxis + (y_range / 2);
	}
	else
	{
		long double c_xaxis = _xmin + ((_xmax - _xmin) / 2); // centre point of x-axis

		long double y_coeff = (_ymax - _ymin) / (double)Height;

		long double x_range = y_coeff / (1 / (double)Width);      // gets new y range

		_xmin = c_xaxis - (x_range / 2);
		_xmax = c_xaxis + (x_range / 2);
	}

	SetView(_xmin, _xmax, _ymin, _ymax);
}


void Fractal::CentreOnPoint(long double _x, long double _y)
{
	long double delta_x = xmax - xmin;
	long double delta_y = ymax - ymin;

	long double _xmin = _x - (delta_x / 2);
	long double _xmax = _x + (delta_x / 2);

	long double _ymin = _y - (delta_y / 2);
	long double _ymax = _y + (delta_y / 2);

	SetView(_xmin, _xmax, _ymin, _ymax);
}


void Fractal::ZoomAtPoint(long double _x, long double _y)
{
	long double x_range = ((xmax - xmin) / 2);
	long double y_range = ((ymax - ymin) / 2);

	long double new_xmin = _x - (x_range / 2);
	long double new_xmax = _x + (x_range / 2);

	long double new_ymin = _y - (y_range / 2);
	long double new_ymax = _y + (y_range / 2);

	SetView(new_xmin, new_xmax, new_ymin, new_ymax);
}


void Fractal::ZoomOut()
{
	long double x_range = ((xmax - xmin) / 2);
	long double y_range = ((ymax - ymin) / 2);

	long double new_xmin = xmin - x_range;
	long double new_xmax = xmax + x_range;

	long double new_ymin = ymin - y_range;
	long double new_ymax = ymax + y_range;

	SetView(new_xmin, new_xmax, new_ymin, new_ymax);
}


void Fractal::SetDimensions(bool force, int _width, int _height)
{
	if (force || (Width != _width || Height != _height))
	{
		Width = _width;
		Height = _height;

		delete[] FractalData;
		delete[] Data;

		delete RenderCanvas;
		delete CopyCanvas;

		FractalData = new Colour[Width * Height];
		Data = new long double[Width * Height];

		RenderCanvas = new TBitmap();
		RenderCanvas->PixelFormat = pf24bit;
		RenderCanvas->Width = Width;
		RenderCanvas->Height = Height;

		CreateRenderCanvases();

		CopyCanvas = new TBitmap();
		CopyCanvas->PixelFormat = pf24bit;
		CopyCanvas->Width = Width;
		CopyCanvas->Height = Height;

		if (Width >= Height)
		{
			long double c_yaxis = ymin + ((ymax - ymin) / 2); // centre point of y-axis

			long double x_coeff = (xmax - xmin) / (long double)Width;

			long double y_range = x_coeff / (1 / (long double)Height);      // gets new y range

			ymin = c_yaxis - (y_range / 2);
			ymax = c_yaxis + (y_range / 2);
		}
		else
		{
			long double c_xaxis = xmin + ((xmax - xmin) / 2); // centre point of x-axis

			long double y_coeff = (ymax - ymin) / (long double)Height;

			long double x_range = y_coeff / (1 / (long double)Width);      // gets new y range

			xmin = c_xaxis - (x_range / 2);
			xmax = c_xaxis + (x_range / 2);
		}

		x_resolution = (xmax - xmin) / Width;
		y_resolution = (ymax - ymin) / Height;

		HasChanged = true;

		SetPreviewDimensions();
	}
}


void Fractal::CreateRenderCanvases()
{
	if (rc1 != nullptr) delete rc1;
	if (rc2 != nullptr) delete rc2;
	if (rc3 != nullptr) delete rc3;
	if (rc4 != nullptr) delete rc4;
	if (rc5 != nullptr) delete rc5;

	int h_delta = std::round((double)Height / 5);

	rc1 = new TBitmap();
	rc1->PixelFormat = pf24bit;
	rc1->Width = Width;
	rc1->Height = h_delta;

	rc2 = new TBitmap();
	rc2->PixelFormat = pf24bit;
	rc2->Width = Width;
	rc2->Height = h_delta;

	rc3 = new TBitmap();
	rc3->PixelFormat = pf24bit;
	rc3->Width = Width;
	rc3->Height = h_delta;

	rc4 = new TBitmap();
	rc4->PixelFormat = pf24bit;
	rc4->Width = Width;
	rc4->Height = h_delta;

	rc5 = new TBitmap();
	rc5->PixelFormat = pf24bit;
	rc5->Width = Width;
	rc5->Height = Height - (4 * h_delta);
}


void Fractal::SetPreviewDimensions()
{
	delete PreviewCanvas;

	if (Width >= Height)
	{
		PreviewWidth = __PreviewWidth;

		PreviewHeight = (int)std::floor((double)Height * ((double)PreviewWidth / (double)Width));
	}
	else
	{
		PreviewHeight = __PreviewHeight;

		PreviewWidth = (int)std::floor((double)Width * ((double)PreviewHeight / (double)Height));
	}

	PreviewCanvas = new TBitmap();
	PreviewCanvas->PixelFormat = pf24bit;
	PreviewCanvas->Width = PreviewWidth;
	PreviewCanvas->Height = PreviewWidth;
}


void Fractal::SetParameters(long double n, int i, int b)
{
	if (n != n_coeff)
	{
		if (n > 0)
		{
			n_coeff = n;
		}
		else
		{
			n_coeff = 1;
		}

		HasChanged = true;
	}

	if (i != max_iterations)
	{
		if (i > 0)
		{
			max_iterations = i;
		}
		else
		{
			i = 1000;
		}

		HasChanged = true;
	}

	if (b != bailout_radius)
	{
		if (b >= 4)
		{
			bailout_radius = b;
		}
		else
		{
			bailout_radius = 4;
		}

        HasChanged = true;
	}
}


void Fractal::SetABC(long double a, long double b, long double c, long double d, long double e)
{
	Var.a = a;
	Var.b = b;
	Var.c = c;
	Var.d = d;
	Var.e = e;
}


void Fractal::SetMorph(int morph_type, bool morph_a, bool morph_b, long double a, long double b)
{
    MorphType = morph_type;

	MorphA = morph_a;
    MorphB = morph_b;

	Var.morph_a = a;
	Var.morph_b = b;
}


void Fractal::SetRenderMode(int new_mode)
{
	RenderMode = new_mode;

    HasChanged = true;
}


void Fractal::SetPaletteInfinity(Colour colour)
{
	pp2->PatternLive.SingleColour = colour;
}


// returns true if the point p,q on a mandelbrot set goes to infinity
bool Fractal::PointGoesToInfinity(long double p, long double q)
{
	int it = 0;

	long double x1 = 0;
	long double y1 = 0;
	long double x2 = 0;
	long double y2 = 0;
	long double w = 0;

	while (x2 + y2 <= 4 && it < 1000)
	{
		x1 = x2 - y2 + p;
		y1 = w - x2 - y2 + q;

		x2 = x1 * x1;
		y2 = y1 * y1;

		w = (x1 + y1) * (x1 + y1);

		it++;
	}

	if (it < 1000)
	{
		return false;
	}

    return true;
}


double Fractal::Sign(long double n)
{
	if (n > 0) return 1;
	if (n < 0) return -1;

	return 0;
}


void Fractal::ColourDistanceI(TBitmap* canvas, long double max_d)
{
	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			if (FractalData[ydotwidth + x].a != max_iterations)
			{
				int index = Fast::Floor(std::pow((Data[ydotwidth + x] / max_d), n_coeff) * pp->ColourCount);

				ptr[x].rgbtRed = pp->Colours[index].r;
				ptr[x].rgbtGreen = pp->Colours[index].g;
				ptr[x].rgbtBlue = pp->Colours[index].b;
			}
			else
			{
				switch (pp2->PatternLive.DrawMode)
				{
				case DrawModeOption::kSingleColour:
					ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
					ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
					ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
					break;
				case DrawModeOption::kGradient:
					if (pp2->PatternLive.GradientDirection)
					{
						int index = (int)std::floor(((double)x / Width) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					else
					{
						int index = (int)std::floor(((double)y / Height) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					break;
				case DrawModeOption::kGrid:
					break;
				case DrawModeOption::kGridGradient:
					break;
				}
			}
		}
	}
}


void Fractal::ColourDistanceII(TBitmap* canvas, long double max_d)
{
	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			if (FractalData[ydotwidth + x].a != max_iterations)
			{
				int index = Fast::Floor(std::pow((Data[ydotwidth + x] / max_d), n_coeff) * pp->ColourCount);

				ptr[x].rgbtRed = pp->Colours[index].r;
				ptr[x].rgbtGreen = pp->Colours[index].g;
				ptr[x].rgbtBlue = pp->Colours[index].b;
			}
			else
			{
				ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
				ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
				ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
			}
		}
	}
}


void Fractal::ColourNTone(TBitmap* canvas, int n)
{
	colours = new Colour[n];

	colours[0] = pp->Colours[0];
	colours[n - 1] = pp->Colours[pp->ColourCount - 1];

	if (n > 2)
	{
		int delta = Fast::Floor(pp->ColourCount / (n - 1));

		for (int t = 1; t < n - 1; t++)
		{
			colours[t] = pp->Colours[delta * t];
		}
	}

	int h_delta = std::round((double)Height / 5);

	std::thread t1(ColourNToneThread, rc1, 0, h_delta, n);
	std::thread t2(ColourNToneThread, rc2, h_delta, 2 * h_delta, n);
	std::thread t3(ColourNToneThread, rc3, 2 * h_delta, 3 * h_delta, n);
	std::thread t4(ColourNToneThread, rc4, 3 * h_delta, 4 * h_delta, n);
	std::thread t5(ColourNToneThread, rc5, 4 * h_delta, Height, n);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	canvas->Canvas->Draw(0, 0, rc1);
	canvas->Canvas->Draw(0, rc1->Height, rc2);
	canvas->Canvas->Draw(0, rc1->Height + rc2->Height, rc3);
	canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height, rc4);
	canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height + rc4->Height, rc5);

	delete[] colours;
}


void Fractal::ColourNToneThread(TBitmap* canvas, int ybegin, int yend, int n)
{
	TRGBTriple *ptr;

	for (int y = ybegin; y < yend; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y - ybegin]);

		for (int x = 0; x < Width; x++)
		{
			if (FractalData[ydotwidth + x].a != max_iterations)
			{
				Colour colour = colours[FractalData[ydotwidth + x].a % n];

				ptr[x].rgbtRed = colour.r;
				ptr[x].rgbtGreen = colour.g;
				ptr[x].rgbtBlue = colour.b;
			}
			else
			{
				switch (pp2->PatternLive.DrawMode)
				{
				case DrawModeOption::kSingleColour:
					ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
					ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
					ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
					break;
				case DrawModeOption::kGradient:
					if (pp2->PatternLive.GradientDirection)
					{
						int index = (int)std::floor(((double)x / Width) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					else
					{
						int index = (int)std::floor(((double)y / Height) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					break;
				case DrawModeOption::kGrid:
					break;
				case DrawModeOption::kGridGradient:
					break;
				}
			}
		}
	}
}


std::wstring Fractal::GetParameters()
{
    return L"";
}


void Fractal::CopyImage()
{
	CopyCanvas->Assign(RenderCanvas);
}


void Fractal::MergeImage()
{
	TRGBTriple *ptra;
	TRGBTriple *ptrb;

	for (int y = 0; y < RenderCanvas->Height; y++)
	{
		ptra = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);
		ptrb = reinterpret_cast<TRGBTriple *>(CopyCanvas->ScanLine[y]);

		for (int x = 0; x  < RenderCanvas->Width; x++)
		{
			if (ptra[x].rgbtRed == pp2->PatternLive.SingleColour.r &&
				ptra[x].rgbtGreen == pp2->PatternLive.SingleColour.g &&
				ptra[x].rgbtBlue == pp2->PatternLive.SingleColour.b)
			{
                ptra[x] = ptrb[x];
			}
		}
	}
}


bool Fractal::AttemptRecolour()
{
	if (Name.find(L"Mandelbrot") != std::wstring::npos)
	{
		FinaliseRenderMandelbrot(RenderCanvas);

		return true;
	}
	else if (Name.find(L"Martin") != std::wstring::npos)
	{
		FinaliseRenderMartin(RenderCanvas);

        return true;
	}
	else if (Name.find(L"Julia") != std::wstring::npos)
	{
		FinaliseRenderJulia(RenderCanvas);

		return true;
	}
	else if (Name.find(L"Dragon") != std::wstring::npos)
	{
		FinaliseRenderDragon(RenderCanvas);

		return true;
	}

    return false;
}


void Fractal::FinaliseRenderJulia(TBitmap *canvas)
{
	switch (RenderMode)
	{
	case __RMJuliaEscapeTime:
	{
		int max = 0;
		int min = max_iterations + 1;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			for (int x = 0; x < Width; x++)
			{
				if (FractalData[ydotwidth + x].a > max) max = FractalData[ydotwidth + x].a;
				if (FractalData[ydotwidth + x].a < min && FractalData[ydotwidth + x].a != 0) min = FractalData[ydotwidth + x].a;
			}
		}

		int h_delta = std::round((double)Height / 5);

		std::thread t1(JuliaThreadEscapeTime, rc1, 0, h_delta, min, max);
		std::thread t2(JuliaThreadEscapeTime, rc2, h_delta, 2 * h_delta, min, max);
		std::thread t3(JuliaThreadEscapeTime, rc3, 2 * h_delta, 3 * h_delta, min, max);
		std::thread t4(JuliaThreadEscapeTime, rc4, 3 * h_delta, 4 * h_delta, min, max);
		std::thread t5(JuliaThreadEscapeTime, rc5, 4 * h_delta, Height, min, max);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();

		canvas->Canvas->Draw(0, 0, rc1);
		canvas->Canvas->Draw(0, rc1->Height, rc2);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height, rc3);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height, rc4);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height + rc4->Height, rc5);

		break;
	}
	case __RMJuliaContinuous:
	case __RMJuliaDistanceOrigin:
		TRGBTriple *ptr;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y]);

			for (int x = 0; x < Width; x++)
			{
				ptr[x].rgbtRed = FractalData[ydotwidth + x].r;
				ptr[x].rgbtGreen = FractalData[ydotwidth + x].g;
				ptr[x].rgbtBlue = FractalData[ydotwidth + x].b;
			}
		}
		break;
	case __RMJuliaDistance:                                                                     // distance II
	{
		long double max_d = 0;

		for (int t = 0; t < Height * Width; t++)
		{
			if (Data[t] > max_d) max_d = Data[t];
		}

		ColourDistanceII(canvas, max_d);
		break;
	}
	case __RMJuliaTwoTone:                                                                     // two-tone
		ColourNTone(canvas, 2);
		break;
	case __RMJuliaThreeTone:                                                                     // three-tone
		ColourNTone(canvas, 3);
		break;
	case __RMJuliaFourTone:                                                                     // four-tone
		ColourNTone(canvas, 4);
		break;
	case __RMJuliaFiveTone:                                                                     // five-tone
		ColourNTone(canvas, 5);
		break;
	case __RMJuliaXOR:
		MandelbrotThreadXOR(canvas);
		break;
	}
}


void Fractal::JuliaThreadEscapeTime(TBitmap *canvas, int ybegin, int yend, int min, int max)
{
	TRGBTriple *ptr;

	for (int y = ybegin; y < yend; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y - ybegin]);

		for (int x = 0; x < Width; x++)
		{
			if (FractalData[ydotwidth + x].a == 0)
			{
				ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
				ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
				ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
			}
			else
			{
				if (max == min)
				{
					ptr[x].rgbtRed = pp->Colours[pp->ColourCount - 1].r;
					ptr[x].rgbtGreen = pp->Colours[pp->ColourCount - 1].g;
					ptr[x].rgbtBlue = pp->Colours[pp->ColourCount - 1].b;
				}
				else
				{
					int it = FractalData[ydotwidth + x].a - min;
					int index = std::round(std::pow((long double)it / ((long double)max - (long double)min), n_coeff) * pp->ColourCount);

					ptr[x].rgbtRed = pp->Colours[index].r;
					ptr[x].rgbtGreen = pp->Colours[index].g;
					ptr[x].rgbtBlue = pp->Colours[index].b;
				}
			}
		}
	}
}


void Fractal::FinaliseRenderMandelbrot(TBitmap *canvas)
{
	switch (RenderMode)
	{
	case __RMMandelbrotEscapeTime:
	{
		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			for (int x = 0; x < Width; x++)
			{
				NumIterationsPerPixel[FractalData[ydotwidth + x].a]++;
			}
		}

		long double total = 0;

		for (int i = 0; i < max_iterations; i++)
		{
			total += NumIterationsPerPixel[i];
		}

		int h_delta = std::round((double)Height / 5);

		std::thread t1(MandelbrotThreadEscapeTime, rc1, 0, h_delta, total);
		std::thread t2(MandelbrotThreadEscapeTime, rc2, h_delta, 2 * h_delta, total);
		std::thread t3(MandelbrotThreadEscapeTime, rc3, 2 * h_delta, 3 * h_delta, total);
		std::thread t4(MandelbrotThreadEscapeTime, rc4, 3 * h_delta, 4 * h_delta, total);
		std::thread t5(MandelbrotThreadEscapeTime, rc5, 4 * h_delta, Height, total);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();

		canvas->Canvas->Draw(0, 0, rc1);
		canvas->Canvas->Draw(0, rc1->Height, rc2);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height, rc3);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height, rc4);
   		canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height + rc4->Height, rc5);

		break;
	}
	case __RMMandelbrotContinuous:
	{
		int h_delta = std::round((double)Height / 5);

		std::thread t1(MandelbrotThreadContinuous, rc1, 0, h_delta);
		std::thread t2(MandelbrotThreadContinuous, rc2, h_delta, 2 * h_delta);
		std::thread t3(MandelbrotThreadContinuous, rc3, 2 * h_delta, 3 * h_delta);
		std::thread t4(MandelbrotThreadContinuous, rc4, 3 * h_delta, 4 * h_delta);
		std::thread t5(MandelbrotThreadContinuous, rc5, 4 * h_delta, Height);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();

		canvas->Canvas->Draw(0, 0, rc1);
		canvas->Canvas->Draw(0, rc1->Height, rc2);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height, rc3);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height, rc4);
		canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height + rc4->Height, rc5);
		break;
	}
	case __RMMandelbrotDistance:
	{
		long double max_d = 0;

		for (int t = 0; t < Height * Width; t++)
		{
			if (Data[t] > max_d) max_d = Data[t];
		}

		ColourDistanceI(canvas, max_d);
		break;
	}
	case __RMMandelbrotDistanceII:
	{
    	long double max_d = 0;

		for (int t = 0; t < Height * Width; t++)
		{
			if (Data[t] > max_d) max_d = Data[t];
		}

		ColourDistanceII(canvas, max_d);
		break;
	}
	case __RMMandelbrotOrbitTrap:
		OrbitTrap(canvas, false);
		break;
	case __RMMandelbrotOrbitTrapFilled:
		OrbitTrap(canvas, true);
		break;
	case __RMMandelbrotTwoTone:
		ColourNTone(canvas, 2);
		break;
	case __RMMandelbrotThreeTone:
		ColourNTone(canvas, 3);
		break;
	case __RMMandelbrotFourTone:
		ColourNTone(canvas, 4);
		break;
	case __RMMandelbrotFiveTone:
		ColourNTone(canvas, 5);
		break;
	case __RMMandelbrotXOR:
	case __RMMandelbrotXOR2:
	case __RMMandelbrotXOR3:
		MandelbrotThreadXOR(canvas);
		break;
	}
}


void Fractal::MandelbrotThreadEscapeTime(TBitmap *canvas, int ybegin, int yend, int total)
{
	TRGBTriple *ptr;

	for (int y = ybegin; y < yend; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y - ybegin]);

		for (int x = 0; x < Width; x++)
		{
			long double c = 0;

			for (int i = 0; i < FractalData[ydotwidth + x].a; i++)
			{
				c += (long double)NumIterationsPerPixel[i] / total;
			}

			if (FractalData[ydotwidth + x].a != max_iterations)
			{
				int index = Fast::Floor(exp(n_coeff * log(c)) * pp->ColourCount);

				if (index >= 0 && index <= pp->ColourCount)
				{
					ptr[x].rgbtRed = pp->Colours[index].r;
					ptr[x].rgbtGreen = pp->Colours[index].g;
					ptr[x].rgbtBlue = pp->Colours[index].b;
				}
			}
			else
			{
				switch (pp2->PatternLive.DrawMode)
				{
				case DrawModeOption::kSingleColour:
					ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
					ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
					ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
					break;
				case DrawModeOption::kGradient:
					if (pp2->PatternLive.GradientDirection)
					{
						int index = (int)std::floor(((double)x / Width) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					else
					{
						int index = (int)Fast::Floor(((double)y / Height) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					break;
				case DrawModeOption::kGrid:
					if (x % pp2->PatternLive.GridWidth == 0 ||
						y % pp2->PatternLive.GridWidth == 0)
					{
						ptr[x].rgbtRed = pp2->PatternLive.GridColourOn.r;
						ptr[x].rgbtGreen = pp2->PatternLive.GridColourOn.g;
						ptr[x].rgbtBlue = pp2->PatternLive.GridColourOn.b;
					}
					else
					{
						ptr[x].rgbtRed = pp2->PatternLive.GridColourOff.r;
						ptr[x].rgbtGreen = pp2->PatternLive.GridColourOff.g;
						ptr[x].rgbtBlue = pp2->PatternLive.GridColourOff.b;
					}
					break;
				case DrawModeOption::kGridGradient:
					break;
				}
			}
		}
	}
}


void Fractal::MandelbrotThreadContinuous(TBitmap *canvas, int ybegin, int yend)
{
	TRGBTriple *ptr;

	for (int y = ybegin; y < yend; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y - ybegin]);

		for (int x = 0; x < Width; x++)
		{
			if (FractalData[ydotwidth + x].a == -1)
			{
				switch (pp2->PatternLive.DrawMode)
				{
				case DrawModeOption::kSingleColour:
					ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
					ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
					ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
					break;
				case DrawModeOption::kGradient:
					if (pp2->PatternLive.GradientDirection)
					{
						int index = (int)Fast::Floor(((double)x / Width) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					else
					{
						int index = (int)Fast::Floor(((double)y / Height) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					break;
				case DrawModeOption::kGrid:
					break;
				case DrawModeOption::kGridGradient:
					break;
				}
			}
			else
			{
				ptr[x].rgbtRed = FractalData[ydotwidth + x].r;
				ptr[x].rgbtGreen = FractalData[ydotwidth + x].g;
				ptr[x].rgbtBlue = FractalData[ydotwidth + x].b;
			}
		}
	}
}


void Fractal::MandelbrotThreadXOR(TBitmap *canvas)
{
	int max = 0;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			if (FractalData[ydotwidth + x].a > max)
			{
				max = FractalData[ydotwidth + x].a;
			}
		}
	}

	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			if (FractalData[ydotwidth + x].a != -1)
			{
				double dd = ((double)FractalData[ydotwidth + x].a / (double)max) * (double)pp->ColourCount;

				int index = (int)dd;

				if (index >= 0 && index <= pp->ColourCount)
				{
					ptr[x].rgbtRed = pp->Colours[index].r;
					ptr[x].rgbtGreen = pp->Colours[index].g;
					ptr[x].rgbtBlue = pp->Colours[index].b;
				}
			}
			else
			{
				switch (pp2->PatternLive.DrawMode)
				{
				case DrawModeOption::kSingleColour:
					ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
					ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
					ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
					break;
				case DrawModeOption::kGradient:
					if (pp2->PatternLive.GradientDirection)
					{
						int index = (int)std::floor(((double)x / Width) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					else
					{
						int index = (int)Fast::Floor(((double)y / Height) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					break;
				case DrawModeOption::kGrid:
					if (x % pp2->PatternLive.GridWidth == 0 ||
						y % pp2->PatternLive.GridWidth == 0)
					{
						ptr[x].rgbtRed = pp2->PatternLive.GridColourOn.r;
						ptr[x].rgbtGreen = pp2->PatternLive.GridColourOn.g;
						ptr[x].rgbtBlue = pp2->PatternLive.GridColourOn.b;
					}
					else
					{
						ptr[x].rgbtRed = pp2->PatternLive.GridColourOff.r;
						ptr[x].rgbtGreen = pp2->PatternLive.GridColourOff.g;
						ptr[x].rgbtBlue = pp2->PatternLive.GridColourOff.b;
					}
					break;
				case DrawModeOption::kGridGradient:
					break;
				}
			}
		}
	}
}


void Fractal::FinaliseRenderDragon(TBitmap* canvas)
{
	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			ptr[x].rgbtRed = pp->Colours[FractalData[ydotwidth + x].a].r;
			ptr[x].rgbtGreen = pp->Colours[FractalData[ydotwidth + x].a].g;
			ptr[x].rgbtBlue = pp->Colours[FractalData[ydotwidth + x].a].b;
		}
	}
}


void Fractal::FinaliseRenderMartin(TBitmap* canvas)
{
	switch (RenderMode)
	{
	case __RMMartinAverage:
		{
			int max = 0;
			int min = max_iterations + 1;

			for (int y = 0; y < Height; y++)
			{
				int ydotwidth = y * Width;

				for (int x = 0; x < Width; x++)
				{
					if (FractalData[ydotwidth + x].a > max) max = FractalData[ydotwidth + x].a;
					if (FractalData[ydotwidth + x].a < min && FractalData[ydotwidth + x].a != 0) min = FractalData[ydotwidth + x].a;
				}
			}

			TRGBTriple *ptr;

			for (int y = 0; y < Height; y++)
			{
				int ydotwidth = y * Width;

				ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y]);

				for (int x = 0; x < Width; x++)
				{
					if (FractalData[ydotwidth + x].a == -1)
					{
						switch (pp2->PatternLive.DrawMode)
						{
						case DrawModeOption::kSingleColour:
							ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
							ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
							ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
							break;
						case DrawModeOption::kGradient:
							if (pp2->PatternLive.GradientDirection)
							{
								int index = (int)Fast::Floor(((double)x / Width) * pp2->ColourCount);

								ptr[x].rgbtRed = pp2->Colours[index].r;
								ptr[x].rgbtGreen = pp2->Colours[index].g;
								ptr[x].rgbtBlue = pp2->Colours[index].b;
							}
							else
							{
								int index = (int)Fast::Floor(((double)y / Height) * pp2->ColourCount);

								ptr[x].rgbtRed = pp2->Colours[index].r;
								ptr[x].rgbtGreen = pp2->Colours[index].g;
								ptr[x].rgbtBlue = pp2->Colours[index].b;
							}
							break;
						case DrawModeOption::kGrid:
							break;
						case DrawModeOption::kGridGradient:
							break;
						}
					}
					else
					{
						int it = FractalData[ydotwidth + x].a - min;

						int index = std::round(std::pow((long double)it / ((long double)max - (long double)min), n_coeff) * pp->ColourCount);

						ptr[x].rgbtRed = pp->Colours[index].r;
						ptr[x].rgbtGreen = pp->Colours[index].g;
						ptr[x].rgbtBlue = pp->Colours[index].b;
					}
				}
			}
			break;
		}
	case __RMMartinTime:
	case __RMMartinDistance:
		TRGBTriple *ptr;

		for (int y = 0; y < Height; y++)
		{
			int ydotwidth = y * Width;

			ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y]);

			for (int x = 0; x < Width; x++)
			{
				if (FractalData[ydotwidth + x].a == -1)
				{
					switch (pp2->PatternLive.DrawMode)
					{
					case DrawModeOption::kSingleColour:
						ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
						ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
						ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
						break;
					case DrawModeOption::kGradient:
						if (pp2->PatternLive.GradientDirection)
						{
							int index = (int)Fast::Floor(((double)x / Width) * pp2->ColourCount);

							ptr[x].rgbtRed = pp2->Colours[index].r;
							ptr[x].rgbtGreen = pp2->Colours[index].g;
							ptr[x].rgbtBlue = pp2->Colours[index].b;
						}
						else
						{
							int index = (int)Fast::Floor(((double)y / Height) * pp2->ColourCount);

							ptr[x].rgbtRed = pp2->Colours[index].r;
							ptr[x].rgbtGreen = pp2->Colours[index].g;
							ptr[x].rgbtBlue = pp2->Colours[index].b;
						}
						break;
					case DrawModeOption::kGrid:
						break;
					case DrawModeOption::kGridGradient:
						break;
					}
				}
				else
				{
					ptr[x].rgbtRed = pp->Colours[FractalData[ydotwidth + x].a].r;
					ptr[x].rgbtGreen = pp->Colours[FractalData[ydotwidth + x].a].g;
					ptr[x].rgbtBlue = pp->Colours[FractalData[ydotwidth + x].a].b;
				}
			}
		}
		break;
	}
}


void Fractal::OrbitTrap(TBitmap* canvas, bool fill)
{
	double maxx = 0;

	for (int y = 0; y < Height; y++)
	{
		int ydotwidth = y * Width;

		for (int x = 0; x < Width; x++)
		{
			if (Data[ydotwidth + x] > maxx)
			{
				maxx = Data[ydotwidth + x];
			}
		}
	}

	int h_delta = std::round((double)Height / 5);

	if (fill)
	{
		std::thread t1(OrbitTrapThreadFilled, rc1, 0, h_delta, maxx);
		std::thread t2(OrbitTrapThreadFilled, rc2, h_delta, 2 * h_delta, maxx);
		std::thread t3(OrbitTrapThreadFilled, rc3, 2 * h_delta, 3 * h_delta, maxx);
		std::thread t4(OrbitTrapThreadFilled, rc4, 3 * h_delta, 4 * h_delta, maxx);
		std::thread t5(OrbitTrapThreadFilled, rc5, 4 * h_delta, Height, maxx);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
	}
	else
	{
		std::thread t1(OrbitTrapThreadNonFilled, rc1, 0, h_delta, maxx);
		std::thread t2(OrbitTrapThreadNonFilled, rc2, h_delta, 2 * h_delta, maxx);
		std::thread t3(OrbitTrapThreadNonFilled, rc3, 2 * h_delta, 3 * h_delta, maxx);
		std::thread t4(OrbitTrapThreadNonFilled, rc4, 3 * h_delta, 4 * h_delta, maxx);
		std::thread t5(OrbitTrapThreadNonFilled, rc5, 4 * h_delta, Height, maxx);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
	}

	canvas->Canvas->Draw(0, 0, rc1);
	canvas->Canvas->Draw(0, rc1->Height, rc2);
	canvas->Canvas->Draw(0, rc1->Height + rc2->Height, rc3);
	canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height, rc4);
	canvas->Canvas->Draw(0, rc1->Height + rc2->Height + rc3->Height + rc4->Height, rc5);
}


void Fractal::OrbitTrapThreadNonFilled(TBitmap *canvas, int ybegin, int yend, double maxx)
{
	TRGBTriple *ptr;

	for (int y = ybegin; y < yend; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y - ybegin]);

		for (int x = 0; x < Width; x++)
		{
			int index = Fast::Floor(std::pow((Data[ydotwidth + x] / maxx), n_coeff) * pp->ColourCount);

			ptr[x].rgbtRed = pp->Colours[index].r;
			ptr[x].rgbtGreen = pp->Colours[index].g;
			ptr[x].rgbtBlue = pp->Colours[index].b;
		}
	}
}


void Fractal::OrbitTrapThreadFilled(TBitmap *canvas, int ybegin, int yend, double maxx)
{
	TRGBTriple *ptr;

	for (int y = ybegin; y < yend; y++)
	{
		int ydotwidth = y * Width;

		ptr = reinterpret_cast<TRGBTriple *>(canvas->ScanLine[y - ybegin]);

		for (int x = 0; x < Width; x++)
		{
			int index = Fast::Floor(std::pow((Data[ydotwidth + x] / maxx), n_coeff) * pp->ColourCount);

			if (FractalData[ydotwidth + x].a != max_iterations)
			{
				ptr[x].rgbtRed = pp->Colours[index].r;
				ptr[x].rgbtGreen = pp->Colours[index].g;
				ptr[x].rgbtBlue = pp->Colours[index].b;
			}
			else
			{
				switch (pp2->PatternLive.DrawMode)
				{
				case DrawModeOption::kSingleColour:
					ptr[x].rgbtRed = pp2->PatternLive.SingleColour.r;
					ptr[x].rgbtGreen = pp2->PatternLive.SingleColour.g;
					ptr[x].rgbtBlue = pp2->PatternLive.SingleColour.b;
					break;
				case DrawModeOption::kGradient:
					if (pp2->PatternLive.GradientDirection)
					{
						int index = (int)Fast::Floor(((double)x / Width) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					else
					{
						int index = (int)Fast::Floor(((double)y / Height) * pp2->ColourCount);

						ptr[x].rgbtRed = pp2->Colours[index].r;
						ptr[x].rgbtGreen = pp2->Colours[index].g;
						ptr[x].rgbtBlue = pp2->Colours[index].b;
					}
					break;
				case DrawModeOption::kGrid:
					break;
				case DrawModeOption::kGridGradient:
					break;
				}
			}
		}
	}
}


std::wstring Fractal::Description()
{
	// handled by subclass
    return L"";
}


std::wstring Fractal::HistoryEntry()
{
	// handled by subclass
	return L"";
}


void Fractal::ToFile(std::ofstream& ofile)
{
	// handled by subclass
}
