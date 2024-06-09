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
	double a = ToDouble(eDeltaA->Text.c_str(), 0);
	double b = ToDouble(eDeltaB->Text.c_str(), 0);
	double c = ToDouble(eDeltaC->Text.c_str(), 0);
	double d = ToDouble(eDeltaD->Text.c_str(), 0);

	int steps = eSteps->Text.ToIntDef(0);

	AnimationConfiguration.Prefix = ePrefix->Text.c_str();

	if (cbAnimateParameters->Checked)
	{
		if (!(a == 0 && b == 0 && c == 0 && d == 0 && steps == 0))
		{
			AnimationConfiguration.Configured = true;

			AnimationConfiguration.Steps = steps;

			AnimationConfiguration.DeltaA = a;
			AnimationConfiguration.DeltaB = b;
			AnimationConfiguration.DeltaC = c;
			AnimationConfiguration.DeltaD = d;

			AnimationConfiguration.IncludeA = cbIncludeA->Checked;
			AnimationConfiguration.IncludeB = cbIncludeB->Checked;
			AnimationConfiguration.IncludeC = cbIncludeC->Checked;
			AnimationConfiguration.IncludeD = cbIncludeD->Checked;

			AnimationConfiguration.Parameters = cbAnimateParameters->Checked;
			AnimationConfiguration.Zoom = cbAnimateZoom->Checked;

			ModalResult = mrOk;

			return;
		}

		if (cbAnimateZoom->Checked)
		{
			return;
        }
	}

	if (cbAnimateZoom->Checked)
	{
		if (steps != 0)
		{
			AnimationConfiguration.Steps = steps;
			AnimationConfiguration.Zoom = cbAnimateZoom->Checked;

			ModalResult = mrOk;

			return;
        }
	}

	lWarning->Visible = true;
}


void __fastcall TfrmAnimate::FormShow(TObject *Sender)
{
	eSteps->Text = AnimationConfiguration.Steps;

	eDeltaA->Text = AnimationConfiguration.DeltaA;
	eDeltaB->Text = AnimationConfiguration.DeltaB;
	eDeltaC->Text = AnimationConfiguration.DeltaC;
	eDeltaD->Text = AnimationConfiguration.DeltaD;

	cbIncludeA->Checked = AnimationConfiguration.IncludeA;
	cbIncludeB->Checked = AnimationConfiguration.IncludeB;
	cbIncludeC->Checked = AnimationConfiguration.IncludeC;
	cbIncludeD->Checked = AnimationConfiguration.IncludeD;

	cbAnimateParameters->Checked = AnimationConfiguration.Parameters;
	cbAnimateZoom->Checked = AnimationConfiguration.Zoom;

	ePrefix->Text = AnimationConfiguration.Prefix.c_str();

    lWarning->Visible = false;
}


void __fastcall TfrmAnimate::eDeltaAChange(TObject *Sender)
{
	cbAnimateParameters->Checked = !(eDeltaA->Text != L"0" && eDeltaB->Text != L"0" &&
									 eDeltaC->Text != L"0" && eDeltaD->Text != L"0");
}


double TfrmAnimate::ToDouble(const std::wstring s, double def)
{
	try
	{
		double d = stod(s);

		return d;
	}
	catch(...)
	{
	}

	return def;
}
