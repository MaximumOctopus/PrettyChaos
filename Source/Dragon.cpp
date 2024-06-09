//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Dragon_curve
// https://www.rosettacode.org/wiki/Dragon_curve

#include <Vcl.Dialogs.hpp>

#include <algorithm>
#include <string>

#include "Constants.h"
#include "Dragon.h"


Dragon::Dragon() : Fractal()
{
	AcceptsABC = true;
	AcceptsVarA = true;

	AcceptsZoom = false;

	Var.a = 16;

	Name = L"Dragon curve";

	max_iterations = 4;

	RenderModes.push_back(L"Iteration");
	RenderModes.push_back(L"Direction");
	RenderModes.push_back(L"Distance");
	RenderModes.push_back(L"Distance Alt");

	NameA = L"Recursions";

    ResetView();
}


Dragon::~Dragon()
{
}


void Dragon::Generate(int iterations)
{
    generator = L"";

	generator.push_back( 1 );
	std::wstring temp;

	for( int y = 0; y < iterations - 1; y++ )
	{
		temp = generator;
		temp.push_back( 1 );

		for(std::wstring::reverse_iterator x = generator.rbegin(); x != generator.rend(); x++)
			temp.push_back( !( *x ) );

		generator = temp;
	}
}


void Dragon::PreRender(bool preview)
{
	if (preview) SwapDimensions();

	Render(-1, -1);

	if (preview) SwapDimensions();
}


void Dragon::Render(int hstart, int hend)
{
	StartTime = std::chrono::system_clock::now();

	Generate(Var.a);

	int i = 0;
	int LEN = 1;
	int dir = __West;
	int from_x = 0;
	int from_y = 0;
	int colour = 0;

	TRGBTriple *ptr;

	for (int y = 0; y < Height; y++)
	{
		ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

		for (int x = 0; x < Width; x++)
		{
			ptr[x].rgbtRed = PaletteInfintyR;
			ptr[x].rgbtGreen = PaletteInfintyG;
			ptr[x].rgbtBlue = PaletteInfintyB;
		}
	}

	int palette_range = std::floor(500 / (double)max_iterations) - 1;

	// maximum distance from the centre of the image
	int maxdim = std::floor(std::sqrt(((Height / 2) * (Height / 2)) + ((Width / 2) * (Width / 2))));

	for (int t = 0; t < max_iterations; t++ )
	{
		int a = std::floor(Width / 2);
		int b = std::floor(Height / 2);
		a += __Move[i++];
		b += __Move[i++];

		from_x = a;
		from_y = b;

		for(std::wstring::iterator x = generator.begin(); x < generator.end(); x++ )
		{
			switch( dir )
			{
			case __North:
				if (*x)
				{
					a += LEN;
					dir = __East;
				}
				else
				{
					a -= LEN;
					dir = __West;
				}
				break;
			case __East:
				if (*x)
				{
					b += LEN;
					dir = __South;
				}
				else
				{
					b -= LEN;
					dir = __North;
				}
				break;
			case __South:
				if (*x)
				{
					a -= LEN;
					dir = __West;
				}
				else
				{
					a += LEN;
					dir = __East;
				}
				break;
			case __West:
				if (*x)
				{
					b -= LEN;
					dir = __North;
				}
				else
				{
					b += LEN;
					dir = __South;
				}
				break;
			}


			switch (RenderMode)
			{
			case 0:
				colour = (t + 1) * palette_range;
				break;
			case 1:
				colour = std::floor((dir / 3) * 499) ;
				break;
			case 2:
			{
				int nx = std::floor(from_x - (Width / 2));
				int ny = std::floor(from_y - (Height / 2));

				colour = t * palette_range + std::floor( std::pow(std::sqrt(nx * nx + ny * ny) / maxdim, n_coeff) * palette_range);//__PaletteCount);
				break;
			}
			case 3:
			{
				int nx = std::floor(from_x - (Width / 2));
				int ny = std::floor(from_y - (Height / 2));

				colour = (t % 2) * 250 + std::floor( std::pow(std::sqrt(nx * nx + ny * ny) / maxdim, n_coeff) * 250);//__PaletteCount);
				break;
			}
			}

			DrawLine(from_x, from_y, a, b, colour);
			from_x = a;
			from_y = b;
		}
	}

	CalculateRenderTime();
}


void Dragon::DrawLine(int x1, int y1, int x2, int y2, int colour)
{
	TRGBTriple *ptr;

	int x,y,dx,dy,dx1,dy1,px,py,xe,ye;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}

		if (y < Height && y >= 0 && x < Width && x >= 0)
		{
			ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

			ptr[x].rgbtRed = Palette[colour] & 0x0000ff;
			ptr[x].rgbtGreen = Palette[colour] >> 8 & 0x0000ff;
			ptr[x].rgbtBlue = Palette[colour] >> 16;
		}

		for (int i = 0; x < xe; i++)
		{
			x = x + 1;

			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}

				px = px + 2 * (dy1 - dx1);
			}

			if (y < Height && y >= 0 && x < Width && x >= 0)
			{
				ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

				ptr[x].rgbtRed = Palette[colour] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[colour] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[colour] >> 16;
			}
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}

		if (y < Height && y >= 0 && x < Width && x >= 0)
		{
			ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

			ptr[x].rgbtRed = Palette[colour] & 0x0000ff;
			ptr[x].rgbtGreen = Palette[colour] >> 8 & 0x0000ff;
			ptr[x].rgbtBlue = Palette[colour] >> 16;
		}

		for (int i = 0; y < ye; i++)
		{
			y = y + 1;

			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}

				py = py + 2 * (dx1 - dy1);
			}

			if (y < Height && y >= 0 && x < Width && x >= 0)
			{
				ptr = reinterpret_cast<TRGBTriple *>(RenderCanvas->ScanLine[y]);

				ptr[x].rgbtRed = Palette[colour] & 0x0000ff;
				ptr[x].rgbtGreen = Palette[colour] >> 8 & 0x0000ff;
				ptr[x].rgbtBlue = Palette[colour] >> 16;
			}
		}
	}
}


void Dragon::ResetView()
{
	int x_min = std::floor(-(double)Width / (2 * 1));
	int x_max = std::floor((double)Width / (2 * 1));

	int y_min = std::floor(-(double)Height / (2 * 1));
	int y_max = std::floor((double)Height / (2 * 1));

	SetView(x_min, x_max, y_min, y_max);
}


void Dragon::ResetAll()
{
	Var.a = 16;

	max_iterations = 4;

	ResetView();
}


std::wstring Dragon::GetParameters()
{
	return L"render mode: " + RenderModes[RenderMode] +
		   L"; recursions: " + std::to_wstring(Var.a) + L"; max iterations: " + std::to_wstring(max_iterations);
}


void Dragon::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(L"Dragon fractal\n");
	ofile << Formatting::to_utf8(L"    Size       : " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"    Rendermode : " + RenderModes[RenderMode] + L" (" + std::to_wstring(RenderMode) + L")\n");
	ofile << Formatting::to_utf8(L"    Iterations : " + std::to_wstring(max_iterations) + L"\n");
	ofile << Formatting::to_utf8(L"    n coeff    : " + std::to_wstring(n_coeff) + L"\n");
	ofile << Formatting::to_utf8(L"    recursions : " + std::to_wstring(Var.a) + L"\n");
}
