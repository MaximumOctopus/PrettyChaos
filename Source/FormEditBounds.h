//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#ifndef FormEditBoundsH
#define FormEditBoundsH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>

class TfrmEditBounds : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *bOK;
	TBitBtn *bCancel;
	TBevel *Bevel1;
	TLabel *Label5;
	TLabel *Label1;
	TLabel *Label6;
	TLabel *Label2;
	TLabel *Label7;
	TLabel *Label3;
	TLabel *Label8;
	TLabel *Label4;
	TEdit *eXMin;
	TEdit *eXMax;
	TEdit *eYMin;
	TEdit *eYMax;
	TRadioButton *rbNoFitting;
	TRadioButton *rbAutoFitting;
	void __fastcall bOKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmEditBounds(TComponent* Owner);

	double xmin = 0;
	double xmax = 0;
	double ymin = 0;
	double ymax = 0;

	int fwidth = 0;
    int fheight = 0;

	void SetBoundsValues(int, int, double, double, double, double);
};

extern PACKAGE TfrmEditBounds *frmEditBounds;

#endif
