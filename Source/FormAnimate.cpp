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

#include "FormAnimate.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmAnimate *frmAnimate;


__fastcall TfrmAnimate::TfrmAnimate(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TfrmAnimate::bOKClick(TObject *Sender)
{
	AnimationConfiguration.Configured = true;

	AnimationConfiguration.Steps = eSteps->Text.ToIntDef(10);

	AnimationConfiguration.DeltaA = eDeltaA->Text.ToDouble();
	AnimationConfiguration.DeltaB = eDeltaB->Text.ToDouble();
	AnimationConfiguration.DeltaC = eDeltaC->Text.ToDouble();

	AnimationConfiguration.Parameters = cbAnimateParameters->Checked;
	AnimationConfiguration.Zoom = cbAnimateZoom->Checked;

	AnimationConfiguration.Prefix = ePrefix->Text.c_str();
}


void __fastcall TfrmAnimate::FormShow(TObject *Sender)
{
	eSteps->Text = AnimationConfiguration.Steps;

	eDeltaA->Text = AnimationConfiguration.DeltaA;
	eDeltaB->Text = AnimationConfiguration.DeltaB;
	eDeltaC->Text = AnimationConfiguration.DeltaC;

	cbAnimateParameters->Checked = AnimationConfiguration.Parameters;
	cbAnimateZoom->Checked = AnimationConfiguration.Zoom;

	ePrefix->Text = AnimationConfiguration.Prefix.c_str();
}
