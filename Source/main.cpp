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
#include <Vcl.Imaging.pngimage.hpp>
#pragma hdrstop

#include <Clipbrd.hpp>

#include "main.h"

#include "FormAbout.h"
#include "FormAnimate.h"
#include "FormColourDialog.h"
#include "FormEditBounds.h"
#include "FormText.h"
#include "PaletteEditor.h"
#include "PaletteHandler.h"

#include "ColourUtility.h"
#include "Constants.h"
#include "Mandelbrot.h"
#include "MartinClassic.h"
#include "Utility.h"

extern PaletteHandler *GPaletteHandler;

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;


__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	std::wstring title = L"PrettyChaos " + __PrettyChaosVersion;

	PalettePath = ExtractFilePath(Application->ExeName) + L"Palettes\\";
	ProjectPath = ExtractFilePath(Application->ExeName) + L"Projects\\";
	RenderPath = ExtractFilePath(Application->ExeName) + L"Renders\\";

	Caption = title.c_str();

	PaletteBitmap = new Graphics::TBitmap;
	PaletteBitmap->PixelFormat = pf24bit;
	PaletteBitmap->Width = 125;
	PaletteBitmap->Height = 1;

	GPaletteHandler = new PaletteHandler();

	GFractalHandler = new FractalHandler();

	imagedescription = new ImageDescription(ExtractFilePath(Application->ExeName).c_str());
    imagedescription->Load();

	for (int t = 0; t < GFractalHandler->Fractals.size(); t++)
	{
		cbFractalSelector->Items->Add(GFractalHandler->Fractals[t]->Name.c_str());
	}

    cbFractalSelector->ItemIndex = 0;

	history = new HistoryHandler();
    projectio = new ProjectIO();

	history->AddZoom(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin, GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax,
					 GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin, GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax);

	System::WideChar k = VK_RETURN;

	cbFractalSelectorChange(nullptr);

	eWidthExit(nullptr);

	UpdatePalette();
}


void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	imagedescription->Save();
}


void __fastcall TfrmMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_UP || Key == VK_DOWN || Key == VK_LEFT || Key == VK_RIGHT)
	{
		double delta = 0.1;

		switch (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->QuickParamterMode)
		{
		case __QPMNone:
			break;
		case __QPMABPlusFine:
			if (Key == VK_LEFT || Key == VK_RIGHT)
			{
				delta = QPFine;
			}

			break;
		case __QPMABC:
			delta = 1;

			if (Key == VK_LEFT || Key == VK_RIGHT)
			{
				delta = 0.1;
			}
			break;
		}

		if (Shift.Contains(ssShift))
		{
			double a = eVarA->Text.ToDouble();

			if (Key == VK_UP || Key == VK_LEFT)
			{
				a += delta;
			}
			else if (Key == VK_DOWN || Key == VK_RIGHT)
			{
				a -= delta;
			}

			eVarA->Text = a;
		}
		else if (Shift.Contains(ssCtrl))
		{
			double b = eVarB->Text.ToDouble();

			if (Key == VK_UP || Key == VK_LEFT)
			{
				b += delta;
			}
			else if (Key == VK_DOWN || Key == VK_RIGHT)
			{
				b -= delta;
			}

			eVarB->Text = b;
		}
		else if (Shift.Contains(ssAlt))
		{
			double c = eVarC->Text.ToDouble();

			if (Key == VK_UP || Key == VK_LEFT)
			{
				c += delta;
			}
			else if (Key == VK_DOWN || Key == VK_RIGHT)
			{
				c -= delta;
			}

			eVarC->Text = c;
		}

		if (miShowPreview->Checked)
		{
			RenderPreview();
		}
		else
		{
			sbRenderClick(nullptr);
        }
	}
}


void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	delete GPaletteHandler;
	delete GFractalHandler;
	delete history;
	delete projectio;
	delete imagedescription;
}


void TfrmMain::UpdateFromFractalChange()
{
	UpdateAllParameters();

	cbRenderMode->Clear();

	for (int t = 0; t < GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderModes.size(); t++)
	{
		cbRenderMode->Items->Add(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderModes[t].c_str());
	}

	cbRenderMode->ItemIndex = 0;

    cbRenderModeChange(nullptr);
}


void TfrmMain::SetFromProjectFile(PCProject &project, Animation &animation)
{
	for (int t = 0; t < cbFractalSelector->Items->Count; t++)
	{
		if (cbFractalSelector->Items->Strings[t] == project.Name.c_str())
		{
			cbFractalSelector->ItemIndex = t;
			cbFractalSelectorChange(nullptr);
		}
	}

	eWidth->Text = project.Width;
	eHeight->Text = project.Height;

	UpdateDimension(true);

	// =========================================================================

	cbRenderMode->ItemIndex = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderMode;
	cbRenderModeChange(nullptr);

	// =========================================================================

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetRenderMode(project.RenderMode);
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff = project.nCoeff;

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations = project.MaxIterations;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->bailout_radius = project.BailoutRadius;

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin = project.xmin;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax = project.xmax;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin = project.ymin;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax = project.ymax;

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.a = project.var_a;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.b = project.var_b;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.c = project.var_c;

	// =========================================================================

	miSuperSample->Checked = project.SuperSampling;

	// =========================================================================

	eCoeffN->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff);
	eIterations->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations);
	eWidth->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width);
	eHeight->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height);

	eVarA->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.a);
	eVarB->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.b);
	eVarC->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.c);
	eVarD->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.d);

	// =========================================================================

	if (animation.Configured)
	{
		AnimationConfiguration.Configured = true;

		AnimationConfiguration.Steps = animation.Steps;

		AnimationConfiguration.DeltaA = animation.DeltaA;
		AnimationConfiguration.DeltaB = animation.DeltaB;
		AnimationConfiguration.DeltaC = animation.DeltaC;
		AnimationConfiguration.DeltaD = animation.DeltaD;

		AnimationConfiguration.IncludeA = animation.IncludeA;
		AnimationConfiguration.IncludeB = animation.IncludeB;
		AnimationConfiguration.IncludeC = animation.IncludeC;
		AnimationConfiguration.IncludeD = animation.IncludeD;

		AnimationConfiguration.Parameters = animation.Parameters;
		AnimationConfiguration.Zoom = animation.Zoom;

		AnimationConfiguration.Prefix = animation.Prefix;
	}

	sbReZoom->Enabled = animation.Configured;

	// =========================================================================

	if (!project.PaletteFileName.empty())
	{
		std::wstring path = ExtractFilePath(Application->ExeName).c_str();

		path += L"Palettes\\" + project.PaletteFileName;

		if (FileExists(path.c_str()))
		{
	        GPaletteHandler->Clear(false);

			if (!LoadAndSetPalette(path))
			{
				std::wstring error = L"Error loading palette \"" + project.PaletteFileName + L"\" :( Using default.";

				sbMain->SimpleText = error.c_str();
			}
		}
		else
		{
			std::wstring error = L"Unable to load palette \"" + project.PaletteFileName + L"\" :(";

			sbMain->SimpleText = error.c_str();
		}
	}

	// =========================================================================

	UpdateFractalPanel();
}


PCProject TfrmMain::GetProjectSettings()
{
	PCProject project;

	project.Name = cbFractalSelector->Text.c_str();

	project.Width = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width;
	project.Height = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height;

	project.RenderMode = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderMode;
	project.nCoeff = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff;

	project.MaxIterations = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations;
	project.BailoutRadius = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->bailout_radius;

	project.xmin = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin;
	project.xmax = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax;
	project.ymin = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin;
	project.ymax = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax;

	project.var_a = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.a;
	project.var_b = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.b;
	project.var_c = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.c;
	project.var_d = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.d;

	return project;
}


void TfrmMain::UpdateAllParameters()
{
	eCoeffN->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff);
	eIterations->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations);
	eBailoutRadius->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->bailout_radius);

	eWidth->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width;
	eHeight->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height;

	if (gbVarABC->Visible)
	{
		eVarA->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.a);
		eVarB->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.b);
		eVarC->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.c);
		eVarD->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.d);
	}
}


void TfrmMain::UpdateFractalPanel()
{
	lXMin->Caption = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin);
	lXMax->Caption = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax);
	lYMin->Caption = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin);
	lYMax->Caption = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax);

	//Caption = (fractal->xmax - fractal->xmin) / (fractal->ymax - fractal->ymin); ratio
}


void TfrmMain::UpdateDimension(bool force)
{
	int Width = eWidth->Text.ToIntDef(-1);
	int Height = eHeight->Text.ToIntDef(-1);

	if (Width > 0 && Height > 0)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetDimensions(force, Width, Height);

		iRender->Width = Width;
		iRender->Height = Height;

		iPreview->Width = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->PreviewWidth;
		iPreview->Height = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->PreviewHeight;

		UpdateFractalPanel();

		if (miShowPreview->Checked && !IsBusy) RenderPreview();
	}
}


void TfrmMain::UpdateABCPanel()
{
	gbVarABC->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ShowABC(cbRenderMode->ItemIndex);

	if (gbVarABC->Visible)
	{
		lVarB->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarB;
		eVarB->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarB;
		lVarC->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarC;
		eVarC->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarC;
		lVarD->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarD;
		eVarD->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarD;

		lVarA->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->NameA.c_str();
		lVarB->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->NameB.c_str();
		lVarC->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->NameC.c_str();
		lVarD->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->NameD.c_str();
	}
}


void TfrmMain::UpdateZoomPanel()
{
	history->Zoom.clear();

	sbReset->Enabled = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsZoom;
	sbZoomOnPoint->Enabled = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsZoom;
	sbZoom->Enabled = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsZoom;
	sbZoomCrop->Enabled = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsZoom;
	sbBack->Enabled = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsZoom;
	sbForward->Enabled = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsZoom;
}


void __fastcall TfrmMain::sbRenderClick(TObject *Sender)
{
	bool rendered = true;

	auto StartTime = std::chrono::system_clock::now();

	sbMain->SimpleText = "Rendering...";

	if (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsABC)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetABC(eVarA->Text.ToDouble(),
																		eVarB->Text.ToDouble(),
																		eVarC->Text.ToDouble(),
																		eVarD->Text.ToDouble());
	}

	eCoeffNExit(eCoeffN);

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetDimensions(false, iRender->Width, iRender->Height);

	if (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->MultiThread)
	{
		rendered = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->MultiThreadRender(false, miSuperSample->Checked);

		SetWarning(!rendered);
	}
	else
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Render(0, 0);
	}

	if (rendered)
	{
		CopyFromFractalToScreen();

		if (imagedescription->Active)
		{
			RenderTextToScreen();
        }

		if (miSaveAllImages->Checked)
		{
			std::wstring file_name = Utility::ProcessFileName(__AutoSaveTemplate);

			SaveFractal(file_name);
		}

		std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = EndTime - StartTime;

		std::wstring c = L"Rendered in " + GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderTime + L" seconds (" + std::to_wstring(elapsed_seconds.count()) + L" seconds)";

		sbMain->SimpleText = c.c_str();
	}
	else
	{
		sbMain->SimpleText = "Invalid real and imaginary points.";
	}
}


void TfrmMain::RenderPreview()
{
    if (IsBusy) return;

	bool rendered = true;

	if (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsABC)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetABC(eVarA->Text.ToDouble(),
																		eVarB->Text.ToDouble(),
																		eVarC->Text.ToDouble(),
																		eVarD->Text.ToDouble());
	}

	eCoeffNExit(nullptr);

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetDimensions(false, iRender->Width, iRender->Height);

	if (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->MultiThread)
	{
		rendered = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->MultiThreadRender(true, false);

		SetWarning(!rendered);
	}
	else
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->PreRender(true);
	}

	if (rendered)
	{
		CopyFromFractalToPreview();
	}
	else
	{
		sbMain->SimpleText = "Invalid real and imaginary points.";
	}
}


void __fastcall TfrmMain::eAnimationClick(TObject *Sender)
{
	for (int i = 0; i < AnimationConfiguration.Steps; i++)
	{
		sbRenderClick(nullptr);

		double a = eVarA->Text.ToDouble();
		double b = eVarB->Text.ToDouble();
		double c = eVarC->Text.ToDouble();
		double d = eVarD->Text.ToDouble();

		std::wstring path = ExtractFilePath(Application->ExeName).c_str();

		std::wstring file_name = path + L"Animation\\" + AnimationConfiguration.Prefix + std::to_wstring(i + 1) + AnimationConfiguration.ParametersForFile(a, b, c, d) + L".png";

		SaveFractal(Utility::ProcessFileName(file_name));

		if (AnimationConfiguration.Parameters)
		{
			a += AnimationConfiguration.DeltaA;
			eVarA->Text = a;

			if (eVarB->Visible)
			{
				b += AnimationConfiguration.DeltaB;
				eVarB->Text = b;
			}

			if (eVarC->Visible)
			{
				c += AnimationConfiguration.DeltaC;
				eVarC->Text = c;
			}

			if (eVarD->Visible)
			{
				d += AnimationConfiguration.DeltaD;
				eVarD->Text = d;
			}
		}

		if (AnimationConfiguration.Zoom)
		{
			if (sbReZoom->Enabled)
			{
				sbReZoomClick(nullptr);
			}
		}
	}
}


void __fastcall TfrmMain::miShowPreviewClick(TObject *Sender)
{
	if (miShowPreview->Checked)
	{
		if (miShowPreview->Checked && !IsBusy) RenderPreview();
	}
}


void __fastcall TfrmMain::bOpenProjectClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetOpenFileName(0, ProjectPath);

	if (!file_name.empty())
	{
		IsBusy = true;

		if (file_name.find(L".prttychs") == std::wstring::npos)
		{
			file_name += L".prttychs";
		}

		PCProject project;
		Animation animation;

		projectio->Load(file_name, project, animation);

		SetFromProjectFile(project, animation);

		ProjectPath = ExtractFilePath(file_name.c_str());

		IsBusy = false;

		if (miShowPreview->Checked) RenderPreview();
	}
}


void __fastcall TfrmMain::bSaveProjectClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(0, ProjectPath);

	if (!file_name.empty())
	{
		if (file_name.find(L".prttychs") == std::wstring::npos)
		{
			file_name += L".prttychs";
		}

		PCProject project = GetProjectSettings();

		projectio->Save(file_name, project, AnimationConfiguration);

		ProjectPath = ExtractFilePath(file_name.c_str());
	}
}


void __fastcall TfrmMain::miSaveFractalParametersClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(3, ProjectPath);

	if (!file_name.empty())
	{
		if (file_name.find(L".txt") == std::wstring::npos)
		{
			file_name += L".txt";
		}

		SaveFractalParameters(file_name);
	}
}


void TfrmMain::RenderTextToScreen()
{
	int y = 10;

	if (imagedescription->Location == 0)
	{
		y = iRender->Height - imagedescription->PositionY - iRender->Canvas->TextHeight(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Description().c_str());
	}

	iRender->Canvas->Brush->Style = bsClear;
	iRender->Canvas->Font->Name = imagedescription->FontName.c_str();
    iRender->Canvas->Font->Size = imagedescription->FontSize;
	iRender->Canvas->Font->Color = TColor(0x00ffffff);
	iRender->Canvas->TextOut(imagedescription->PositionX, y, GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Description().c_str());
}


void TfrmMain::CopyFromFractalToScreen()
{
	iRender->Picture->Assign(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderCanvas);

	sbSwapImage->Tag = 0;
}


void TfrmMain::CopyFromFractalToPreview()
{
	iPreview->Picture->Assign(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderCanvas);
}


void TfrmMain::CopyFromBackupToScreen()
{
	iRender->Picture->Assign(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->CopyCanvas);

	sbSwapImage->Tag = 1;
}


void __fastcall TfrmMain::sbSaveImageClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(1, RenderPath);

	if (!file_name.empty())
	{
		if (file_name.find(L".png") == std::wstring::npos)
		{
			file_name += L".png";
		}

		SaveFractal(file_name);

		RenderPath = ExtractFilePath(file_name.c_str());
	}
}


void TfrmMain::SaveFractal(const std::wstring file_name)
{
	TPngImage* png  = new TPngImage();
	png->Assign(iRender->Picture->Bitmap);

	png->SaveToFile(file_name.c_str());

	if (miSaveParameters->Checked)
	{
		std::wstring pfn = file_name;

		auto index = pfn.find(L".png", 0);

		if (index != std::wstring::npos)
		{
			pfn.replace(index, 4, L".txt");

			SaveFractalParameters(pfn);
		}
	}

	delete png;
}


void TfrmMain::SaveFractalParameters(const std::wstring file_name)
{
	std::ofstream file(file_name);

	if (file)
	{
		file << Formatting::to_utf8(L"Project\n");
		file << Formatting::to_utf8(L"    Application    : " + __PrettyChaosVersion + L"\n");
		file << Formatting::to_utf8(L"    Super-sampling : " + std::to_wstring(miSuperSample->Checked) + L"\n");
		file << Formatting::to_utf8(L"\n\n");

		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ToFile(file);

		file.close();
	}
}


void __fastcall TfrmMain::iRenderMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if (Shift.Contains(ssRight) && miRMBSetParameters->Checked)
	{
		double x = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin + (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->x_resolution * X);
		double y = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin + (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->y_resolution * Y);

		eVarA->Text = x;
        eVarB->Text = y;
	}
	else
	{
		switch (ZoomMode)
		{
		case 0:
		{
			if (FirstPoint)
			{
				FirstPoint = false;

				ZPoint1x = X;
				ZPoint1y = Y;
			}
			else
			{
				ZoomMode = -1;

				ZPoint2x = X;
				ZPoint2y = Y;

				if (ZPoint2x < ZPoint1x) std::swap(ZPoint1x, ZPoint2x);
				if (ZPoint2y < ZPoint1y) std::swap(ZPoint1y, ZPoint2y);

				Fractal* &fractal = GFractalHandler->Fractals[cbFractalSelector->ItemIndex];

				double xmin = fractal->xmin + (((fractal->xmax - fractal->xmin) / fractal->Width) * (double)ZPoint1x);
				double xmax = fractal->xmin + (((fractal->xmax - fractal->xmin) / fractal->Width) * (double)ZPoint2x);

				double ymin = fractal->ymin + (((fractal->ymax - fractal->ymin) / fractal->Height) * (double)ZPoint1y);
				double ymax = fractal->ymin + (((fractal->ymax - fractal->ymin) / fractal->Height) * (double)ZPoint2y);

				fractal->FitToView(xmin, xmax, ymin, ymax);

				history->AddZoom(fractal->xmin, fractal->xmax, fractal->ymin, fractal->ymax);

				UpdateFractalPanel();

				iRender->Cursor = crDefault;
			}
			break;
		}
		case 1:
		{
			if (FirstPoint)
			{
				FirstPoint = false;
				ZoomMode = -1;

				sbReZoom->Enabled = true;

                Fractal* &fractal = GFractalHandler->Fractals[cbFractalSelector->ItemIndex];

				double xmin = fractal->xmin + (((fractal->xmax - fractal->xmin) / fractal->Width) * (double)X);
				double ymin = fractal->ymin + (((fractal->ymax - fractal->ymin) / fractal->Height) * (double)Y);

				ZoomPointClick(xmin, ymin);

				iRender->Cursor = crDefault;
			}
			break;
		}
		case 2:
		{
			if (FirstPoint)
			{
				FirstPoint = false;
				ZoomMode = -1;

				Fractal* &fractal = GFractalHandler->Fractals[cbFractalSelector->ItemIndex];

				double xmin = fractal->xmin + (((fractal->xmax - fractal->xmin) / fractal->Width) * (double)X);
				double ymin = fractal->ymin + (((fractal->ymax - fractal->ymin) / fractal->Height) * (double)Y);

				fractal->CentreOnPoint(xmin, ymin);

               	UpdateFractalPanel();

				iRender->Cursor = crDefault;
			}
			break;
		}
		}
	}

	if (miShowPreview->Checked && !IsBusy) RenderPreview();
}


void TfrmMain::ZoomPointClick(double X, double Y)
{
	Fractal* &fractal = GFractalHandler->Fractals[cbFractalSelector->ItemIndex];

	LastZoomX = X;
	LastZoomY = Y;

	fractal->ZoomAtPoint(LastZoomX, LastZoomY);

	history->AddZoom(fractal->xmin, fractal->xmax, fractal->ymin, fractal->ymax);

	UpdateFractalPanel();
}


void TfrmMain::ZoomOut()
{
	Fractal* &fractal = GFractalHandler->Fractals[cbFractalSelector->ItemIndex];

	fractal->ZoomOut();

	UpdateFractalPanel();
}


void __fastcall TfrmMain::miConfigAnimationClick(TObject *Sender)
{
	if (frmAnimate->ShowModal() == mrOk)
	{
		AnimationConfiguration = frmAnimate->AnimationConfiguration;

        eAnimation->Enabled = true;
    }
}


void __fastcall TfrmMain::sbResetClick(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ResetView();

	UpdateDimension(true);

	UpdateFractalPanel();
}


void __fastcall TfrmMain::sbZoomOnPointClick(TObject *Sender)
{
	if (ZoomMode != -1)
	{
		ZoomMode = -1;

		iRender->Cursor = crDefault;
	}
	else
	{
		ZoomMode = 2;
		FirstPoint = true;

		iRender->Cursor = crCross;
	}
}


void __fastcall TfrmMain::sbZoomCentreClick(TObject *Sender)
{
	sbReZoom->Enabled = true;

	Fractal* &fractal = GFractalHandler->Fractals[cbFractalSelector->ItemIndex];

	double x = iRender->Width / 2;
	double y = iRender->Height / 2;

	double xmin = fractal->xmin + (((fractal->xmax - fractal->xmin) / fractal->Width) * x);
	double ymin = fractal->ymin + (((fractal->ymax - fractal->ymin) / fractal->Height) * y);

	ZoomPointClick(xmin, ymin);

	if (miShowPreview->Checked && !IsBusy) RenderPreview();
}


void __fastcall TfrmMain::sbZoomClick(TObject *Sender)
{
	if (ZoomMode != -1)
	{
		ZoomMode = -1;

		iRender->Cursor = crDefault;
	}
	else
	{
		ZoomMode = 1;
		FirstPoint = true;

		iRender->Cursor = crCross;
	}
}


void __fastcall TfrmMain::sbZoomOutClick(TObject *Sender)
{
	ZoomOut();

	if (miShowPreview->Checked && !IsBusy) RenderPreview();
}


void __fastcall TfrmMain::sbReZoomClick(TObject *Sender)
{
	ZoomPointClick(LastZoomX, LastZoomY);

	if (miShowPreview->Checked && !IsBusy) RenderPreview();
}


void __fastcall TfrmMain::sbZoomCropClick(TObject *Sender)
{
	if (ZoomMode != -1)
	{
		ZoomMode = -1;

		iRender->Cursor = crDefault;
	}
	else
	{
		ZoomMode = 0;
		FirstPoint = true;

		iRender->Cursor = crCross;
	}
}


void __fastcall TfrmMain::sbBackClick(TObject *Sender)
{
	if (history->Zoom.size() > 1)
	{
		history->Zoom.pop_back();

		ZoomHistory& zh = history->Zoom.back();

		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetView(zh.xmin, zh.xmax, zh.ymin, zh.ymax);

		UpdateFractalPanel();

   		if (miShowPreview->Checked && !IsBusy) RenderPreview();
	}
}


void __fastcall TfrmMain::sbResetAllClick(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ResetAll();

	UpdateAllParameters();

	if (miShowPreview->Checked && !IsBusy) RenderPreview();
}


void __fastcall TfrmMain::sbCopyImageClick(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->CopyImage();
}


void __fastcall TfrmMain::sbMergeImageClick(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->MergeImage();

	CopyFromFractalToScreen();
}


void __fastcall TfrmMain::sbSwapImageClick(TObject *Sender)
{
	if (sbSwapImage->Tag == 0)
	{
		CopyFromBackupToScreen();
	}
	else
	{
		CopyFromFractalToScreen();
	}
}


void __fastcall TfrmMain::sbDescriptionClick(TObject *Sender)
{
	ImageDescription id = OpenTextDialog(imagedescription);

	if (id.Valid)
	{
		imagedescription->Active = id.Active;
		imagedescription->FontName = id.FontName;
		imagedescription->FontSize = id.FontSize;
        imagedescription->PositionY = id.PositionY;
	}
}


void __fastcall TfrmMain::sbAboutClick(TObject *Sender)
{
	frmAbout->ShowModal();
}


 void __fastcall TfrmMain::eWidthExit(TObject *Sender)
{
	UpdateDimension(false);
}


void __fastcall TfrmMain::bEditPaletteClick(TObject *Sender)
{
	TfrmPaletteEditor *frmPaletteEditor = new TfrmPaletteEditor(Application);

    frmPaletteEditor->PalettePath = PalettePath;

	if (frmPaletteEditor->ShowModal() == mrOk)
	{
		CopyPaletteToFractal();

		UpdatePalette();

		if (miShowPreview->Checked) RenderPreview();
	}

	delete frmPaletteEditor;
}


void __fastcall TfrmMain::sbLoadPaletteClick(TObject *Sender)
{
	odPalette->InitialDir = PalettePath.c_str();

	if (odPalette->Execute())
	{
		GPaletteHandler->Clear(false);

		if (LoadAndSetPalette(odPalette->FileName.c_str()))
		{
			PalettePath = ExtractFilePath(odPalette->FileName);

			if (miShowPreview->Checked) RenderPreview();
		}
		else
		{
			std::wstring error = L"Error loading palette, using default.";

			sbMain->SimpleText = error.c_str();
		}
	}
}


bool TfrmMain::LoadAndSetPalette(const std::wstring file_name)
{
	bool result = GPaletteHandler->Load(file_name);

	GPaletteHandler->Render();
	GPaletteHandler->CopyPublic();

	CopyPaletteToFractal();

	UpdatePalette();

	return result;
}



void __fastcall TfrmMain::sInfinityMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (frmColourDialog->ShowModal() == mrOk)
	{
		sInfinity->Brush->Color = TColor(frmColourDialog->SelectedColour);

		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetPaletteInfinity(Colour(sInfinity->Brush->Color));

		GPaletteHandler->Palette[__PaletteInfinity].FromIntBGR(sInfinity->Brush->Color);
	}
}


void TfrmMain::CopyPaletteToFractal()
{
	// 0 - 499, main palette; 500, infinity colour
	for (int t = 0; t < 500; t++)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Palette[t] = GPaletteHandler->Palette[t];
	}

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetPaletteInfinity(GPaletteHandler->Palette[__PaletteInfinity]);
}


void TfrmMain::UpdatePalette()
{
	pbPalette->Canvas->StretchDraw(TRect(0, 0, 124, 19), GPaletteHandler->Gradient);

	sInfinity->Brush->Color = TColor(GPaletteHandler->Palette[__PaletteInfinity].ToIntBGR());
}


void __fastcall TfrmMain::FormPaint(TObject *Sender)
{
	UpdatePalette();
}


void __fastcall TfrmMain::cbFractalSelectorChange(TObject *Sender)
{
	IsBusy = true;

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetRenderMode(cbRenderMode->ItemIndex);

	sbReZoom->Enabled = false;

	UpdateZoomPanel();

	UpdateABCPanel();

	UpdateDimension(false);

	CopyPaletteToFractal();

	UpdateFromFractalChange();

	SetWarning(false);

	IsBusy = false;
}


void __fastcall TfrmMain::cbRenderModeChange(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetRenderMode(cbRenderMode->ItemIndex);

	UpdateABCPanel();

    if (miShowPreview->Checked) RenderPreview();
}


void __fastcall TfrmMain::eCoeffNExit(TObject *Sender)
{
	double n = eCoeffN->Text.ToDouble();
	int i = eIterations->Text.ToIntDef(-1);
	int rb = eBailoutRadius->Text.ToIntDef(-1);

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetParameters(n, i, rb);

	if (n <= 0)
	{
		eCoeffN->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff);
	}

	if (i <= 0)
	{
		eIterations->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations);
	}

	if (rb < 4)
	{
		eBailoutRadius->Text = FloatToStr(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->bailout_radius);
	}

	if (Sender != nullptr)
	{
		if (miShowPreview->Checked) RenderPreview();
	}
}


void __fastcall TfrmMain::sbCopyBoundsToClipboardClick(TObject *Sender)
{
	TClipboard *clippy = Clipboard();

	std::wstring bounds = L"xmin = " + std::to_wstring(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin) +
		L", xmax = " + std::to_wstring(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax) +
		L", ymin = " + std::to_wstring(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin) +
		L", ymax = " + std::to_wstring(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax);

	clippy->AsText = bounds.c_str();
}


void __fastcall TfrmMain::miCopyAllToClipboardClick(TObject *Sender)
{
	TClipboard *clippy = Clipboard();

	std::wstring parameters(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->GetParameters());

	clippy->AsText = parameters.c_str();
}


void __fastcall TfrmMain::miQPAClick(TObject *Sender)
{
	TMenuItem* mi = (TMenuItem*)Sender;

	switch (mi->Tag)
	{
	case 0:
		QPFine = 0.01;
		break;
	case 1:
		QPFine = 0.001;
		break;
	case 2:
		QPFine = 0.0001;
		break;
	case 3:
		QPFine = 0.00001;
		break;
	case 4:
		QPFine = 0.000001;
		break;
	}
}


void __fastcall TfrmMain::sbEditBoundsClick(TObject *Sender)
{
	frmEditBounds->SetBoundsValues(
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width,
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height,
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin,
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax,
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin,
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax);

	if (frmEditBounds->ShowModal() == mrOk)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetView(frmEditBounds->xmin,
			frmEditBounds->xmax,
			frmEditBounds->ymin,
			frmEditBounds->ymax);

        UpdateFractalPanel();
	}
}


void __fastcall TfrmMain::miDesktopDimensionClick(TObject *Sender)
{
	TMenuItem* mi = (TMenuItem*)Sender;

	eWidth->Text = DimensionsDesktop[mi->Tag][0];
	eHeight->Text = DimensionsDesktop[mi->Tag][1];

	UpdateDimension(false);
}


void __fastcall TfrmMain::miMobileDimensionsClick(TObject *Sender)
{
	TMenuItem* mi = (TMenuItem*)Sender;

	eWidth->Text = DimensionsPhone[mi->Tag][0];
	eHeight->Text = DimensionsPhone[mi->Tag][1];

	UpdateDimension(false);
}


void __fastcall TfrmMain::miTextureDimensionsClick(TObject *Sender)
{
	TMenuItem* mi = (TMenuItem*)Sender;

	eWidth->Text = DimensionsTexture[mi->Tag];
	eHeight->Text = DimensionsTexture[mi->Tag];

	UpdateDimension(false);
}


void __fastcall TfrmMain::miExampleJS1Click(TObject *Sender)
{
	TMenuItem* mi = (TMenuItem*)Sender;

	eVarA->Text = JuliaSetExamples[mi->Tag][0];
	eVarB->Text = JuliaSetExamples[mi->Tag][1];

	if (miShowPreview->Checked && !IsBusy) RenderPreview();
}


void __fastcall TfrmMain::miExampleM1Click(TObject *Sender)
{
	TMenuItem* mi = (TMenuItem*)Sender;

	eVarA->Text = MartinExamples[mi->Tag][0];
	eVarB->Text = MartinExamples[mi->Tag][1];
	eVarC->Text = MartinExamples[mi->Tag][2];

	if (miShowPreview->Checked && !IsBusy) RenderPreview();
}


void __fastcall TfrmMain::iRenderMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	double x = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin + (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->x_resolution * X);
	double y = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin + (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->y_resolution * Y);

	std::wstring s = std::to_wstring(x) + L", " + std::to_wstring(y);

	lCursor->Caption = s.c_str();

	///lCursorColour->Caption = ColourUtility::BGRtoRGBHex(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Canvas[Y * iRender->Width + X]); TO DO
}


void __fastcall TfrmMain::Panel3MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	lCursor->Caption = "-";

	lCursorColour->Caption = "-";
}


void TfrmMain::SetWarning(bool warning)
{
	if (warning)
	{
		if (lVarA->Font->Color != clMaroon)
		{
			lVarA->Font->Color = clMaroon;
			lVarB->Font->Color = clMaroon;
		}
	}
	else
	{
		if (lVarA->Font->Color != clWindowText)
		{
			lVarA->Font->Color = clWindowText;
			lVarB->Font->Color = clWindowText;
		}
	}
}
