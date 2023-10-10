//---------------------------------------------------------------------------

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
	void __fastcall bOKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations

	Animation AnimationConfiguration;

	__fastcall TfrmAnimate(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAnimate *frmAnimate;
//---------------------------------------------------------------------------
#endif
