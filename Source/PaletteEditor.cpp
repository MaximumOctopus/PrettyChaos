//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <vcl.h>
#pragma hdrstop

#include <fstream>

#include "FormColourDialog.h"

#include "Constants.h"
#include "ColourUtility.h"
#include "Formatting.h"
#include "PaletteEditor.h"
#include "Utility.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPaletteEditor *frmPaletteEditor;


__fastcall TfrmPaletteEditor::TfrmPaletteEditor(TComponent* Owner)
	: TForm(Owner)
{
	bGradient = new TBitmap();
	bGradient->PixelFormat = pf24bit;
	bGradient->Width = __PaletteCount;
	bGradient->Height = 1;

	for (int t = 0; t < 3; t++)
	{
		RGBGradients[t] = new TBitmap();
		RGBGradients[t]->PixelFormat = pf24bit;
		RGBGradients[t]->Width = 255;
		RGBGradients[t]->Height = 1;
	}

	AddNewKey(0x000000, 0, 0);
	AddNewKey(0xffffff, 0, 499);

	KeySelected = 0;

	UpdateKeyDisplay(KeySelected);

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::FormDestroy(TObject *Sender)
{
	delete bGradient;
    delete RGBGradients[2];
	delete RGBGradients[1];
	delete RGBGradients[0];
}


void __fastcall TfrmPaletteEditor::FormShow(TObject *Sender)
{
	RenderGradient();

	sInfinity->Brush->Color = TColor(Palette[__PaletteInfinity]);
}


void __fastcall TfrmPaletteEditor::FormPaint(TObject *Sender)
{
	if (pcColourSpace->TabIndex == 0)
	{
		BuildRGBGradients();
	}
	else
	{
		BuildHSVGradients();
	}

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::pbRedPaint(TObject *Sender)
{
	TRGBTriple *ptr1 = reinterpret_cast<TRGBTriple *>(RGBGradients[0]->ScanLine[0]);

	for (int t = 0; t < 256; t++)
	{
		ptr1[t].rgbtRed = t;
		ptr1[t].rgbtGreen = tbGreen->Position;
		ptr1[t].rgbtBlue = tbBlue->Position;
	}

	for (int t = 0; t < 4; t++)
	{
		pbRed->Canvas->Draw(0, t, RGBGradients[0]);
	}
}


void __fastcall TfrmPaletteEditor::pbGreenPaint(TObject *Sender)
{
	TRGBTriple *ptr2 = reinterpret_cast<TRGBTriple *>(RGBGradients[1]->ScanLine[0]);

	for (int t = 0; t < 256; t++)
	{
		ptr2[t].rgbtRed = tbRed->Position;
		ptr2[t].rgbtGreen = t;
		ptr2[t].rgbtBlue = tbBlue->Position;
	}

	for (int t = 0; t < 4; t++)
	{
		pbGreen->Canvas->Draw(0, t, RGBGradients[1]);
	}
}


void __fastcall TfrmPaletteEditor::pbBluePaint(TObject *Sender)
{
	TRGBTriple *ptr3 = reinterpret_cast<TRGBTriple *>(RGBGradients[2]->ScanLine[0]);

	for (int t = 0; t < 256; t++)
	{
		ptr3[t].rgbtRed = tbRed->Position;
		ptr3[t].rgbtGreen = tbGreen->Position;
		ptr3[t].rgbtBlue = t;
	}

	for (int t = 0; t < 4; t++)
	{
		pbBlue->Canvas->Draw(0, t, RGBGradients[2]);
	}
}


void __fastcall TfrmPaletteEditor::pbHuePaint(TObject *Sender)
{
	TRGBTriple *ptr1 = reinterpret_cast<TRGBTriple *>(RGBGradients[0]->ScanLine[0]);

	int r, g, b;

	for (int i = 0; i < 256; i++)
	{
		ColourUtility::HSVtoRGB(std::floor(((double)i / 255) * 360), tbSaturation->Position, tbValue->Position, r, g, b);
		ptr1[i].rgbtBlue  = b;
		ptr1[i].rgbtGreen = g;
		ptr1[i].rgbtRed   = r;
	}

	for (int t = 0; t < 4; t++)
	{
		pbHue->Canvas->Draw(0, t, RGBGradients[0]);
	}
}


void __fastcall TfrmPaletteEditor::pbSaturationPaint(TObject *Sender)
{
	TRGBTriple *ptr2 = reinterpret_cast<TRGBTriple *>(RGBGradients[1]->ScanLine[0]);

	int r, g, b;

	for (int i = 0; i < 256; i++)
	{
		ColourUtility::HSVtoRGB(tbHue->Position, i, tbValue->Position, r, g, b);
		ptr2[i].rgbtBlue  = b;
		ptr2[i].rgbtGreen = g;
		ptr2[i].rgbtRed   = r;
	}

	for (int t = 0; t < 4; t++)
	{
		pbSaturation->Canvas->Draw(0, t, RGBGradients[1]);
	}
}


void __fastcall TfrmPaletteEditor::pbValuePaint(TObject *Sender)
{
	TRGBTriple *ptr3 = reinterpret_cast<TRGBTriple *>(RGBGradients[2]->ScanLine[0]);

	int r, g, b;

	for (int i = 0; i < 256; i++)
	{
		ColourUtility::HSVtoRGB(tbHue->Position, tbSaturation->Position, i, r, g, b);
		ptr3[i].rgbtBlue  = b;
		ptr3[i].rgbtGreen = g;
		ptr3[i].rgbtRed   = r;
	}

	for (int t = 0; t < 4; t++)
	{
		pbValue->Canvas->Draw(0, t, RGBGradients[2]);
	}
}


void TfrmPaletteEditor::AddNewKey(int colour, int mode, int position)
{
	TShape* ts = new TShape(this);
	ts->Parent = gbColour;
	ts->Width = 10;
	ts->Height = 10;
	ts->Top = __KeyTop;
	ts->Left = position + __KeyOffset;
	ts->Brush->Color = TColor(colour);
	ts->Tag = PaletteKeys.size();
	ts->OnMouseDown = shapeStartColourMouseDown;
	ts->OnMouseUp = shapeStartColourMouseUp;

	if (PaletteKeys.size() < 2)
	{
		ts->Shape = stSquare;
	}
	else
	{
		ts->Shape = stCircle;
		ts->OnMouseMove = shapeStartColourMouseMove;
	}

	PaletteKey pk;
	pk.Colour = ts->Brush->Color;
    pk.Mode = mode;
	pk.Shape = ts;
	pk.Position = position;

	PaletteKeys.push_back(pk);
}


// updates the key information (colours etc) for the object
// with the index key_index in the palettekeys array
void TfrmPaletteEditor::UpdateKeyDisplay(int key_index)
{
	KeyDisplayUpdating = true;

	PaletteKey &pk = PaletteKeys[key_index];

	if (pcColourSpace->TabIndex == 0)
	{
		tbRed->Position = pk.Colour & 0x0000ff;
		tbGreen->Position = (pk.Colour >> 8) & 0x0000ff;
		tbBlue->Position = (pk.Colour >> 16) & 0x0000ff;

		seRed->Value = tbRed->Position;
		seGreen->Value = tbGreen->Position;
		seBlue->Value = tbBlue->Position;
	}
	else
	{
		int H, S, V;

		ColourUtility::BGRtoHSV(pk.Colour, H, S, V);

		tbHue->Position = H;
		tbSaturation->Position = S;
		tbValue->Position = V;

		seHue->Value = H;
		seSaturation->Value = S;
		seValue->Value = V;
	}

	sePosition->Value = pk.Position;

	if (pk.Method == 0)
	{
		sbLinear->Down = true;
	}
	else
	{
		sbLog->Down = true;
	}

	if (pk.Mode == 0)
	{
		sbRGB->Down = true;
	}
	else
	{
		sbHSV->Down = true;
	}

	BuildRGBGradients();

	KeyDisplayUpdating = false;
}


void __fastcall TfrmPaletteEditor::tbRedChange(TObject *Sender)
{
	if (!SliderUpdating && !KeyDisplayUpdating)
	{
		SliderUpdating = true;

		seRed->Value = tbRed->Position;
		seGreen->Value = tbGreen->Position;
		seBlue->Value = tbBlue->Position;

		PaletteKey &pk = PaletteKeys[KeySelected];

		pk.Shape->Brush->Color = TColor(tbRed->Position + (tbGreen->Position << 8) + (tbBlue->Position << 16));
		pk.Colour = pk.Shape->Brush->Color;

		lHexRed->Caption = IntToHex(tbRed->Position, 2);
		lHexGreen->Caption = IntToHex(tbGreen->Position, 2);
		lHexBlue->Caption = IntToHex(tbBlue->Position, 2);

		lColourHex->Caption = ColourUtility::BRGtoRGBHex(pk.Colour);

		BuildRGBGradients();

		RenderGradient();

		SliderUpdating = false;
	}
}


void __fastcall TfrmPaletteEditor::tbHueChange(TObject *Sender)
{
	if (!SliderUpdating && !KeyDisplayUpdating)
	{
		SliderUpdating = true;

		int r, g, b;

		ColourUtility::HSVtoRGB(tbHue->Position, tbSaturation->Position, tbValue->Position, r, g, b);

		int colour = (r) + (g << 8) + (b << 16);

		PaletteKeys[KeySelected].Shape->Brush->Color = TColor(colour);
		PaletteKeys[KeySelected].Colour = colour;

		lColourHex->Caption = "0x" + IntToHex(colour, 6);

		seHue->Value = tbHue->Position;
		seSaturation->Value = tbSaturation->Position;
		seValue->Value = tbValue->Position;

		BuildHSVGradients();

		RenderGradient();

        SliderUpdating = false;
    }
}


void TfrmPaletteEditor::BuildRGBGradients()
{
	pbRedPaint(nullptr);
	pbGreenPaint(nullptr);
	pbBluePaint(nullptr);
}


void TfrmPaletteEditor::BuildHSVGradients()
{
	pbHuePaint(nullptr);
	pbSaturationPaint(nullptr);
	pbValuePaint(nullptr);
}


void __fastcall TfrmPaletteEditor::sbClearClick(TObject *Sender)
{
	ClearPalette();

	AddNewKey(0x000000, 0, 0);
	AddNewKey(0xffffff, 0, 499);

	ResetUI();

	UpdateKeyDisplay(KeySelected);
}


void __fastcall TfrmPaletteEditor::sbAddNewKeyClick(TObject *Sender)
{
	AddNewKey(0xaaaaaa, 0, 200);

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::sbDeleteSelectedKeyClick(TObject *Sender)
{
	if (KeySelected > 1)
	{
		delete PaletteKeys[KeySelected].Shape;
		PaletteKeys.erase(PaletteKeys.begin() + KeySelected);

		for (int t = 0; t < PaletteKeys.size(); t++)
		{
			PaletteKeys[t].Shape->Tag = t;
		}

		if (KeySelected != 0)
		{
			KeySelected--;
		}
		else
		{
			KeySelected = 0;
		}

		UpdateKeyDisplay(KeySelected);

		RenderGradient();
    }
}


void __fastcall TfrmPaletteEditor::sbAlignAllClick(TObject *Sender)
{
	if (PaletteKeys.size() > 2)         // nothing to align if only two keys
	{
		int delta = std::floor(__PaletteCount / (PaletteKeys.size() - 1));

		for (int t = 2; t < PaletteKeys.size(); t++)
		{
			PaletteKeys[t].Shape->Left = (delta * (t - 1)) + __KeyOffset;
			PaletteKeys[t].Position = delta * (t - 1);
		}

		iPointer->Left = PaletteKeys[KeySelected].Shape->Left;

		RenderGradient();
    }
}


void __fastcall TfrmPaletteEditor::sbColourClick(TObject *Sender)
{
	RenderGradient();
}


void __fastcall TfrmPaletteEditor::shapeStartColourMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (Shift.Contains(ssRight))
	{
		// show colour dialog to do
	}
	else if (Shift.Contains(ssLeft))
	{
		TShape *shape = (TShape*)Sender;

		if (shape->Tag >= 2)
		{
			KeyMoveMode = true;
			KeyInitialX = X;
        }

		iPointer->Left = shape->Left;

		KeySelected = shape->Tag;

        UpdateKeyDisplay(KeySelected);
    }
}


void __fastcall TfrmPaletteEditor::shapeStartColourMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	if (KeyMoveMode)
	{
		if (Shift.Contains(ssLeft))
		{
			TShape *shape = (TShape*)Sender;

			if (shape->Left + (X - 5) > 515)
			{
				shape->Left = 515;
				iPointer->Left = shape->Left;
			}
			else if (shape->Left + (X - 5) < __KeyOffset)
			{
				shape->Left = __KeyOffset;
				iPointer->Left = shape->Left;
			}
			else
			{
				shape->Left = shape->Left + (X - 5);
				iPointer->Left = shape->Left;
			}

			PaletteKeys[KeySelected].Position = shape->Left - __KeyOffset;

            RenderGradient();
        }
    }
}


void __fastcall TfrmPaletteEditor::shapeStartColourMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	KeyMoveMode = false;
}


int TfrmPaletteEditor::GradientKeyAt(int xpos)
{
	for (int t = 0; t < PaletteKeys.size(); t++)
	{
		if (PaletteKeys[t].Position == xpos)
		{
			return t;
		}
	}

	return -1;
 }


 int TfrmPaletteEditor::GetNextGradientKey(int xpos)
 {
	int found = -1;
	int low = 9999;

	for (int t = 0; t < PaletteKeys.size(); t++)
	{
		if (PaletteKeys[t].Position > xpos &&
		   PaletteKeys[t].Position < low)
		{
			found = t;
			low = PaletteKeys[t].Position;
		}
	}

	return found;
}


void TfrmPaletteEditor::RenderGradient()
{
	if (IsRendering) return;

	IsRendering = true;

   	int colstart = 0;
	int colend = 0;
	int method = 0;
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
	int step_count = cbSteps->Text.ToInt();

	// ===========================================================================

	for (int y = 0; y < __PaletteCount; y++)
	{
		int keyat = GradientKeyAt(y);

		if (keyat != -1)
		{
			colstart = PaletteKeys[keyat].Colour;
			method = PaletteKeys[keyat].Method;
			mode = PaletteKeys[keyat].Mode;

			keyat = GetNextGradientKey(y);

			if (keyat != -1)
			{
				colend = PaletteKeys[keyat].Colour;

				gradheight = PaletteKeys[keyat].Position - y;
				gradstart = y;
			}
			else
			{
				colend = PaletteKeys[1].Colour;

				gradheight = __PaletteCount - y;
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

		TRGBTriple *ptr;

		if (sbColour->Down)									// colour mode
		{
			ptr = reinterpret_cast<TRGBTriple *>(bGradient->ScanLine[0]);

			ptr[y].rgbtRed   = newrout;
			ptr[y].rgbtGreen = newgout;
			ptr[y].rgbtBlue  = newbout;
		}
		else                                                // grayscale mode
		{
			int newgrayscale = floor((newrout * 0.3) + (newgout * 0.59) + (newbout * 0.11));

			ptr = reinterpret_cast<TRGBTriple *>(bGradient->ScanLine[0]);

			ptr[y].rgbtRed   = newgrayscale;
			ptr[y].rgbtGreen = newgrayscale;
			ptr[y].rgbtBlue  = newgrayscale;
		}

		// =====================================================================

		if (method == 0)
		{
			newr += r_delta;
			newg += g_delta;
			newb += b_delta;

			newri = std::floor(newr);
			newgi = std::floor(newg);
			newbi = std::floor(newb);
		}
		else
		{
			sr = std::pow(((double)y - (double)gradstart) / (double)gradheight, (double)tbLog->Position / 50) * rdy;
			sg = std::pow(((double)y - (double)gradstart) / (double)gradheight, (double)tbLog->Position / 50) * gdy;
			sb = std::pow(((double)y - (double)gradstart) / (double)gradheight, (double)tbLog->Position / 50) * bdy;

			newri = std::floor(newr + sr);
			newgi = std::floor(newg + sg);
			newbi = std::floor(newb + sb);
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

	for (int t = 0; t < 25; t++)
	{
		pbGradient->Canvas->Draw(0, t, bGradient);
	}

	IsRendering = false;
}


void __fastcall TfrmPaletteEditor::bAcceptClick(TObject *Sender)
{
	TRGBTriple *ptr;

	ptr = reinterpret_cast<TRGBTriple *>(bGradient->ScanLine[0]);

	// render palette to public
	for (int t = 0; t < __PaletteCount; t++)
	{
		Palette[t] = ptr[t].rgbtRed + (ptr[t].rgbtGreen << 8) + (ptr[t].rgbtBlue << 16);
	}

	Palette[__PaletteInfinity] = sInfinity->Brush->Color;

    HasPalette = true;
}


void __fastcall TfrmPaletteEditor::bSaveClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(2);

	if (!file_name.empty())
	{
		if (file_name.find(L".palette") == std::wstring::npos)
		{
			file_name += L".palette";
		}

		SavePalette(file_name);
	}
}


void __fastcall TfrmPaletteEditor::bLoadClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetOpenFileName(2);

	if (!file_name.empty())
	{
		if (file_name.find(L".palette") == std::wstring::npos)
		{
			file_name += L".palette";
		}

		ClearPalette();
		ResetUI();

		if (LoadPalette(file_name))
		{
			RenderGradient();

			UpdateKeyDisplay(KeySelected);
        }
	}
}


void TfrmPaletteEditor::ClearPalette()
{
	for (int t = PaletteKeys.size() - 1; t >= 0; t--)
	{
		delete PaletteKeys[t].Shape;

		PaletteKeys.pop_back();
	}
}


void TfrmPaletteEditor::ResetUI()
{
	KeyMoveMode = false;
	KeySelected = 0;
	iPointer->Left = __KeyOffset;
}


void TfrmPaletteEditor::SavePalette(std::wstring file_name)
{
	std::ofstream file(file_name);

	if (file)
	{
		std::wstring steps = cbSteps->Text.c_str();

		file << Formatting::to_utf8(L"[\n");
		file << Formatting::to_utf8(L"infinity=" + std::to_wstring(sbColour->Down) + L"\n");
		file << Formatting::to_utf8(L"steps=" + steps + L"\n");
		file << Formatting::to_utf8(L"]\n");

		for (int t = 0; t < PaletteKeys.size(); t++)
		{
			file << Formatting::to_utf8(L"{\n");
			file << Formatting::to_utf8(L"colour=" + std::to_wstring(PaletteKeys[t].Colour) + L"\n");
			file << Formatting::to_utf8(L"mode=" + std::to_wstring(PaletteKeys[t].Mode) + L"\n");
			file << Formatting::to_utf8(L"method=" + std::to_wstring(PaletteKeys[t].Method) + L"\n");
			file << Formatting::to_utf8(L"position=" + std::to_wstring(PaletteKeys[t].Position) + L"\n");
			file << Formatting::to_utf8(L"}\n");
        }

		file.close();
	}
}


bool TfrmPaletteEditor::LoadPalette(std::wstring file_name)
{
	std::wifstream file(file_name);

	if (file)
	{
		std::wstring s(L"");

		int colour(0);
        int method(0);
		int mode(0);
		int position(0);
		int infinity(0);
		std::wstring steps(L"");

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
						AddNewKey(colour, mode, position);

						break;
					}
					case 3:
						break;
					case 4:
						break;
					case 5:
						infinity = stoi(value);
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
						steps = value;
						break;
                    }
				}
			}
		}

		file.close();

		sInfinity->Brush->Color = TColor(infinity);
		lInfinityHex->Caption = ColourUtility::BRGtoRGBHex(infinity);

		cbSteps->Text = steps.c_str();

		return true;
	}

	return false;
}


int TfrmPaletteEditor::GetKeyType(const std::wstring key)
{
	if (key == L"{")
		return 1;
	else if (key == L"}")
		return 2;
	else if (key == L"[")
		return 3;
	else if (key == L"]")
		return 4;
	else if (key == L"infinity")
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

	return 0;
}


void __fastcall TfrmPaletteEditor::sePositionChange(TObject *Sender)
{
	if (KeySelected != -1 && KeySelected >= 2)
	{
		PaletteKeys[KeySelected].Position = sePosition->Value;

		PaletteKeys[KeySelected].Shape->Left = sePosition->Value + 20;
		iPointer->Left = PaletteKeys[KeySelected].Shape->Left;
    }
}


void __fastcall TfrmPaletteEditor::sInfinityMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (frmColourDialog->ShowModal() == mrOk)
	{
		sInfinity->Brush->Color = TColor(frmColourDialog->SelectedColour);

		lInfinityHex->Caption = ColourUtility::BRGtoRGBHex(frmColourDialog->SelectedColour);
    }
}


void __fastcall TfrmPaletteEditor::seRedChange(TObject *Sender)
{
	tbRed->Position = seRed->Value;

	tbRedChange(nullptr);
}


void __fastcall TfrmPaletteEditor::seGreenChange(TObject *Sender)
{
	tbGreen->Position = seGreen->Value;

	tbRedChange(nullptr);
}


void __fastcall TfrmPaletteEditor::seBlueChange(TObject *Sender)
{
	tbBlue->Position = seBlue->Value;

	tbRedChange(nullptr);
}


void __fastcall TfrmPaletteEditor::sbRGBClick(TObject *Sender)
{
	TSpeedButton* sb = (TSpeedButton*)Sender;

	PaletteKeys[KeySelected].Mode = sb->Tag;

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::seHueChange(TObject *Sender)
{
	tbHue->Position = seHue->Value;

	tbHueChange(nullptr);
}


void __fastcall TfrmPaletteEditor::seSaturationChange(TObject *Sender)
{
	tbSaturation->Position = seSaturation->Value;

	tbHueChange(nullptr);
}


void __fastcall TfrmPaletteEditor::seValueChange(TObject *Sender)
{
	tbValue->Position = seValue->Value;

	tbHueChange(nullptr);
}


void __fastcall TfrmPaletteEditor::sbLinearClick(TObject *Sender)
{
	TSpeedButton* sb = (TSpeedButton*)Sender;

	PaletteKeys[KeySelected].Method = sb->Tag;

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::pcColourSpaceChange(TObject *Sender)
{
	if (pcColourSpace->TabIndex == 0)
	{
		int r, g, b;

		ColourUtility::HSVtoRGB(tbHue->Position, tbSaturation->Position, tbValue->Position,
			r, g, b);

		tbRed->Position = r;
		tbGreen->Position = g;
		tbBlue->Position = b;

		tbRedChange(nullptr);
	}
	else
	{
		int h, s, v;
		int colour = (tbRed->Position << 16) + (tbGreen->Position << 8) + tbBlue->Position;

		ColourUtility::RGBtoHSV(colour, h, s, v);

		tbHue->Position = h;
		tbSaturation->Position = s;
		tbValue->Position = v;

		tbHueChange(nullptr);
	}
}
