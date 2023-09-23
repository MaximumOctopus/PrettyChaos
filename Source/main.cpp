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

	fractal = new Mandelbrot();
	history = new HistoryHandler();
    projectio = new ProjectIO();

	history->Add(fractal->xmin, fractal->xmax, fractal->ymin, fractal->ymax);

	System::WideChar k = VK_RETURN;

	eWidthKeyPress(nullptr, k);

	UpdatePalette();
}

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	delete fractal;
	delete history;
    delete projectio;
}


void TfrmMain::SetFromProjectFile(PCProject &project)
{
	fractal->Width = project.Width;
	fractal->Height = project.Height;

	fractal->SetRenderMode(project.RenderMode);
	fractal->n_coeff = project.nCoeff;

	fractal->max_iterations = project.MaxIterations;
	fractal->bailout_radius = project.BailoutRadius;

	fractal->xmin = project.xmin;
	fractal->xmax = project.xmax;
	fractal->ymin = project.ymin;
	fractal->ymax = project.ymax;

	iRender->Width = fractal->Width;
	iRender->Height = fractal->Height;

	// ====

	cbRenderMode->ItemIndex = fractal->RenderMode;

	eCoeffN->Text = fractal->n_coeff;
	eWidth->Text = fractal->Width;
	eHeight->Text = fractal->Height;

    UpdateFractalPanel();
}


PCProject TfrmMain::GetProjectSettings()
{
	PCProject project;

	project.Width = fractal->Width;
	project.Height = fractal->Height;

	project.RenderMode = fractal->RenderMode;
	project.nCoeff = fractal->n_coeff;

	project.MaxIterations = fractal->max_iterations;
	project.BailoutRadius = fractal->bailout_radius;

	project.xmin = fractal->xmin;
	project.xmax = fractal->xmax;
	project.ymin = fractal->ymin;
	project.ymax = fractal->ymax;

	return project;
}


void TfrmMain::UpdateFractalPanel()
{
	lXMin->Caption = fractal->xmin;
	lXMax->Caption = fractal->xmax;
	lYMin->Caption = fractal->ymin;
	lYMax->Caption = fractal->ymax;

	//Caption = (fractal->xmax - fractal->xmin) / (fractal->ymax - fractal->ymin); ratio
}


void TfrmMain::UpdateDimension()
{
	int Width = eWidth->Text.ToIntDef(-1);
	int Height = eHeight->Text.ToIntDef(-1);

	if (Width > 0 && Height > 0)
	{
		fractal->SetDimensions(Width, Height);

		iRender->Width = Width;
		iRender->Height = Height;

		UpdateFractalPanel();
	}
}


void __fastcall TfrmMain::sbRenderClick(TObject *Sender)
{
	sbMain->SimpleText = "Rendering...";

    eCoeffNExit(nullptr);

	fractal->SetDimensions(iRender->Width, iRender->Height);

	fractal->Render();

	std::wstring c = L"Rendered in " + fractal->RenderTime + L" seconds.";// + fractal->debug;

	sbMain->SimpleText = c.c_str();

	TBitmap* bit = new TBitmap();
	bit->PixelFormat = pf24bit;
	bit->Width = fractal->Width;
	bit->Height = fractal->Height;

	TRGBTriple *ptr;

	for (int y = 0; y < fractal->Height; y++)
	{
		ptr = reinterpret_cast<TRGBTriple *>(bit->ScanLine[y]);

		for (int x = 0; x < fractal->Width; x++)
		{
			ptr[x].rgbtRed = fractal->Canvas[y * fractal->Width + x] & 0x0000ff;
			ptr[x].rgbtGreen = fractal->Canvas[y * fractal->Width + x] >> 8 & 0x0000ff;
			ptr[x].rgbtBlue = fractal->Canvas[y * fractal->Width + x] >> 16 & 0x0000ff;
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
    fractal->ResetView();
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

		fractal->SetView(zh.xmin, zh.xmax, zh.ymin, zh.ymax);

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
		for (int t = 0; t < 500; t++)
		{
			fractal->Palette[t] = frmPaletteEditor->Palette[t];
		}

        fractal->PaletteInfinity = frmPaletteEditor->InfinityColour;

		UpdatePalette();
	}
}


void TfrmMain::UpdatePalette()
{
	TRGBTriple *ptr = reinterpret_cast<TRGBTriple *>(PaletteBitmap->ScanLine[0]);

	for (int t = 0; t < 125; t++)
	{
		ptr[t].rgbtBlue = fractal->Palette[t * 4] >> 16 & 0x0000ff;
		ptr[t].rgbtGreen = fractal->Palette[t * 4] >> 8 & 0x0000ff;
		ptr[t].rgbtRed = fractal->Palette[t * 4] & 0x0000ff;
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


void __fastcall TfrmMain::cbRenderModeChange(TObject *Sender)
{
	fractal->SetRenderMode(cbRenderMode->ItemIndex);
}


void __fastcall TfrmMain::eCoeffNExit(TObject *Sender)
{
	double n = eCoeffN->Text.ToDouble();
	int i = eIterations->Text.ToIntDef(-1);
	int rb = eBailoutRadius->Text.ToIntDef(-1);

	fractal->SetParameters(n, i, rb);

	if (n <= 0)
	{
		eCoeffN->Text = fractal->n_coeff;
	}

	if (i <= 0)
	{
		eIterations->Text = fractal->max_iterations;
	}

	if (rb < 4)
	{
		eBailoutRadius->Text = fractal->bailout_radius;
	}
}


void __fastcall TfrmMain::sbCopyBoundsToClipboardClick(TObject *Sender)
{
	TClipboard *clippy = Clipboard();

	std::wstring bounds = L"xmin = " + std::to_wstring(fractal->xmin) +
		L", xmax = " + std::to_wstring(fractal->xmax) +
		L", ymin = " + std::to_wstring(fractal->ymin) +
		L", ymax = " + std::to_wstring(fractal->ymax);

	clippy->AsText = bounds.c_str();
}


void __fastcall TfrmMain::sbEditBoundsClick(TObject *Sender)
{
	frmEditBounds->SetBoundsValues(
		fractal->Width,
        fractal->Height,
		fractal->xmin,
		fractal->xmax,
		fractal->ymin,
        fractal->ymax);

	if (frmEditBounds->ShowModal() == mrOk)
	{
		fractal->SetView(frmEditBounds->xmin,
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
