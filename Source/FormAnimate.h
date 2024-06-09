//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#ifndef FormAnimateH
#define FormAnimateH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "Animation.h"
//---------------------------------------------------------------------------
class TfrmAnimate : public TForm
{
__published:	// IDE-managed Components
	TEdit *eDeltaA;
	TLabel *lVariableA;
	TEdit *eDeltaB;
	TLabel *lVariableB;
	TEdit *eDeltaC;
	TLabel *lVariableC;
	TLabel *Label1;
	TEdit *eSteps;
	TBitBtn *bOK;
	TBitBtn *bCancel;
	TBevel *Bevel1;
	TLabel *Label2;
	TEdit *ePrefix;
	TLabel *Label3;
	TCheckBox *cbAnimateParameters;
	TCheckBox *cbAnimateZoom;
	TLabel *Label4;
	TEdit *eDeltaD;
	TLabel *lWarning;
	TCheckBox *cbIncludeA;
	TCheckBox *cbIncludeB;
	TCheckBox *cbIncludeC;
	TCheckBox *cbIncludeD;
	void __fastcall bOKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall eDeltaAChange(TObject *Sender);
private:

	double ToDouble(const std::wstring, double);

public:

	Animation AnimationConfiguration;

	__fastcall TfrmAnimate(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAnimate *frmAnimate;
//---------------------------------------------------------------------------
#endif
