//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#ifndef FormTextH
#define FormTextH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>

#include "ImageDescription.h"

class TfrmText : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *cbEnable;
	TBitBtn *BitBtn1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *lFontName;
	TLabel *lFontSize;
	TBitBtn *bCancel;
	TBitBtn *bOK;
	TFontDialog *fdText;
	TEdit *eYOffset;
	TLabel *Label3;
	void __fastcall BitBtn1Click(TObject *Sender);
private:


public:
	__fastcall TfrmText(TComponent* Owner);

	void BuildFrom(ImageDescription*);
};
//---------------------------------------------------------------------------

ImageDescription OpenTextDialog(ImageDescription *);

//---------------------------------------------------------------------------
extern PACKAGE TfrmText *frmText;
//---------------------------------------------------------------------------
#endif
