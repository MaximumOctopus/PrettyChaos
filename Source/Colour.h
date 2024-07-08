//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include <System.UITypes.hpp>

#include <string>


class Colour
{

public:

	int a = 0;   //
	int r = 0;   // 0 to 255
	int g = 0;   // 0 to 255
	int b = 0;   // 0 to 255

	Colour operator+(const Colour& c)
	{
		return Colour(r + c.r, g + c.g, b + c.b);
	}

	Colour operator-(const Colour& c)
	{
		return Colour(r - c.r, g - c.g, b - c.b);
	}

	Colour operator*(double factor)
	{
		return Colour(r * factor, g * factor, b * factor);
	}

	void operator+=(const Colour& c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
	}

	void operator*=(double factor)
	{
		r *= factor;
		g *= factor;
		b *= factor;
	}

	void operator>>=(int n)
	{
		r >>= n;
		g >>= n;
		b >>= n;

		a >>= n;
	}

	void Clear();

	Colour() noexcept;

	Colour(TColor color) noexcept;
	Colour(int) noexcept;
	Colour(std::wstring) noexcept;

	Colour(int, int, int) noexcept;

	void FromIntBGR(int);			// from Windows format: BGR
	void FromIntRGB(int);

	int ToIntBGR();
	int ToIntRGB();
};
