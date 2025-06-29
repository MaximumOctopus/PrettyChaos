//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Dialogs.hpp>

#include <vector>

#include "PaletteHandler.h"
#include "PaletteKey.h"

extern PaletteHandler* GPaletteHandler;


class TfrmPaletteEditor : public TForm
{
__published:	// IDE-managed Components
	TImageList *iPalette;
	TBevel *Bevel2;
	TBitBtn *bSave;
	TBitBtn *bLoad;
	TBitBtn *BitBtn1;
	TBitBtn *bAccept;
	TGroupBox *GroupBox2;
	TTrackBar *tbLog;
	TSpeedButton *sbLinear;
	TSpeedButton *sbLog;
	TGroupBox *gbColour;
	TSpeedButton *sbAddNewKey;
	TImage *iPointer;
	TSpeedButton *sbColour;
	TSpeedButton *sbBW;
	TSpeedButton *sbDeleteSelectedKey;
	TLabel *Label1;
	TSpeedButton *sbClear;
	TSpeedButton *sbAlignAll;
	TPaintBox *pbGradient;
	TSpeedButton *sbRGB;
	TSpeedButton *sbHSV;
	TPageControl *pcColourSpace;
	TTabSheet *TabSheet1;
	TPaintBox *pbRed;
	TPaintBox *pbGreen;
	TPaintBox *pbBlue;
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TLabel *lHexRed;
	TLabel *lHexGreen;
	TLabel *lHexBlue;
	TSpinEdit *seRed;
	TTrackBar *tbRed;
	TSpinEdit *seGreen;
	TTrackBar *tbGreen;
	TSpinEdit *seBlue;
	TTrackBar *tbBlue;
	TTabSheet *TabSheet2;
	TPaintBox *pbHue;
	TPaintBox *pbSaturation;
	TPaintBox *pbValue;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TTrackBar *tbHue;
	TTrackBar *tbSaturation;
	TTrackBar *tbValue;
	TSpinEdit *seHue;
	TSpinEdit *seSaturation;
	TSpinEdit *seValue;
	TSpinEdit *sePosition;
	TLabel *lLog;
	TLabel *Label6;
	TComboBox *cbSteps;
	TCheckBox *cbInterleve;
	TRadioButton *rbInterleveX2;
	TRadioButton *rbInterleveX4;
	TCheckBox *cbInterleveReverse;
	TSpeedButton *sbReverse;
	TSpeedButton *sbRandom;
	TSpeedButton *sbRandomFrom;
	TComboBox *cbPalettes;
	TLabel *Label7;
	TLabel *Label5;
	TLabel *lColourHex;
	TSpeedButton *sbHorizontal;
	TSpeedButton *sbVertical;
	TShape *sSingleColour;
	TCheckBox *cbGradient;
	void __fastcall tbRedChange(TObject *Sender);
	void __fastcall sbAddNewKeyClick(TObject *Sender);
	void __fastcall shapeStartColourMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall shapeStartColourMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall shapeStartColourMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall bSaveClick(TObject *Sender);
	void __fastcall bAcceptClick(TObject *Sender);
	void __fastcall sePositionChange(TObject *Sender);
	void __fastcall bLoadClick(TObject *Sender);
	void __fastcall sbClearClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbAlignAllClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall seRedChange(TObject *Sender);
	void __fastcall seGreenChange(TObject *Sender);
	void __fastcall seBlueChange(TObject *Sender);
	void __fastcall sbColourClick(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall sbRGBClick(TObject *Sender);
	void __fastcall tbHueChange(TObject *Sender);
	void __fastcall seHueChange(TObject *Sender);
	void __fastcall seSaturationChange(TObject *Sender);
	void __fastcall seValueChange(TObject *Sender);
	void __fastcall sbLinearClick(TObject *Sender);
	void __fastcall sbDeleteSelectedKeyClick(TObject *Sender);
	void __fastcall pcColourSpaceChange(TObject *Sender);
	void __fastcall pbRedPaint(TObject *Sender);
	void __fastcall pbGreenPaint(TObject *Sender);
	void __fastcall pbBluePaint(TObject *Sender);
	void __fastcall pbHuePaint(TObject *Sender);
	void __fastcall pbValuePaint(TObject *Sender);
	void __fastcall pbSaturationPaint(TObject *Sender);
	void __fastcall cbStepsChange(TObject *Sender);
	void __fastcall cbInterleveClick(TObject *Sender);
	void __fastcall rbInterleveX2Click(TObject *Sender);
	void __fastcall cbInterleveReverseClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall sbReverseClick(TObject *Sender);
	void __fastcall sbRandomClick(TObject *Sender);
	void __fastcall sbRandomFromClick(TObject *Sender);
	void __fastcall tbLogChange(TObject *Sender);
	void __fastcall cbPalettesChange(TObject *Sender);
	void __fastcall sSingleColourMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

private:

	int PaletteR[500];
	int PaletteG[500];
	int PaletteB[500];

	std::vector<TShape*> Shapes;

	static const int __KeyOffset = 12;
	static const int __KeyTop = 90;

	bool IsRendering = false;
	bool SliderUpdating = false;
	bool KeyDisplayUpdating = false;

	bool KeyMoveMode = false;
	int KeyInitialX = 0;
	int KeySelected = 0;

    TShape *Selected = nullptr;

	TBitmap* RGBGradients[3];

    void BuildGuiForPalette();

	void AddNewPaletteKey(int, int, int);

    void AddShape(int);

    void UpdateAllKeys();

	void UpdateKeyDisplay(int);
	void BuildRGBGradients();
	void BuildHSVGradients();

	void RenderGradient();

	void ClearPalette(bool);
	void ResetUI();

	void SavePalette(std::wstring);

public:

	int CurrentPaletteIndex = 0;

	std::wstring PaletteFileName = L"";    // relative to \palettes\

    std::wstring PalettePath = L"";

	__fastcall TfrmPaletteEditor(TComponent* Owner);
};

bool OpenPalette(int, const std::wstring);

extern PACKAGE TfrmPaletteEditor *frmPaletteEditor;
