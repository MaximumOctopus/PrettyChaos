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
#include <Vcl.Imaging.pngimage.hpp>
#pragma hdrstop

#include <Clipbrd.hpp>

#include "main.h"

#include "FormEditBounds.h"
#include "PaletteEditor.h"

#include "Constants.h"
#include "Mandelbrot.h"
#include "Martin.h"
#include "Utility.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;


__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	Caption = __PrettyChaosVersion.c_str();

	PaletteBitmap = new Graphics::TBitmap;
		PaletteBitmap->PixelFormat = pf24bit;
		PaletteBitmap->Width = 125;
		PaletteBitmap->Height = 1;

	GFractalHandler = new FractalHandler();

	for (int t = 0; t < GFractalHandler->Fractals.size(); t++)
	{
		cbFractalSelector->Items->Add(GFractalHandler->Fractals[t]->Name.c_str());
	}

    cbFractalSelector->ItemIndex = 0;

	history = new HistoryHandler();
    projectio = new ProjectIO();

	history->Add(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin, GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax,
				 GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin, GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax);

	System::WideChar k = VK_RETURN;

	cbFractalSelectorChange(nullptr);

	eWidthKeyPress(nullptr, k);

	UpdatePalette();
}

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	delete GFractalHandler;
	delete history;
	delete projectio;
}


void TfrmMain::UpdateFromFractalChange()
{
	eCoeffN->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff;
	eIterations->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations;
	eBailoutRadius->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->bailout_radius;

	eWidth->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width;
	eHeight->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height;

	if (gbVarABC->Visible)
	{
		eVarA->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.a;
		eVarB->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.b;
		eVarC->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.c;
    }

	cbRenderMode->Clear();

	for (int t = 0; t < GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderModes.size(); t++)
	{
		cbRenderMode->Items->Add(GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderModes[t].c_str());
	}

    cbRenderMode->ItemIndex = 0;
}


void TfrmMain::SetFromProjectFile(PCProject &project)
{
	for (int t = 0; t < cbFractalSelector->Items->Count; t++)
	{
		if (cbFractalSelector->Items[t].Text == project.Name.c_str())
		{
			cbFractalSelector->ItemIndex = t;
            cbFractalSelectorChange(nullptr);
		}
    }

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width = project.Width;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height = project.Height;

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetRenderMode(project.RenderMode);
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff = project.nCoeff;

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations = project.MaxIterations;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->bailout_radius = project.BailoutRadius;

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin = project.xmin;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax = project.xmax;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin = project.ymin;
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax = project.ymax;

	iRender->Width = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width;
	iRender->Height = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height;

	// ====

	cbRenderMode->ItemIndex = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderMode;

	eCoeffN->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff;
	eWidth->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width;
	eHeight->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height;

	eVarA->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.a;
	eVarB->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.b;
	eVarC->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Var.c;

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

	return project;
}


void TfrmMain::UpdateFractalPanel()
{
	lXMin->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmin;
	lXMax->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->xmax;
	lYMin->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymin;
	lYMax->Caption = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ymax;

	//Caption = (fractal->xmax - fractal->xmin) / (fractal->ymax - fractal->ymin); ratio
}


void TfrmMain::UpdateDimension()
{
	int Width = eWidth->Text.ToIntDef(-1);
	int Height = eHeight->Text.ToIntDef(-1);

	if (Width > 0 && Height > 0)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetDimensions(Width, Height);

		iRender->Width = Width;
		iRender->Height = Height;

		UpdateFractalPanel();
	}
}


void __fastcall TfrmMain::sbRenderClick(TObject *Sender)
{
	sbMain->SimpleText = "Rendering...";

	if (GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsABC)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetABC(eVarA->Text.ToDouble(), eVarB->Text.ToDouble(), eVarC->Text.ToDouble());
	}

    eCoeffNExit(nullptr);

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetDimensions(iRender->Width, iRender->Height);

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Render();

	std::wstring c = L"Rendered in " + GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->RenderTime + L" seconds.";// + fractal->debug;

	sbMain->SimpleText = c.c_str();

	TBitmap* bit = new TBitmap();
	bit->PixelFormat = pf24bit;
	bit->Width = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width;
	bit->Height = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height;

	TRGBTriple *ptr;

	for (int y = 0; y < GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Height; y++)
	{
		ptr = reinterpret_cast<TRGBTriple *>(bit->ScanLine[y]);

		for (int x = 0; x < GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width; x++)
		{
			ptr[x].rgbtRed = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Canvas[y * GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width + x] & 0x0000ff;
			ptr[x].rgbtGreen = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Canvas[y * GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width + x] >> 8 & 0x0000ff;
			ptr[x].rgbtBlue = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Canvas[y * GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Width + x] >> 16 & 0x0000ff;
		}
	}

	iRender->Picture->Assign(bit);

	delete bit;
}


void __fastcall TfrmMain::bOpenProjectClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetOpenFileName(0);

	if (!file_name.empty())
	{
		if (file_name.find(L".prttychs") == std::wstring::npos)
		{
			file_name += L".prttychs";
		}

		PCProject project;

		projectio->Load(file_name, project);

		SetFromProjectFile(project);
	}
}


void __fastcall TfrmMain::bSaveProjectClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(0);

	if (!file_name.empty())
	{
		if (file_name.find(L".prttychs") == std::wstring::npos)
		{
			file_name += L".prttychs";
		}

		PCProject project = GetProjectSettings();

		projectio->Save(file_name, project);
	}
}


void __fastcall TfrmMain::sbSaveImageClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(1);

	if (!file_name.empty())
	{
		if (file_name.find(L".png") == std::wstring::npos)
		{
			file_name += L".png";
		}

		TPngImage* png  = new TPngImage();
		png->Assign(iRender->Picture->Bitmap);

		png->SaveToFile(file_name.c_str());

		delete png;
	}
}


void __fastcall TfrmMain::iRenderMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
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

			history->Add(fractal->xmin, fractal->xmax, fractal->ymin, fractal->ymax);

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

			Fractal* &fractal = GFractalHandler->Fractals[cbFractalSelector->ItemIndex];

			double xmin = fractal->xmin + (((fractal->xmax - fractal->xmin) / fractal->Width) * (double)X);
			double ymin = fractal->ymin + (((fractal->ymax - fractal->ymin) / fractal->Height) * (double)Y);

			fractal->ZoomAtPoint(xmin, ymin);

			history->Add(fractal->xmin, fractal->xmax, fractal->ymin, fractal->ymax);

			UpdateFractalPanel();

			iRender->Cursor = crDefault;
		}
		break;
	}
	}
}


void __fastcall TfrmMain::sbResetClick(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->ResetView();
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
	if (history->History.size() > 1)
	{
		history->History.pop_back();

		ZoomHistory& zh = history->History.back();

		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetView(zh.xmin, zh.xmax, zh.ymin, zh.ymax);

		UpdateFractalPanel();
	}
}


void __fastcall TfrmMain::eWidthKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Key == VK_RETURN)
	{
		UpdateDimension();
	}
}


void __fastcall TfrmMain::bEditPaletteClick(TObject *Sender)
{
	if (frmPaletteEditor->ShowModal() == mrOk)
	{
		CopyPaletteToFractal();

		UpdatePalette();
	}
}


void TfrmMain::CopyPaletteToFractal()
{
	if (frmPaletteEditor != nullptr)
	{
	for (int t = 0; t < 500; t++)
	{
		GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Palette[t] = frmPaletteEditor->Palette[t];
	}

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->PaletteInfinity = frmPaletteEditor->InfinityColour;
	}
}


void TfrmMain::UpdatePalette()
{
	TRGBTriple *ptr = reinterpret_cast<TRGBTriple *>(PaletteBitmap->ScanLine[0]);

	for (int t = 0; t < 125; t++)
	{
		ptr[t].rgbtBlue = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Palette[t * 4] >> 16 & 0x0000ff;
		ptr[t].rgbtGreen = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Palette[t * 4] >> 8 & 0x0000ff;
		ptr[t].rgbtRed = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->Palette[t * 4] & 0x0000ff;
	}

	for (int t = 0; t < 20; t++)
	{
		pbPalette->Canvas->Draw(0, t, PaletteBitmap);
	}
}


void __fastcall TfrmMain::FormPaint(TObject *Sender)
{
	UpdatePalette();
}


void __fastcall TfrmMain::cbFractalSelectorChange(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetRenderMode(cbRenderMode->ItemIndex);

	gbVarABC->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsABC;

	if (gbVarABC->Visible)
	{
		lVarB->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarB;
		eVarB->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarB;
		lVarC->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarC;
		eVarC->Visible = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->AcceptsVarC;
	}

	UpdateDimension();

    CopyPaletteToFractal();

	UpdateFromFractalChange();
}


void __fastcall TfrmMain::cbRenderModeChange(TObject *Sender)
{
	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetRenderMode(cbRenderMode->ItemIndex);
}


void __fastcall TfrmMain::eCoeffNExit(TObject *Sender)
{
	double n = eCoeffN->Text.ToDouble();
	int i = eIterations->Text.ToIntDef(-1);
	int rb = eBailoutRadius->Text.ToIntDef(-1);

	GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->SetParameters(n, i, rb);

	if (n <= 0)
	{
		eCoeffN->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->n_coeff;
	}

	if (i <= 0)
	{
		eIterations->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->max_iterations;
	}

	if (rb < 4)
	{
		eBailoutRadius->Text = GFractalHandler->Fractals[cbFractalSelector->ItemIndex]->bailout_radius;
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
			frmEditBounds->xmin,
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

	UpdateDimension();
}


void __fastcall TfrmMain::miMobileDimensionsClick(TObject *Sender)
{
	TMenuItem* mi = (TMenuItem*)Sender;

	eWidth->Text = DimensionsPhone[mi->Tag][0];
	eHeight->Text = DimensionsPhone[mi->Tag][1];

    UpdateDimension();
}
