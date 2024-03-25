//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//
#include <Vcl.Dialogs.hpp>

#include <string>

#include "Constants.h"
#include "Fractal.h"



Fractal::Fractal()
{
	Iteration = new int[1280 * 1024];
	Data = new double[1280 * 1024];

	RenderCanvas = new TBitmap();
    RenderCanvas->PixelFormat = pf24bit;
	RenderCanvas->Width = 1280;
	RenderCanvas->Height = 1024;

	for (int t = 0; t < __PaletteCount; t++)
	{
		int colour = std::floor(((double)t / __PaletteCount) * 255);

		Palette[t] = colour + (colour << 8) + (colour << 16);
	}

	Palette[__PaletteInfinity] = 0x000000;
}


Fractal::~Fractal()
{
	delete Iteration;
	delete Data;
    delete RenderCanvas;
}


void Fractal::CalculateRenderTime()
{
	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = EndTime - StartTime;

	RenderTime = std::to_wstring(elapsed_seconds.count());
}


void Fractal::MultiThreadRender()
{

}


void Fractal::Render(int hs, int he)
{
	// handled by subclass
}


void Fractal::Preview()
{
	// handled by subclass
}


void Fractal::ResetView()
{
	// handled by subclass
}


void Fractal::SetView(double _xmin, double _xmax, double _ymin, double _ymax)
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
void Fractal::FitToView(double _xmin, double _xmax, double _ymin, double _ymax)
{
	if (Width > Height || Width == Height)
	{
		double c_yaxis = _ymin + ((_ymax - _ymin) / 2); // centre point of y-axis

		double x_coeff = (_xmax - _xmin) / (double)Width;

		double y_range = x_coeff / (1 / (double)Height);      // gets new y range

		_ymin = c_yaxis - (y_range / 2);
		_ymax = c_yaxis + (y_range / 2);
	}
	else
	{
		double c_xaxis = _xmin + ((_xmax - _xmin) / 2); // centre point of x-axis

		double y_coeff = (_ymax - _ymin) / (double)Height;

		double x_range = y_coeff / (1 / (double)Width);      // gets new y range

		_xmin = c_xaxis - (x_range / 2);
		_xmax = c_xaxis + (x_range / 2);
	}

	SetView(_xmin, _xmax, _ymin, _ymax);
}


void Fractal::ZoomAtPoint(double _x, double _y)
{
	double x_range = ((xmax - xmin) / 2);
	double y_range = ((ymax - ymin) / 2);

	double new_xmin = _x - (x_range / 2);
	double new_xmax = _x + (x_range / 2);

	double new_ymin = _y - (y_range / 2);
	double new_ymax = _y + (y_range / 2);

	SetView(new_xmin, new_xmax, new_ymin, new_ymax);
}


void Fractal::SetDimensions(int _width, int _height)
{
	if (Width != _width || Height != _height)
	{
		Width = _width;
		Height = _height;

		delete[] Iteration;
		delete[] Data;

		delete RenderCanvas;

		Iteration = new int[Width * Height];
		Data = new double[Width * Height];

		RenderCanvas = new TBitmap();
		RenderCanvas->PixelFormat = pf24bit;
		RenderCanvas->Width = Width;
		RenderCanvas->Height = Height;

		if (Width >= Height)
		{
			double c_yaxis = ymin + ((ymax - ymin) / 2); // centre point of y-axis

			double x_coeff = (xmax - xmin) / (double)Width;

			double y_range = x_coeff / (1 / (double)Height);      // gets new y range

			ymin = c_yaxis - (y_range / 2);
			ymax = c_yaxis + (y_range / 2);
		}
		else
		{
			double c_xaxis = xmin + ((xmax - xmin) / 2); // centre point of x-axis

			double y_coeff = (ymax - ymin) / (double)Height;

			double x_range = y_coeff / (1 / (double)Width);      // gets new y range

			xmin = c_xaxis - (x_range / 2);
			xmax = c_xaxis + (x_range / 2);
		}

		x_resolution = (xmax - xmin) / Width;
		y_resolution = (ymax - ymin) / Height;

       	HasChanged = true;
	}
}


void Fractal::SetParameters(double n, int i, int b)
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

	if (n != max_iterations)
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


void Fractal::SetABC(double a, double b, double c, double d)
{
	Var.a = a;
	Var.b = b;
	Var.c = c;
	Var.d = d;
}


bool Fractal::ShowABC(int rm)
{
	if (AcceptsABC)
	{
		if (AcceptsABCSpectificRenderModeBegin != -1)
		{
			if (AcceptsABCSpectificRenderModeBegin > rm ||
				AcceptsABCSpectificRenderModeEnd < rm)
			{
				return false;
			}
		}

		return true;
	}

	return false;
}


void Fractal::SetRenderMode(int new_mode)
{
	RenderMode = new_mode;

    HasChanged = true;
}


double Fractal::Sign(double n)
{
	if (n > 0) return 1;
	if (n < 0) return -1;

	return 0;
}


void Fractal::ToFile(std::ofstream& ofile)
{

}
