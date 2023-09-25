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

#include "Fractal.h"



Fractal::Fractal()
{
	Canvas = new int[640 * 640];
	Iteration = new int[640 * 640];

	for (int t = 0; t < 500; t++)
	{
		int colour = std::floor(((double)t / 500) * 255);

		Palette[t] = colour + (colour << 8) + (colour << 16);
    }
}


Fractal::~Fractal()
{
	delete Canvas;
	delete Iteration;
}


void Fractal::CalculateRenderTime()
{
	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = EndTime - StartTime;

	RenderTime = std::to_wstring(elapsed_seconds.count());
}


int Fractal::LinearInterpolate(int colour1, int colour2, double t)
{
	int red1 = colour1 & 0x0000ff;
	int green1 = colour1 >> 8 & 0x0000ff;
	int blue1 = colour1 >> 16 & 0x0000ff;

	int red2 = colour2 & 0x0000ff;
	int green2 = colour2 >> 8 & 0x0000ff;
	int blue2 = colour2 >> 16 & 0x0000ff;

	int red = std::floor((double)red1 + t * ((double)red2 - (double)red1));
	int green = std::floor((double)green1 + t * ((double)green2 - (double)green1));
	int blue = std::floor((double)blue1 + t * ((double)blue2 - (double)blue1));

    return (blue << 16) + (green << 8) + red;
}


void Fractal::Render()
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

		delete Canvas;
		delete Iteration;

		Canvas = new int[Width * Height];
		Iteration = new int[Width * Height];

		if (Width > Height || Width == Height)
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


void Fractal::SetABC(double a, double b, double c)
{
	Var.a = a;
	Var.b = b;
	Var.c = c;
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
