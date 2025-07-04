//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
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


#include "Animation.h"
#include "FractalHandler.h"
#include "HistoryHandler.h"
#include "ImageDescription.h"
#include "Mandelbrot.h"
#include "MartinClassic.h"
#include "ProjectIO.h"

#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>


class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel3;
	TImage *iRender;
	TSpeedButton *sbRender;
	TSpeedButton *sbSaveImage;
	TStatusBar *sbMain;
	TImageList *ImageList1;
	TSpeedButton *bSaveProject;
	TSpeedButton *bOpenProject;
	TBevel *Bevel2;
	TBevel *Bevel3;
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
	TSpeedButton *sbReset;
	TSpeedButton *sbZoom;
	TSpeedButton *sbZoomCrop;
	TSpeedButton *sbBack;
	TSpeedButton *sbForward;
	TBevel *Bevel4;
	TPopupMenu *puExamples;
	TMenuItem *JuliaSets1;
	TMenuItem *miExampleJS1;
	TMenuItem *N1621041;
	TMenuItem *N3011;
	TMenuItem *N147601;
	TMenuItem *N12771;
	TMenuItem *N280081;
	TMenuItem *N0081;
	TMenuItem *N037011;
	TMenuItem *N035503551;
	TMenuItem *N0540541;
	TMenuItem *N040591;
	TMenuItem *N0340051;
	TMenuItem *N035553403372921;
	TMenuItem *N01621041;
	TMenuItem *N0790151;
	TMenuItem *N03300081;
	TMenuItem *N0745430113011;
	TMenuItem *N0801561;
	TMenuItem *N0260541;
	TMenuItem *N1040041;
	TMenuItem *N1135024751;
	TMenuItem *N11825031751;
	TMenuItem *N072032751;
	TMenuItem *N11767506451;
	TMenuItem *Martin1;
	TMenuItem *miExampleM1;
	TMenuItem *N6875832;
	TMenuItem *N10101001;
	TMenuItem *N2004801;
	TMenuItem *N1371741;
	TMenuItem *N10100101;
	TMenuItem *N10100102;
	TMenuItem *N12182561;
	TMenuItem *Export1;
	TMenuItem *miSaveParameters;
	TMenuItem *N7;
	TMenuItem *miSaveAllImages;
	TBevel *Bevel5;
	TSpeedButton *sbAbout;
	TMenuItem *N101;
	TMenuItem *N102;
	TMenuItem *N8;
	TMenuItem *miRMBSetParameters;
	TMenuItem *Help1;
	TMenuItem *About1;
	TMenuItem *N9;
	TMenuItem *miSaveFractalParameters;
	TMenuItem *miRenderAnimation;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *miConfigAnimation;
	TSpeedButton *eAnimation;
	TSpeedButton *sbReZoom;
	TMenuItem *N12;
	TMenuItem *N0801562;
	TMenuItem *exture1;
	TMenuItem *N13;
	TMenuItem *miTextureDimensions;
	TMenuItem *N128x1282;
	TMenuItem *N128x1283;
	TMenuItem *N128x1284;
	TMenuItem *N128x1285;
	TMenuItem *N128x1286;
	TOpenDialog *odPalette;
	TMenuItem *N3840x21601;
	TSpeedButton *sbResetAll;
	TBevel *Bevel6;
	TSpeedButton *sbZoomOnPoint;
	TMenuItem *Edity1;
	TMenuItem *Copyboundstoclipboard1;
	TMenuItem *miCopyAllToClipboard;
	TSpeedButton *sbCopyImage;
	TSpeedButton *sbMergeImage;
	TBevel *Bevel7;
	TSpeedButton *sbSwapImage;
	TMenuItem *N14;
	TMenuItem *QuickParameter1;
	TMenuItem *miQPA;
	TMenuItem *miQPB;
	TMenuItem *miQPC;
	TMenuItem *miQPD;
	TMenuItem *miQPE;
	TMenuItem *N15;
	TMenuItem *miShowPreview;
	TSpeedButton *sbDescription;
	TBevel *Bevel8;
	TMenuItem *miSuperSample;
	TSpeedButton *sbZoomCentre;
	TSpeedButton *sbZoomOut;
	TBevel *Bevel9;
	TBevel *Bevel10;
	TMenuItem *Samples1;
	TMenuItem *N16;
	TMenuItem *miSamples4;
	TMenuItem *miSamples8;
	TMenuItem *miSamples16;
	TMenuItem *miSamples32;
	TMenuItem *JuliaCubic1;
	TMenuItem *miExampleJC1;
	TMenuItem *miExampleJC2;
	TMenuItem *miExampleJC3;
	TMenuItem *miExampleJC4;
	TMenuItem *miExampleJC5;
	TMenuItem *N1659068071;
	TMenuItem *N1659068072;
	TMenuItem *N0789131631;
	TMenuItem *N0789131632;
	TMenuItem *N16070611;
	TMenuItem *N17;
	TMenuItem *miRecolour;
	TPanel *pMain;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox4;
	TLabel *lCursor;
	TLabel *lCursorColour;
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
	TSpeedButton *sbCopyBoundsToClipboard;
	TSpeedButton *sbEditBounds;
	TEdit *eWidth;
	TEdit *eHeight;
	TGroupBox *GroupBox1;
	TSpeedButton *bEditPalette;
	TPaintBox *pbPalette;
	TShape *sInfinity;
	TSpeedButton *sbLoadPalette;
	TGroupBox *gbVarABC;
	TLabel *lVarA;
	TLabel *lVarB;
	TLabel *lVarC;
	TLabel *lVarD;
	TEdit *eVarA;
	TEdit *eVarB;
	TEdit *eVarC;
	TEdit *eVarD;
	TGroupBox *GroupBox3;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TComboBox *cbRenderMode;
	TEdit *eCoeffN;
	TEdit *eIterations;
	TEdit *eBailoutRadius;
	TLabel *Label16;
	TComboBox *cbFractalSelector;
	TBevel *Bevel1;
	TListBox *lbHistory;
	TPanel *Panel2;
	TSpeedButton *sbClearHistory;
	TSpeedButton *sbLoadHistory;
	TSpeedButton *sbSaveHistory;
	TMenuItem *N18;
	TMenuItem *miCopyToClipboard;
	TPanel *Panel4;
	TImage *iPreview;
	TLabel *lCursorAbsolute;
	TMenuItem *miSamples64;
	TMenuItem *N027930011;
	TMenuItem *Resize1;
	TMenuItem *N19;
	TMenuItem *Quarter1;
	TMenuItem *Half1;
	TMenuItem *Half2;
	TMenuItem *Quadruplex41;
	TPaintBox *pbPalette2;
	TShape *sInfinity2;
	void __fastcall sbRenderClick(TObject *Sender);
	void __fastcall sbSaveImageClick(TObject *Sender);
	void __fastcall iRenderMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sbZoomClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall sbResetClick(TObject *Sender);
	void __fastcall sbBackClick(TObject *Sender);
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
	void __fastcall miExampleJS1Click(TObject *Sender);
	void __fastcall miExampleM1Click(TObject *Sender);
	void __fastcall sbAboutClick(TObject *Sender);
	void __fastcall eWidthExit(TObject *Sender);
	void __fastcall iRenderMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Panel3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall sInfinityMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall miSaveFractalParametersClick(TObject *Sender);
	void __fastcall miConfigAnimationClick(TObject *Sender);
	void __fastcall eAnimationClick(TObject *Sender);
	void __fastcall sbReZoomClick(TObject *Sender);
	void __fastcall miTextureDimensionsClick(TObject *Sender);
	void __fastcall sbLoadPaletteClick(TObject *Sender);
	void __fastcall sbResetAllClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sbZoomOnPointClick(TObject *Sender);
	void __fastcall miCopyAllToClipboardClick(TObject *Sender);
	void __fastcall sbCopyImageClick(TObject *Sender);
	void __fastcall sbMergeImageClick(TObject *Sender);
	void __fastcall sbSwapImageClick(TObject *Sender);
	void __fastcall miQPAClick(TObject *Sender);
	void __fastcall sbDescriptionClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall miShowPreviewClick(TObject *Sender);
	void __fastcall sbZoomCentreClick(TObject *Sender);
	void __fastcall sbZoomOutClick(TObject *Sender);
	void __fastcall miSuperSampleClick(TObject *Sender);
	void __fastcall miSamples4Click(TObject *Sender);
	void __fastcall miExampleJC1Click(TObject *Sender);
	void __fastcall sbClearHistoryClick(TObject *Sender);
	void __fastcall lbHistoryDblClick(TObject *Sender);
	void __fastcall sbLoadHistoryClick(TObject *Sender);
	void __fastcall sbSaveHistoryClick(TObject *Sender);
	void __fastcall miCopyToClipboardClick(TObject *Sender);
	void __fastcall Half2Click(TObject *Sender);
	void __fastcall pbPalette2Click(TObject *Sender);
	void __fastcall sInfinity2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);


private:	// User declarations

	bool IsBusy = false;

    double QPFine = 0.1;

    FractalHandler* GFractalHandler = nullptr;

	HistoryHandler* history = nullptr;
	ProjectIO* projectio = nullptr;
	ImageDescription* imagedescription = nullptr;

	Graphics::TBitmap* PaletteBitmap;

	Animation AnimationConfiguration;

	std::wstring PalettePath = L"";
	std::wstring ProjectPath = L"";
    std::wstring RenderPath = L"";

	int ZoomMode = -1;
	bool FirstPoint = True;

	double ZPoint1x, ZPoint1y;
	double ZPoint2x, ZPoint2y;

	double LastZoomX, LastZoomY;

	void RenderPreview();

	void ZoomPointClick(double, double);
	void ZoomOut();

	void SaveFractal(const std::wstring);
	void SaveFractalParameters(const std::wstring);

	void UpdateDimension(bool);
	void UpdateABCPanel();
    void UpdateZoomPanel();

	void SetFromProjectFile(PCProject&, Animation&);
	PCProject GetProjectSettings();

    void RenderTextToScreen();

	void CopyFromFractalToScreen();
    void CopyFromFractalToPreview();
    void CopyFromBackupToScreen();

	void UpdateFromFractalChange();
	void UpdateFractalPanel();
	void UpdatePalette();
    void UpdateAllParameters();

	bool LoadAndSetPalette(int, const std::wstring);

	void SetWarning(bool);

	void SetTitle(const std::wstring);

    void UpdateLastHistoryItem();

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};

extern PACKAGE TfrmMain *frmMain;

#endif
