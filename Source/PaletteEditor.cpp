//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
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
#include "PaletteHandler.h"
#include "Utility.h"

extern PaletteHandler *GPaletteHandler;

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPaletteEditor *frmPaletteEditor;


__fastcall TfrmPaletteEditor::TfrmPaletteEditor(TComponent* Owner)
	: TForm(Owner)
{
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
	RenderGradient();

	sInfinity->Brush->Color = TColor(GPaletteHandler->Palette[__PaletteInfinity]);
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


void TfrmPaletteEditor::UpdateAllKeys()
{
	for (int t = 0; t < Shapes.size(); t++)
	{
        Shapes[t]->Left = GPaletteHandler->Keys[Shapes[t]->Tag].Position + __KeyOffset;
	}

   	iPointer->Left = Selected->Left;
}


// updates the key information (colours etc) for the object
// with the index key_index in the palettekeys array
void TfrmPaletteEditor::UpdateKeyDisplay(int key_index)
{
	KeyDisplayUpdating = true;

	PaletteKey &pk = GPaletteHandler->Keys[key_index];

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

		PaletteKey &pk = GPaletteHandler->Keys[KeySelected];

		Selected->Brush->Color = TColor(tbRed->Position + (tbGreen->Position << 8) + (tbBlue->Position << 16));
		pk.Colour = Selected->Brush->Color;

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

		Selected->Brush->Color = TColor(colour);
		GPaletteHandler->Keys[KeySelected].Colour = colour;

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
	GPaletteHandler->Clear(true);

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
	int index = GPaletteHandler->AddNewKey(0xaaaaaa, 0, 200, false);

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

		GPaletteHandler->Keys.erase(GPaletteHandler->Keys.begin() + KeySelected);

		for (int t = 0; t < GPaletteHandler->Keys.size(); t++)
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
	if (GPaletteHandler->Align())
	{
		UpdateAllKeys();

		RenderGradient();
    }
}


void __fastcall TfrmPaletteEditor::sbColourClick(TObject *Sender)
{
	GPaletteHandler->ColourSpace = sbColour->Down;

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

			GPaletteHandler->Keys[KeySelected].Position = shape->Left - __KeyOffset;

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
	if (GPaletteHandler->IsRendering) return;

	GPaletteHandler->Render();

	// now copy the single row across the paintbox

	for (int t = 0; t < 25; t++)
	{
		pbGradient->Canvas->Draw(0, t, GPaletteHandler->Gradient);
	}
}


void __fastcall TfrmPaletteEditor::bAcceptClick(TObject *Sender)
{
	GPaletteHandler->CopyPublic();
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
	if (GPaletteHandler->ColourSpace)
	{
		sbColour->Down = true;
	}
	else
	{
		sbBW->Down = true;
	}

	cbInterleve->Checked = GPaletteHandler->Interleve;
	cbInterleveReverse->Checked = GPaletteHandler->InterleveReverse;

	if (GPaletteHandler->InterleveMode == 0)
	{
		rbInterleveX2->Checked = true;
	}
	else
	{
		rbInterleveX4->Checked = true;
	}

	for (int t = 0; t < cbSteps->Items->Count; t++)
	{
		if (cbSteps->Items->Strings[t] == IntToStr(GPaletteHandler->Steps))
		{
			cbSteps->ItemIndex = t;
			break;
        }
	}

	for (int t = 0; t < GPaletteHandler->Keys.size(); t++)
	{
		AddShape(t);
	}

	KeySelected = 0;

	if (GPaletteHandler->Keys.size() == 0)
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

		if (GPaletteHandler->Load(file_name))
		{
			BuildGuiForPalette();
        }
	}
}


void TfrmPaletteEditor::ClearPalette(bool autoadd)
{
	GPaletteHandler->Clear(autoadd);

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
	shape->Left = GPaletteHandler->Keys[index].Position + __KeyOffset;
	shape->Brush->Color = TColor(GPaletteHandler->Keys[index].Colour);
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
	GPaletteHandler->Save(file_name);
}


void __fastcall TfrmPaletteEditor::sePositionChange(TObject *Sender)
{
	if (KeySelected != -1 && KeySelected >= 2)
	{
		GPaletteHandler->Keys[KeySelected].Position = sePosition->Value;

		Selected->Left = sePosition->Value + 20;
		iPointer->Left = sePosition->Value + 20;
	}
}


void __fastcall TfrmPaletteEditor::sInfinityMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (frmColourDialog->ShowModal() == mrOk)
	{
		sInfinity->Brush->Color = TColor(frmColourDialog->SelectedColour);

		lInfinityHex->Caption = ColourUtility::BRGtoRGBHex(frmColourDialog->SelectedColour);

		GPaletteHandler->Palette[__PaletteInfinity] = frmColourDialog->SelectedColour;
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

	GPaletteHandler->Keys[KeySelected].Mode = sb->Tag;

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

	GPaletteHandler->Keys[KeySelected].Method = sb->Tag;

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
    GPaletteHandler->Steps = cbSteps->Text.ToInt();

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::cbInterleveClick(TObject *Sender)
{
	GPaletteHandler->Interleve = cbInterleve->Checked;

	RenderGradient();
}


void __fastcall TfrmPaletteEditor::rbInterleveX2Click(TObject *Sender)
{
	if (rbInterleveX2->Checked)
	{
		GPaletteHandler->InterleveMode = 0;
	}
	else
	{
		GPaletteHandler->InterleveMode = 1;
	}

    RenderGradient();
}


void __fastcall TfrmPaletteEditor::cbInterleveReverseClick(TObject *Sender)
{
	GPaletteHandler->InterleveReverse = cbInterleveReverse->Checked;

	RenderGradient();
}
