//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include "PaletteKey.h"

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
	TGroupBox *GroupBox1;
	TShape *sInfinity;
	TLabel *lInfinityHex;
	TLabel *lColourHex;
	TLabel *Label5;
	TLabel *lLog;
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
	void __fastcall sInfinityMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
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

private:

	static const int __KeyOffset = 12;
	static const int __KeyTop = 78;

    bool IsRendering = false;
	bool SliderUpdating = false;
	bool KeyDisplayUpdating = false;

	bool KeyMoveMode = false;
	int KeyInitialX = 0;
	int KeySelected = 0;

	TBitmap* RGBGradients[3];
    TBitmap* bGradient;

	std::vector<PaletteKey> PaletteKeys;

    void AddNewKey(int, int, int);

	void UpdateKeyDisplay(int);
	void BuildRGBGradients();
    void BuildHSVGradients();

	void RenderGradient();

	int GradientKeyAt(int);
	int GetNextGradientKey(int);

	void ClearPalette();
    void ResetUI();

	void SavePalette(std::wstring);
	bool LoadPalette(std::wstring);

    int GetKeyType(const std::wstring);

public:

	int Palette[500];

    int InfinityColour = 0;

	__fastcall TfrmPaletteEditor(TComponent* Owner);
};

extern PACKAGE TfrmPaletteEditor *frmPaletteEditor;
