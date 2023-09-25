//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once


namespace ColourUtility
{
	System::UnicodeString BRGtoRGBHex(int bgr)
	{
		int r = (bgr & 0x0000ff);
		int g = (bgr & 0x00ff00) >> 8;
		int b = (bgr & 0xff0000) >> 16;

        return IntToHex((r << 16) + (b << 8) + g, 6);
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
		double fR = (rgb & 0xff0000) >> 16;
		double fG = (rgb & 0x00ff00) >> 8;
		double fB = (rgb & 0x0000ff);

		fR = fR / 255;
		fG = fG / 255;
		fB = fB / 255;

		double fH = H;
		double fS = S / 255;
		double fV = V / 255;

		float fCMax = std::max(std::max(fR, fG), fB);
		float fCMin = std::min(std::min(fR, fG), fB);
		float fDelta = fCMax - fCMin;

		if (fDelta > 0)
		{
			if(fCMax == fR)
			{
				fH = 60 * (fmod(((fG - fB) / fDelta), 6));
			}
			else if(fCMax == fG) {
				fH = 60 * (((fB - fR) / fDelta) + 2);
			}
			else if(fCMax == fB)
			{
				fH = 60 * (((fR - fG) / fDelta) + 4);
			}

			if (fCMax > 0)
			{
				fS = fDelta / fCMax;
			}
			else
			{
				fS = 0;
			}

			fV = fCMax;
		}
		else
		{
			fH = 0;
			fS = 0;
			fV = fCMax;
		}

		if (fH < 0)
		{
			fH = 360 + fH;
		}

		H = std::floor(fH);
		S = std::floor(fS * 255);
		V = std::floor(fV * 255);
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
}
