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
#include <tchar.h>

USEFORM("main.cpp", frmMain);
USEFORM("PaletteEditor.cpp", frmPaletteEditor);
USEFORM("FormAbout.cpp", frmAbout);
USEFORM("FormAnimate.cpp", frmAnimate);
USEFORM("FormColourDialog.cpp", frmColourDialog);
USEFORM("FormEditBounds.cpp", frmEditBounds);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TfrmPaletteEditor), &frmPaletteEditor);
		Application->CreateForm(__classid(TfrmColourDialog), &frmColourDialog);
		Application->CreateForm(__classid(TfrmEditBounds), &frmEditBounds);
		Application->CreateForm(__classid(TfrmAbout), &frmAbout);
		Application->CreateForm(__classid(TfrmAnimate), &frmAnimate);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
