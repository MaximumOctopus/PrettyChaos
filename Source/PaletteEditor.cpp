//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
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
#include "Fast.h"
#include "Formatting.h"
#include "PaletteEditor.h"
#include "PaletteHandler.h"
#include "Utility.h"

extern PaletteHandler *GPaletteHandler;

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPaletteEditor *frmPaletteEditor;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

bool OpenPalette(int index, const std::wstring palette_path)
{
	bool is_ok = false;

	TfrmPaletteEditor *frmPaletteEditor = new TfrmPaletteEditor(Application);

	frmPaletteEditor->CurrentPaletteIndex = index;
	frmPaletteEditor->PalettePath = palette_path;

	if (frmPaletteEditor->ShowModal() == mrOk)
	{
		is_ok = true;
	}

	delete frmPaletteEditor;

	return is_ok;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

__fastcall TfrmPaletteEditor::TfrmPaletteEditor(TComponent* Owner)
	: TForm(Owner)
{
	for (int t = 0; t < GPaletteHandler->Palettes.size(); t++)
	{
		cbPalettes->Items->Add(GPaletteHandler->Palettes[t]->Description.c_str());

		GPaletteHandler->Palettes[t]->CopyToTemp();
	}

	for (int t = 0; t < 3; t++)
	{
		RGBGradients[t] = new TBitmap();
		RGBGradients[t]->PixelFormat = pf24bit;
		RGBGradients[t]->Width = 255;
		RGBGradients[t]->Height = 1;
	}

	BuildGuiForPalette();
}


void __fastcall TfrmPaletteEditor::FormDestroy(TObject *Sender)
{
    delete RGBGradients[2];
	delete RGBGradients[1];
	delete RGBGradients[0];
}


void __fastcall TfrmPaletteEditor::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}


void __fastcall TfrmPaletteEditor::FormShow(TObject *Sender)
{
	cbPalettes->ItemIndex = CurrentPaletteIndex;

	RenderGradient();

	sSingleColour->Brush->Color = TColor(GPaletteHandler->Palettes[CurrentPaletteIndex]->SingleColour.ToIntBGR());
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
		ColourUtility::HSVtoRGB(Fast::Floor(((double)i / 255) * 360), tbSaturation->Position, tbValue->Position, r, g, b);
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


void TfrmPaletteEditor::UpdateAllKeys()
{
	for (int k = 0; k < Shapes.size(); k++)
	{
		Shapes[k]->Left = GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[Shapes[k]->Tag].Position + __KeyOffset;

		Shapes[k]->Brush->Color = TColor(GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[k].Colour);
	}

   	iPointer->Left = Selected->Left;
}


// updates the key information (colours etc) for the object
// with the index key_index in the palettekeys array
void TfrmPaletteEditor::UpdateKeyDisplay(int key_index)
{
	KeyDisplayUpdating = true;

	PaletteKey &pk = GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[key_index];

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

        lLog->Caption = pk.SubMethod;
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

		PaletteKey &pk = GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[KeySelected];

		Selected->Brush->Color = TColor(tbRed->Position + (tbGreen->Position << 8) + (tbBlue->Position << 16));
		pk.Colour = Selected->Brush->Color;

		lHexRed->Caption = IntToHex(tbRed->Position, 2);
		lHexGreen->Caption = IntToHex(tbGreen->Position, 2);
		lHexBlue->Caption = IntToHex(tbBlue->Position, 2);

		lColourHex->Caption = ColourUtility::BGRtoRGBHex(pk.Colour);

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

		Selected->Brush->Color = TColor(colour);
		GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[KeySelected].Colour = colour;

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
	GPaletteHandler->Palettes[CurrentPaletteIndex]->Clear(true);

	ClearPalette(true);

	ResetUI();

	cbSteps->ItemIndex = 0;
	cbInterleve->Checked = false;
	rbInterleveX2->Checked = true;
    cbInterleveReverse->Checked = false;

	UpdateKeyDisplay(KeySelected);

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::sbAddNewKeyClick(TObject *Sender)
{
	int index = GPaletteHandler->Palettes[CurrentPaletteIndex]->AddNewKey(0xaaaaaa, 0, 200, false);

	AddShape(index);

	Selected = Shapes.back();
	KeySelected = index;

	iPointer->Left = Shapes.back()->Left;

    UpdateKeyDisplay(KeySelected);

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::sbDeleteSelectedKeyClick(TObject *Sender)
{
	if (KeySelected > 1)
	{
		int index = -1;

		for (int t = 0; t < Shapes.size(); t++)
		{
			if (Shapes[t]->Tag == KeySelected)
			{
				index = t;
				break;
			}
		}

		if (index != -1)
		{
			delete Shapes[index];
			Shapes.erase(Shapes.begin() + index);
		}

		GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.erase(GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.begin() + KeySelected);

		for (int t = 0; t < GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size(); t++)
		{
			Shapes[t]->Tag = t;
		}

		KeySelected = 0;
		Selected = Shapes[0];

        UpdateAllKeys();

		UpdateKeyDisplay(KeySelected);

		RenderGradient();
	}
}


void __fastcall TfrmPaletteEditor::sbAlignAllClick(TObject *Sender)
{
	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->Align())
	{
		UpdateAllKeys();

		RenderGradient();
    }
}


void __fastcall TfrmPaletteEditor::sbColourClick(TObject *Sender)
{
	GPaletteHandler->Palettes[CurrentPaletteIndex]->ColourSpace = sbColour->Down;

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::sbRandomFromClick(TObject *Sender)
{
	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size() != 0 && GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size() > 2)
	{
		int lastcolour = GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[0].Colour;

		for (int k = 2; k < GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size(); k++)
		{
			GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[k].Colour = ColourUtility::RandomBGRFromBGR(lastcolour);

			lastcolour = GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[k].Colour;
		}

		GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[1].Colour = ColourUtility::RandomBGRFromBGR(lastcolour);

		UpdateAllKeys();

		RenderGradient();
	}
}


void __fastcall TfrmPaletteEditor::sbRandomClick(TObject *Sender)
{
	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size() != 0)
	{
		for (int k = 0; k < GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size(); k++)
		{
			GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[k].Colour = ColourUtility::RandomBGR();
		}

		UpdateAllKeys();

		RenderGradient();
	}
}


void __fastcall TfrmPaletteEditor::sbReverseClick(TObject *Sender)
{
	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size() != 0)
	{
		std::swap(GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[0].Colour, GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[1].Colour);

		if (GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size() > 2)
		{
			for (int k = 2; k < GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size(); k++)
			{
				GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[k].Reverse();
			}
		}

		UpdateAllKeys();

		RenderGradient();
	}
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

        Selected = shape;

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

			sePosition->Value = shape->Left - __KeyOffset;

			GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[KeySelected].Position = shape->Left - __KeyOffset;

            RenderGradient();
        }
    }
}


void __fastcall TfrmPaletteEditor::shapeStartColourMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	KeyMoveMode = false;
}


void TfrmPaletteEditor::RenderGradient()
{
	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->IsRendering) return;

	GPaletteHandler->Palettes[CurrentPaletteIndex]->Render();

	// now copy the single row across the paintbox

	for (int t = 0; t < 25; t++)
	{
		pbGradient->Canvas->Draw(0, t, GPaletteHandler->Palettes[CurrentPaletteIndex]->Gradient);
	}
}


void __fastcall TfrmPaletteEditor::bAcceptClick(TObject *Sender)
{
	cbPalettesChange(NULL);

	for (int t = 0; t < GPaletteHandler->Palettes.size(); t++)
	{
		GPaletteHandler->Palettes[t]->SetFromTemp();

        GPaletteHandler->Palettes[t]->CopyPublic();
	}
}


void __fastcall TfrmPaletteEditor::bSaveClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(2, PalettePath);

	if (!file_name.empty())
	{
		if (file_name.find(L".palette") == std::wstring::npos)
		{
			file_name += L".palette";
		}

		SavePalette(file_name);
	}
}


void TfrmPaletteEditor::BuildGuiForPalette()
{
	bool ShowPaletteOptions = true;

	if (CurrentPaletteIndex == 0)
	{
		ShowPaletteOptions = false;
	}

	sbHorizontal->Enabled = ShowPaletteOptions;
	sbVertical->Enabled = ShowPaletteOptions;
	sSingleColour->Enabled = ShowPaletteOptions;
	cbGradient->Enabled = ShowPaletteOptions;

	cbInterleve->Enabled = ShowPaletteOptions;
	rbInterleveX2->Enabled = ShowPaletteOptions;
	rbInterleveX4->Enabled = ShowPaletteOptions;
	cbInterleveReverse->Enabled = ShowPaletteOptions;

	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->TempGradientDirection)
	{
		sbVertical->Down = true;
	}
	else
	{
		sbHorizontal->Down = true;
	}

	cbGradient->Checked = GPaletteHandler->Palettes[CurrentPaletteIndex]->TempIsGradient;
	sSingleColour->Brush->Color = TColor(GPaletteHandler->Palettes[CurrentPaletteIndex]->TempSingleColour.ToIntBGR());

	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->ColourSpace)
	{
		sbColour->Down = true;
	}
	else
	{
		sbBW->Down = true;
	}

	cbInterleve->Checked = GPaletteHandler->Palettes[CurrentPaletteIndex]->Interleve;
	cbInterleveReverse->Checked = GPaletteHandler->Palettes[CurrentPaletteIndex]->InterleveReverse;

	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->InterleveMode == 0)
	{
		rbInterleveX2->Checked = true;
	}
	else
	{
		rbInterleveX4->Checked = true;
	}

	for (int t = 0; t < cbSteps->Items->Count; t++)
	{
		if (cbSteps->Items->Strings[t] == IntToStr(GPaletteHandler->Palettes[CurrentPaletteIndex]->Steps))
		{
			cbSteps->ItemIndex = t;
			break;
        }
	}

	for (int t = 0; t < GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size(); t++)
	{
		AddShape(t);
	}

	KeySelected = 0;

	if (GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys.size() == 0)
		ShowMessage(L"help!!");

	Selected = Shapes[0];

	RenderGradient();

	UpdateKeyDisplay(KeySelected);
}


void __fastcall TfrmPaletteEditor::bLoadClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetOpenFileName(2, PalettePath);

	if (!file_name.empty())
	{
		if (file_name.find(L".palette") == std::wstring::npos)
		{
			file_name += L".palette";
		}

		ClearPalette(false);
		ResetUI();

		if (GPaletteHandler->Palettes[CurrentPaletteIndex]->Load(file_name))
		{
			BuildGuiForPalette();
        }
	}
}


void TfrmPaletteEditor::ClearPalette(bool autoadd)
{
	GPaletteHandler->Palettes[CurrentPaletteIndex]->Clear(autoadd);

	for (int t = Shapes.size() - 1; t >= 0; t--)
	{
		delete Shapes[t];

		Shapes.pop_back();
	}

    Shapes.clear();

	if (autoadd)
	{
		AddShape(0);
		AddShape(1);
    }

	Selected = Shapes[0];
}


void TfrmPaletteEditor::AddShape(int index)
{
	TShape *shape = new TShape(this);
	shape->Parent = gbColour;
	shape->Width = 10;
	shape->Height = 10;
	shape->Top = __KeyTop;
	shape->Left = GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[index].Position + __KeyOffset;
	shape->Brush->Color = TColor(GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[index].Colour);
	shape->Tag = index;
	shape->Shape = stSquare;
	shape->OnMouseDown = shapeStartColourMouseDown;
	shape->OnMouseUp = shapeStartColourMouseUp;

	if (index > 1)
	{
		shape->Shape = stCircle;
		shape->OnMouseMove = shapeStartColourMouseMove;
	}
	else
	{
		shape->Shape = stSquare;
	}

	Shapes.push_back(shape);
}


void TfrmPaletteEditor::ResetUI()
{
	KeyMoveMode = false;
	KeySelected = 0;
	iPointer->Left = __KeyOffset;
}


void TfrmPaletteEditor::SavePalette(std::wstring file_name)
{
	GPaletteHandler->Palettes[CurrentPaletteIndex]->Save(file_name);
}


void __fastcall TfrmPaletteEditor::sePositionChange(TObject *Sender)
{
	if (KeySelected != -1 && KeySelected >= 2)
	{
		GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[KeySelected].Position = sePosition->Value;

		Selected->Left = sePosition->Value + 20;
		iPointer->Left = sePosition->Value + 20;
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

	GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[KeySelected].Mode = sb->Tag;

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

	GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[KeySelected].Method = sb->Tag;

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::tbLogChange(TObject *Sender)
{
	lLog->Caption = tbLog->Position;

	GPaletteHandler->Palettes[CurrentPaletteIndex]->Keys[KeySelected].SubMethod = tbLog->Position;

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


void __fastcall TfrmPaletteEditor::cbStepsChange(TObject *Sender)
{
	GPaletteHandler->Palettes[CurrentPaletteIndex]->Steps = cbSteps->Text.ToInt();

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::cbInterleveClick(TObject *Sender)
{
	GPaletteHandler->Palettes[CurrentPaletteIndex]->Interleve = cbInterleve->Checked;

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::rbInterleveX2Click(TObject *Sender)
{
	if (rbInterleveX2->Checked)
	{
		GPaletteHandler->Palettes[CurrentPaletteIndex]->InterleveMode = 0;
	}
	else
	{
		GPaletteHandler->Palettes[CurrentPaletteIndex]->InterleveMode = 1;
	}

    RenderGradient();
}


void __fastcall TfrmPaletteEditor::cbInterleveReverseClick(TObject *Sender)
{
	GPaletteHandler->Palettes[CurrentPaletteIndex]->InterleveReverse = cbInterleveReverse->Checked;

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::cbPalettesChange(TObject *Sender)
{
	if (sbHorizontal->Down)
	{
		GPaletteHandler->Palettes[CurrentPaletteIndex]->TempGradientDirection = false;
	}
	else
	{
		GPaletteHandler->Palettes[CurrentPaletteIndex]->TempGradientDirection = true;
	}

	GPaletteHandler->Palettes[CurrentPaletteIndex]->TempIsGradient = cbGradient->Checked;
	GPaletteHandler->Palettes[CurrentPaletteIndex]->TempSingleColour = sSingleColour->Brush->Color;

	CurrentPaletteIndex = cbPalettes->ItemIndex;

	if (Sender != NULL)
	{
    	for (int t = Shapes.size() - 1; t >= 0; t--)
		{
			delete Shapes[t];

			Shapes.pop_back();
		}

		BuildGuiForPalette();

        iPointer->Left = Shapes.front()->Left;
    }
}


void __fastcall TfrmPaletteEditor::sSingleColourMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (frmColourDialog->ShowModal() == mrOk)
	{
		sSingleColour->Brush->Color = TColor(frmColourDialog->SelectedColour);

		sSingleColour->Hint = ColourUtility::BGRtoRGBHex(frmColourDialog->SelectedColour);
	}
}
