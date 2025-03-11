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

#include "FormColourDialog.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmColourDialog *frmColourDialog;


__fastcall TfrmColourDialog::TfrmColourDialog(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TfrmColourDialog::tbRedChange(TObject *Sender)
{
	if (!Changing)
	{
		SelectedColour = (tbBlue->Position << 16) + (tbGreen->Position << 8) + tbRed->Position;

		sShapeColour->Brush->Color = TColor(SelectedColour);
    }
}


void __fastcall TfrmColourDialog::FormShow(TObject *Sender)
{
	Changing = true;

	sShapeColour->Brush->Color = TColor(SelectedColour);

	tbBlue->Position = (SelectedColour & 0x00FF0000) >> 16;
	tbGreen->Position = (SelectedColour & 0x0000FF00) >> 8;
	tbRed->Position = (SelectedColour & 0x000000FF);

	Changing = false;
}
