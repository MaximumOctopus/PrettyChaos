//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <System.SysUtils.hpp>
#include "ColourUtility.h"


namespace ColourUtility
{
	System::UnicodeString BRGtoRGBHex(int bgr)
	{
		int r = (bgr & 0x0000ff);
		int g = (bgr & 0x00ff00) >> 8;
		int b = (bgr & 0xff0000) >> 16;

		return "0x" + IntToHex((r << 16) + (g << 8) + b, 6);
	}


	void BGRtoHSV(int rgb, int &H, int &S, int &V)
	{
		int r = (rgb & 0x0000ff);
		int g = (rgb & 0x00ff00) >> 8;
		int b = (rgb & 0xff0000) >> 16;

		int MinValue = std::min(std::min(r, g), b);
		V            = std::max(std::max(r, g), b);

		int Delta = V - MinValue;

		// Calculate saturation:  saturation is 0 if r, g and b are all 0
		if (V == 0)
		{
			S = 0;
		}
		else
		{
			S  = std::floor(std::div(255 * Delta, V).quot);
		}

		if (S == 0)
		{
			H = 0;
		}
		else
		{
			if (r == V)
			{
				H = std::floor(std::div(60*(g-b), Delta).quot);
			}
			else if (g == V)
			{
				H = std::floor(120 + std::div((60*(b-r)), Delta).quot);
			}
			else if (b == V)
			{
				H = std::floor(240 + std::div((60 * ( r - g)), Delta).quot);
			}
		  }

		if (H < 0)
		{
			H = H + 360;
		}
	}


	void RGBtoHSV(int rgb, int &H, int &S, int &V)
	{
		double r = (rgb & 0xff0000) >> 16;
		double g = (rgb & 0x00ff00) >> 8;
		double b = (rgb & 0x0000ff);

		int MinValue = std::min(std::min(r, g), b);
		V            = std::max(std::max(r, g), b);

		int Delta = V - MinValue;

		// Calculate saturation:  saturation is 0 if r, g and b are all 0
		if (V == 0)
		{
			S = 0;
		}
		else
		{
			S  = std::floor(std::div(255 * Delta, V).quot);
		}

		if (S == 0)
		{
			H = 0;
		}
		else
		{
			if (r == V)
			{
				H = std::floor(std::div(60*(g-b), Delta).quot);
			}
			else if (g == V)
			{
				H = std::floor(120 + std::div((60*(b-r)), Delta).quot);
			}
			else if (b == V)
			{
				H = std::floor(240 + std::div((60 * ( r - g)), Delta).quot);
			}
		  }

		if (H < 0)
		{
			H = H + 360;
		}
	}


	void HSVtoRGB(int H, int S, int V, int &R, int &G, int &B)
	{
		if (S <= 0)
		{
			R = V;
			G = V;
			B = V;

			return;
		}
		else
		{
			double news = (double)S / 255;
			double newv = (double)V / 255;

			double hh = H;
			if(hh >= 360.0) hh = 0.0;
			hh /= 60.0;
			int i = (int)hh;
			double ff = hh - i;
			double p = (newv * (1.0 - news));
			double q = (newv * (1.0 - (news * ff)));
			double t = (newv * (1.0 - (news * (1.0 - ff))));

			switch (i)
			{
			case 0:
				R = std::round(newv * 255);
				G = std::round(t * 255);
				B = std::round(p * 255);
				break;
			case 1:
				R =std::round(q * 255);
				G = std::round(newv * 255);
				B = std::round(p * 255);
				break;
			case 2:
				R = std::round(p * 255);
				G = std::round(newv * 255);
				B = std::round(t * 255);
				break;
			case 3:
				R = std::round(p * 255);
				G = std::round(q * 255);
				B = std::round(newv * 255);
				break;
			case 4:
				R = std::round(t * 255);
				G = std::round(p * 255);
				B = std::round(newv * 255);
				break;
			case 5:
			default:
				R = std::round(newv * 255);
				G = std::round(p * 255);
				B = std::round(q * 255);
				break;
			}
		}
	}


	int LinearInterpolate(int colour1, int colour2, double t)
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
}
