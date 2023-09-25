//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#ifndef mainH
#define mainH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>

#include "FractalHandler.h"
#include "HistoryHandler.h"
#include "Mandelbrot.h"
#include "Martin.h"
#include "ProjectIO.h"

#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>


class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TImage *iRender;
	TSpeedButton *sbRender;
	TSpeedButton *sbSaveImage;
	TStatusBar *sbMain;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TLabel *lXMin;
	TLabel *lXMax;
	TLabel *lYMin;
	TLabel *lYMax;
	TLabel *Label4;
	TLabel *Label8;
	TLabel *Label7;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label6;
	TLabel *Label5;
	TLabel *Label1;
	TLabel *lWidth;
	TLabel *Label9;
	TEdit *eWidth;
	TEdit *eHeight;
	TSpeedButton *bEditPalette;
	TPaintBox *pbPalette;
	TImageList *ImageList1;
	TGroupBox *GroupBox3;
	TComboBox *cbRenderMode;
	TLabel *Label10;
	TEdit *eCoeffN;
	TSpeedButton *bSaveProject;
	TSpeedButton *bOpenProject;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TSpeedButton *sbCopyBoundsToClipboard;
	TSpeedButton *sbEditBounds;
	TLabel *Label11;
	TEdit *eIterations;
	TLabel *Label12;
	TEdit *eBailoutRadius;
	TPopupMenu *puDimensions;
	TMenuItem *Dimensions1;
	TMenuItem *Dimensions2;
	TMenuItem *miDimensions;
	TMenuItem *miDesktopDimension;
	TMenuItem *N1024x7682;
	TMenuItem *N1280x8001;
	TMenuItem *N1280x8002;
	TMenuItem *N1360x7681;
	TMenuItem *N1360x7682;
	TMenuItem *N1440x9001;
	TMenuItem *N1440x9002;
	TMenuItem *N1680x10501;
	TMenuItem *N1920x12001;
	TMenuItem *N2560x14401;
	TMenuItem *N2560x10801;
	TMenuItem *N2560x18001;
	TMenuItem *N3440x14401;
	TMenuItem *N1920x10801;
	TMenuItem *N2880x18001;
	TMenuItem *Mobilephone1;
	TMenuItem *miMobileDimensions;
	TMenuItem *iPhone11Pro1125x24361;
	TMenuItem *iPhone11Pro1125x24362;
	TMenuItem *iPhoneSE2020750x13341;
	TMenuItem *iPhoneSE2020750x13342;
	TMenuItem *iPhone12mini1125x24361;
	TMenuItem *iPhone12mini1125x24362;
	TMenuItem *iPhone12ProMax1284x27781;
	TMenuItem *iPhone12ProMax1284x27782;
	TMenuItem *iPhone13mini1080x23401;
	TMenuItem *iPhone13mini1080x23402;
	TMenuItem *iPhone13ProMax1284x27781;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *File2;
	TMenuItem *Saveproject1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *ools1;
	TMenuItem *Resetparameters1;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *Zoomintoarea1;
	TMenuItem *Render1;
	TMenuItem *Render2;
	TGroupBox *gbVarABC;
	TLabel *Label13;
	TLabel *lVarB;
	TLabel *lVarC;
	TEdit *eVarA;
	TEdit *eVarB;
	TEdit *eVarC;
	TComboBox *cbFractalSelector;
	TLabel *Label16;
	TBevel *Bevel1;
	TSpeedButton *sbReset;
	TSpeedButton *sbZoom;
	TSpeedButton *sbZoomCrop;
	TSpeedButton *sbBack;
	TSpeedButton *SpeedButton1;
	TBevel *Bevel4;
	void __fastcall sbRenderClick(TObject *Sender);
	void __fastcall sbSaveImageClick(TObject *Sender);
	void __fastcall iRenderMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sbZoomClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall sbResetClick(TObject *Sender);
	void __fastcall sbBackClick(TObject *Sender);
	void __fastcall eWidthKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall bEditPaletteClick(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall cbRenderModeChange(TObject *Sender);
	void __fastcall eCoeffNExit(TObject *Sender);
	void __fastcall bOpenProjectClick(TObject *Sender);
	void __fastcall bSaveProjectClick(TObject *Sender);
	void __fastcall sbZoomCropClick(TObject *Sender);
	void __fastcall sbCopyBoundsToClipboardClick(TObject *Sender);
	void __fastcall sbEditBoundsClick(TObject *Sender);
	void __fastcall miDesktopDimensionClick(TObject *Sender);
	void __fastcall miMobileDimensionsClick(TObject *Sender);
	void __fastcall cbFractalSelectorChange(TObject *Sender);
private:	// User declarations

    FractalHandler* GFractalHandler = nullptr;

	HistoryHandler* history = nullptr;
    ProjectIO* projectio = nullptr;

	Graphics::TBitmap* PaletteBitmap;

	int ZoomMode = -1;
	bool FirstPoint = True;

	double ZPoint1x, ZPoint1y;
	double ZPoint2x, ZPoint2y;

    void UpdateDimension();

	void SetFromProjectFile(PCProject&);
	PCProject GetProjectSettings();

    void UpdateFromFractalChange();

	void UpdateFractalPanel();

	void UpdatePalette();

	void CopyPaletteToFractal();

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};

extern PACKAGE TfrmMain *frmMain;

#endif
