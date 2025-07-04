//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <fstream>
#include <Vcl.Dialogs.hpp>

#include "ColourUtility.h"
#include "Constants.h"
#include "Fast.h"
#include "Formatting.h"
#include "Palette.h"
#include "PaletteHandler.h"


Palette::Palette(int count, const std::wstring name)
{
    Description = name;

	Gradient = new TBitmap();
	Gradient->PixelFormat = pf24bit;
	Gradient->Width = 500;              // always render to 500px width image for display in paltte editor
	Gradient->Height = 1;

	AddNewKey(0x000000, 0, 0, true);
	AddNewKey(0xffffff, 0, count - 1, true);

	SetSize(count);
}


Palette::~Palette()
{
    delete Gradient;
}


// autoadd to false if the handler is about to load a new palette from a file
void Palette::Clear(bool autoadd)
{
    FileName = L"";

	Interleve = false;
	InterleveReverse = false;
	InterleveMode = 0;
	Steps = 1;
	ColourSpace = true;

	Keys.clear();

	if (autoadd)
	{
		AddNewKey(0x000000, 0, 0, true);
		AddNewKey(0xffffff, 0, 499, true);
	}
}


void Palette::SetSize(int count)
{
	if (count > 0)
	{
	    ColourCount = count;

		if (Colours != nullptr) delete Colours;
		if (PaletteR != nullptr) delete PaletteR;
		if (PaletteG != nullptr) delete PaletteG;
		if (PaletteB != nullptr) delete PaletteB;

		Colours = new Colour[count];
		PaletteR = new int[count];
		PaletteG = new int[count];
		PaletteB = new int[count];

		Render();
      	CopyPublic();
	}
}


bool Palette::Align()
{
	if (Keys.size() > 2)         // nothing to align if only two keys
	{
		int delta = Fast::Floor(500 / (Keys.size() - 1));   // 500 is the size of the rendered display

		for (int t = 2; t < Keys.size(); t++)
		{
			Keys[t].Position = delta * (t - 1);
		}

		Render();

		return true;
	}

	return false;
}


// sets key positions referenced from colour count
void Palette::NormaliseKeys()
{
	Keys[0].NormalisedPosition = 0;
	Keys[1].NormalisedPosition = ColourCount - 1;

	if (Keys.size() > 2)
	{
		for (int t = 2; t < Keys.size(); t++)
		{
			Keys[t].NormalisedPosition = (int)std::floor(((double)Keys[t].Position / 499) * (double)ColourCount);
		}
	}
}


int Palette::GradientKeyAt(int xpos)
{
	for (int t = 0; t < Keys.size(); t++)
	{
		if (Keys[t].NormalisedPosition == xpos)
		{
			return t;
		}
	}

	return -1;
 }


 int Palette::GetNextGradientKey(int xpos)
 {
	int found = -1;
	int low = 9999;

	for (int t = 0; t < Keys.size(); t++)
	{
		if (Keys[t].NormalisedPosition > xpos &&
		   Keys[t].NormalisedPosition < low)
		{
			found = t;
			low = Keys[t].NormalisedPosition;
		}
	}

	return found;
}


void Palette::Render()
{
	if (IsRendering) return;

	IsRendering = true;

	int colstart = 0;
	int colend = 0;
	int method = 0;
	int submethod = 0;
	int mode = 0;
	int gradheight = 0;
	int gradstart = 0;

	double r_delta = 0;
	double g_delta = 0;
	double b_delta = 0;
	int rdy = 0;
	int gdy = 0;
	int bdy = 0;
	double newr = 0;
	double newg = 0;
	double newb = 0;

	int newri = 0;
	int newgi = 0;
	int newbi = 0;

	int newrout = 0;
	int newgout = 0;
	int newbout = 0;

	double sr = 0;
	double sg = 0;
	double sb = 0;

	int step = 1;
	int step_count = Steps;

	NormaliseKeys();

	// ===========================================================================

	for (int y = 0; y < ColourCount; y++)
	{
		int keyat = GradientKeyAt(y);

		if (keyat != -1)
		{
			colstart = Keys[keyat].Colour;
			method = Keys[keyat].Method;
			submethod = Keys[keyat].SubMethod;
			mode = Keys[keyat].Mode;

			keyat = GetNextGradientKey(y);

			if (keyat != -1)
			{
				colend = Keys[keyat].Colour;

				gradheight = Keys[keyat].NormalisedPosition - y;
				gradstart = y;
			}
			else
			{
				colend = Keys[1].Colour;

				gradheight = ColourCount - y;
				gradstart = y;
			}

			if (mode == modeRGB)
			{
				bdy = (((colend & 0xff0000) >> 16) - ((colstart & 0xff0000) >> 16));
				gdy = (((colend & 0x00ff00) >> 8) - ((colstart & 0x00ff00) >> 8));
				rdy = ((colend & 0x0000ff) - (colstart & 0x0000ff));

				newb = (colstart & 0xff0000) >> 16;
				newg = (colstart & 0x00ff00) >> 8;
				newr = (colstart & 0x0000ff);
			}
			else
			{
				int hdy1 = 0;
				int sdy1 = 0;
				int vdy1 = 0;
				int hdy2 = 0;
				int sdy2 = 0;
				int vdy2 = 0;

				ColourUtility::BGRtoHSV(colend, hdy1, sdy1, vdy1);
				ColourUtility::BGRtoHSV(colstart, hdy2, sdy2, vdy2);

				rdy = hdy1 - hdy2;
				gdy = sdy1 - sdy2;
				bdy = vdy1 - vdy2;

				newr = hdy2;
				newg = sdy2;
				newb = vdy2;
			}

			newbout = (colstart & 0xff0000) >> 16;
			newgout = (colstart & 0x00ff00) >> 8;
			newrout = (colstart & 0x0000ff);

			r_delta = (double)rdy / (double)gradheight;
			g_delta = (double)gdy / (double)gradheight;
			b_delta = (double)bdy / (double)gradheight;
		}

		// =====================================================================

		if (ColourSpace)									// colour mode
		{
			PaletteR[y] = newrout;
			PaletteG[y] = newgout;
			PaletteB[y] = newbout;
		}
		else                                                // grayscale mode
		{
			int newgrayscale = Fast::Floor((newrout * 0.3) + (newgout * 0.59) + (newbout * 0.11));

			PaletteR[y] = newgrayscale;
			PaletteG[y] = newgrayscale;
			PaletteB[y] = newgrayscale;
		}

		// =====================================================================

		if (method == 0)    // linear
		{
			newr += r_delta;
			newg += g_delta;
			newb += b_delta;

			newri = Fast::Floor(newr);
			newgi = Fast::Floor(newg);
			newbi = Fast::Floor(newb);
		}
		else                // log
		{
			sr = std::pow(((double)y - (double)gradstart) / (double)gradheight, (double)submethod / 100) * rdy;
			sg = std::pow(((double)y - (double)gradstart) / (double)gradheight, (double)submethod / 100) * gdy;
			sb = std::pow(((double)y - (double)gradstart) / (double)gradheight, (double)submethod / 100) * bdy;

			newri = Fast::Floor(newr + sr);
			newgi = Fast::Floor(newg + sg);
			newbi = Fast::Floor(newb + sb);
		}

		// =====================================================================

		if (step == step_count)
		{
			step = 1;

			if (mode == modeRGB)
			{
				newrout = newri;
				newgout = newgi;
				newbout = newbi;
			}
			else
			{
				ColourUtility::HSVtoRGB(newri, newgi, newbi, newrout, newgout, newbout);
			}
		}
		else
		{
            step++;
        }
	}

	// copy from buffer to render bitmap

	TRGBTriple *ptr = reinterpret_cast<TRGBTriple *>(Gradient->ScanLine[0]);

	if (Interleve)
	{
		if (InterleveMode == 0)
		{
			for (int y = 0; y < 250; y++)
			{
				ptr[y * 2].rgbtRed = PaletteR[y];
				ptr[y * 2].rgbtGreen = PaletteG[y];
				ptr[y * 2].rgbtBlue = PaletteB[y];

				if (InterleveReverse)
				{
					ptr[1 + (y * 2)].rgbtRed = PaletteR[499 - y];
					ptr[1 + (y * 2)].rgbtGreen = PaletteG[499 - y];
					ptr[1 + (y * 2)].rgbtBlue = PaletteB[499 - y];
				}
				else
				{
					ptr[1 + (y * 2)].rgbtRed = PaletteR[250 + y];
					ptr[1 + (y * 2)].rgbtGreen = PaletteG[250 + y];
					ptr[1 + (y * 2)].rgbtBlue = PaletteB[250 + y];
				}
			}
		}
		else
		{
			for (int y = 0; y < 125; y++)
			{
				ptr[y * 4].rgbtRed = PaletteR[y];
				ptr[y * 4].rgbtGreen = PaletteG[y];
				ptr[y * 4].rgbtBlue = PaletteB[y];

				ptr[2 + (y * 4)].rgbtRed = PaletteR[250 + y];
				ptr[2 + (y * 4)].rgbtGreen = PaletteG[250 + y];
				ptr[2 + (y * 4)].rgbtBlue = PaletteB[250 + y];

				if (InterleveReverse)
				{
					ptr[1 + (y * 4)].rgbtRed = PaletteR[249 - y];
					ptr[1 + (y * 4)].rgbtGreen = PaletteG[249 - y];
					ptr[1 + (y * 4)].rgbtBlue = PaletteB[249 - y];

					ptr[3 + (y * 4)].rgbtRed = PaletteR[499 - y];
					ptr[3 + (y * 4)].rgbtGreen = PaletteG[499 - y];
					ptr[3 + (y * 4)].rgbtBlue = PaletteB[499 - y];
				}
				else
				{
					ptr[1 + (y * 4)].rgbtRed = PaletteR[125 + y];
					ptr[1 + (y * 4)].rgbtGreen = PaletteG[125 + y];
					ptr[1 + (y * 4)].rgbtBlue = PaletteB[125 + y];

					ptr[3 + (y * 4)].rgbtRed = PaletteR[375 + y];
					ptr[3 + (y * 4)].rgbtGreen = PaletteG[375 + y];
					ptr[3 + (y * 4)].rgbtBlue = PaletteB[375 + y];
				}
			}
		}
	}
	else
	{
		for (int pixely = 0; pixely < 500; pixely++)
		{
			int palettey = pixely;

			if (ColourCount != 500) palettey = (int)Fast::Floor(((double)pixely / 499) * (double)ColourCount);

			ptr[pixely].rgbtRed = PaletteR[palettey];
			ptr[pixely].rgbtGreen = PaletteG[palettey];
			ptr[pixely].rgbtBlue = PaletteB[palettey];
		}
	}

	IsRendering = false;
}


void Palette::CopyPublic()
{
	for (int t = 0; t < ColourCount; t++)
	{
		Colours[t] = Colour(PaletteR[t], PaletteG[t], PaletteB[t]);
	}
}


bool Palette::Load(const std::wstring file_name)
{
	std::wifstream file(file_name);

	if (file)
	{
		FileName = ExtractFileName(file_name.c_str()).c_str();

		std::wstring s(L"");

		int colour(0);
		int method(0);
		int mode(0);
		int position(0);
		bool locked(false);
		bool interleve(false);
		int interlevelevel(0);
		bool interlevereverse(false);

		while (std::getline(file, s))
		{
			if (s != L"")
			{
				if (s[0] == L'/' || s[0] == L'#')
				{
					// comment, do nothing
				}
				else
				{
					auto equals = s.find(L'=');

					std::wstring key = s.substr(0, equals);
					std::wstring value = s.substr(equals + 1);

					if (equals == std::wstring::npos)
					{
						key = s;
					}

					switch (GetKeyType(key))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
					{
						int index = AddNewKey(colour, mode, position, locked);

						if (index < 2)
						{
                            Keys[index].Locked = true;  // always lock the begin and end keys
						}

						break;
					}
					case 3:
						break;
					case 4:
						break;
					case 5:
						ColourSpace = stoi(value);
						break;
					case 6:
						colour = stoi(value);
						break;
					case 7:
						method = stoi(value);
						break;
					case 8:
						mode = stoi(value);
						break;
					case 9:
						position = stoi(value);
						break;
					case 10:
						Steps = stoi(value);
						break;

					case 11:
						interleve = stoi(value);
						break;
					case 12:
						interlevelevel = stoi(value);
						break;
					case 13:
						interlevereverse = stoi(value);
						break;

					case 14:
						SingleColour.FromIntBGR(stoi(value));
						break;

					case 15:
						locked = stoi(value);
						break;
					}
				}
			}
		}

		file.close();

		// assume load is successful!

		Interleve = interleve;
		InterleveReverse = interlevereverse;
		InterleveMode = interlevelevel;

		return true;
	}

    Clear(true);

	return false;
}


bool Palette::Save(const std::wstring file_name)
{
	std::ofstream file(file_name);

	if (file)
	{
		file << Formatting::to_utf8(L"[\n");
		file << Formatting::to_utf8(L"infinity=" + std::to_wstring(SingleColour.ToIntBGR()) + L"\n");
		file << Formatting::to_utf8(L"colourspace=" + std::to_wstring(ColourSpace) + L"\n");
		file << Formatting::to_utf8(L"steps=" + std::to_wstring(Steps) + L"\n");
		file << Formatting::to_utf8(L"interleve=" + std::to_wstring(Interleve) + L"\n");
		file << Formatting::to_utf8(L"interlever=" + std::to_wstring(InterleveReverse) + L"\n");
		if (InterleveMode)
		{
			file << Formatting::to_utf8(L"interlevex=0\n");
		}
		else
		{
			file << Formatting::to_utf8(L"interlevex=1\n");
		}

		file << Formatting::to_utf8(L"]\n");

		for (int t = 0; t < Keys.size(); t++)
		{
			file << Formatting::to_utf8(L"{\n");
			file << Formatting::to_utf8(L"colour=" + std::to_wstring(Keys[t].Colour) + L"\n");
			file << Formatting::to_utf8(L"mode=" + std::to_wstring(Keys[t].Mode) + L"\n");
			file << Formatting::to_utf8(L"method=" + std::to_wstring(Keys[t].Method) + L"\n");
			file << Formatting::to_utf8(L"position=" + std::to_wstring(Keys[t].Position) + L"\n");
			file << Formatting::to_utf8(L"locked=" + std::to_wstring(Keys[t].Locked) + L"\n");
			file << Formatting::to_utf8(L"}\n");
        }

		file.close();

		FileName = ExtractFileName(file_name.c_str()).c_str();
	}

    return true;
}


int Palette::GetKeyType(const std::wstring key)
{
	if (key == L"{")
		return 1;
	else if (key == L"}")
		return 2;
	else if (key == L"[")
		return 3;
	else if (key == L"]")
		return 4;
	else if (key == L"colourspace")
		return 5;
	else if (key == L"colour")
		return 6;
	else if (key == L"method")
		return 7;
	else if (key == L"mode")
		return 8;
	else if (key == L"position")
		return 9;
	else if (key == L"steps")
		return 10;
	else if (key == L"interleve")
		return 11;
	else if (key == L"interlevex")
		return 12;
	else if (key == L"interlever")
		return 13;
	else if (key == L"infinity")
		return 14;
	else if (key == L"locked")
		return 15;

	return 0;
}


void Palette::SetFromTemp()
{
	GradientDirection = TempGradientDirection;
	IsGradient = TempIsGradient;
	SingleColour = TempSingleColour;
}


void Palette::CopyToTemp()
{
	TempGradientDirection = GradientDirection;
	TempIsGradient = IsGradient;
	TempSingleColour = SingleColour;
}


int Palette::AddNewKey(int colour, int mode, int position, bool locked)
{
	PaletteKey pk;
	pk.Colour = colour;
	pk.Mode = mode;
	pk.Position = position;
    pk.Locked = locked;

	Keys.push_back(pk);

	return Keys.size() - 1;
}

