//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include "Constants.h"
#include "Colour.h"


Colour::Colour() noexcept
{
	r = 0;
	g = 0;
	b = 0;

    a = 0;
}


Colour::Colour(TColor color) noexcept
{
	r = (color & 0x0000FF);
	g = (color & 0x00FF00) >> 8;
	b = (color & 0xFF0000) >> 16;
}


Colour::Colour(std::wstring s) noexcept
{

}


Colour::Colour(int R, int G, int B) noexcept
{
	r = R;
	g = G;
	b = B;
}


void Colour::Clear()
{
	r = 0;
	g = 0;
	b = 0;

    a = 0;
}


#ifdef _GUI
TRGBTriple Colour::ToRGBTriple()
{
	TRGBTriple t;
	t.rgbtRed = To255(r);
	t.rgbtGreen = To255(g);
	t.rgbtBlue = To255(b);

	return t;
}
#endif


int Colour::ToIntBGR()
{
	return (b << 16) + (g << 8) + r;
}


int Colour::ToIntRGB()
{
	return (r << 16) + (g << 8) + b;
}


void Colour::FromIntBGR(int colour)
{
	r = (colour & 0x0000FF);
	g = (colour & 0x00FF00) >> 8;
	b = (colour & 0xFF0000) >> 16;
}


void Colour::FromIntRGB(int colour)
{
	r = (colour & 0xFF0000) >> 16;
	g = (colour & 0x00FF00) >> 8;
	b = (colour & 0x0000FF);
}
