//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmText *frmText;

//---------------------------------------------------------------------------

ImageDescription OpenTextDialog(ImageDescription *old)
{
	TfrmText *frmOpenTextDialog = new TfrmText(Application);

	ImageDescription newid(L"");

	frmOpenTextDialog->BuildFrom(old);

	if (frmOpenTextDialog->ShowModal() == mrOk)
	{
		newid.Valid = true;

		newid.Active = frmOpenTextDialog->cbEnable->Checked;

		newid.FontName = frmOpenTextDialog->lFontName->Caption.c_str();
		newid.FontSize = frmOpenTextDialog->lFontSize->Caption.ToInt();

		newid.PositionY = frmOpenTextDialog->eYOffset->Text.ToInt();
	}

	delete frmOpenTextDialog;

	return newid;
}

//---------------------------------------------------------------------------

__fastcall TfrmText::TfrmText(TComponent* Owner)
	: TForm(Owner)
{
}


void TfrmText::BuildFrom(ImageDescription *old)
{
    cbEnable->Checked = old->Active;

	lFontName->Caption = old->FontName.c_str();
	lFontSize->Caption = old->FontSize;

    eYOffset->Text = old->PositionY;
}


void __fastcall TfrmText::BitBtn1Click(TObject *Sender)
{
	if (fdText->Execute())
	{
		lFontName->Caption = fdText->Font->Name;
		lFontSize->Caption = fdText->Font->Size;
	}
}
