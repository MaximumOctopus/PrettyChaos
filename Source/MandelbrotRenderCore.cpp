

#include "MandelbrotRenderCore.h"


MandelbrotRenderCore::MandelbrotRenderCore()
{
	Iteration = new int[1280 * 256];

   std:::thread fred (Render);
}


MandelbrotRenderCore::~MandelbrotRenderCore()
{

}


void MandelbrotRenderCore::Render()
{
	int delta = YStart * Width;

	for (int y = YStart; y < YEnd; y++)
	{
		int ydotwidth = y * Width;

		double q = ymin + (double)y * (ymax - ymin) / (double)Height;   // imaginary part

		for (int x = 0; x < Width; x++)
		{
			double p = xmin + (double)x * (xmax - xmin) / (double)Width;    // real part

			int it = 0;

			//Data[y * Width + x] = 10000000000000;
			double x1 = 0;
			double y1 = 0;
			double x2 = 0;
			double y2 = 0;
			double w = 0;

			while (x2 + y2 <= bailout_radius && it < max_iterations)
			{
				x1 = x2 - y2 + p;
				y1 = w - x2 - y2 + q;

				x2 = x1 * x1;
				y2 = y1 * y1;

				w = (x1 + y1) * (x1 + y1);

				/*if (RenderMode == __RMOrbitTrap || RenderMode == __RMOrbitTrapFilled)
				{
					double cr = x1 - Var.a;
					double ci = y1 - Var.b;

					double magnitude = std::sqrt(cr * cr + ci * ci);

					if (magnitude < Data[ydotwidth + x])
					{
						Data[ydotwidth + x] = magnitude;
					}
				} */

				it++;
			}

			switch (RenderMode)
			{
			case __RMEscapeTime:
			case __RMOrbitTrap:
			case __RMOrbitTrapFilled:
	 	    case __RMTwoTone:
			case __RMThreeTone:
			case __RMFourTone:
			case __RMFiveTone:
			{
				Iteration[ydotwidth - delta + x] = it;
				break;
			}
			/*case __RMContinuous:
			{
				if (it < max_iterations)
				{
					double log_zn = std::log(x1 * x1 + y1 * y1) / 2;
					double nu = std::log(log_zn / std::log(2)) / std::log(2);

					double itnew = it + 1 - nu;

					it = std::pow((std::floor(itnew) / max_iterations), n_coeff) * __PaletteCount;
					double it_d = (double)it + 1 - nu;

					Canvas[ydotwidth + x] = ColourUtility::LinearInterpolate(Palette[it],
																			 Palette[it + 1],
																			 it_d - (std::floorl(it_d)));
				}
				else
				{
					Canvas[ydotwidth + x] = Palette[__PaletteInfinity];
				}

				break;
			}
			case __RMDistance:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(w);

					if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];

					Iteration[ydotwidth + x] = it;
				}
				Iteration[ydotwidth + x] = it;
				break;
			}
			case __RMDistanceII:
			{
				if (it < max_iterations)
				{
					Data[ydotwidth + x] = std::sqrt(std::pow(x2 + y2, 2));

					if (Data[ydotwidth + x] > max_d) max_d = Data[ydotwidth + x];

					Iteration[ydotwidth + x] = it;
				}
				Iteration[ydotwidth + x] = it;

				break;
			}      */
			}
		}
	}
}


void MandelbrotRenderCore::SetRenderBounds(int w, int ys, int ye)
{
	Width = w;

	YStart = ys;
    YEnd = ye;
}


void MandelbrotRenderCore::SetFractalBounds(double xi, double xa, double yi, double ya)
{
	xmin = xi;
	xmax = xa;
	ymin = yi;
	ymax = ya;
}
