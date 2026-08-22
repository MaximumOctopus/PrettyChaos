//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2026
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("PaletteEditor.cpp", frmPaletteEditor);
USEFORM("FormText.cpp", frmText);
USEFORM("FormEditBounds.cpp", frmEditBounds);
USEFORM("FormColourDialog.cpp", frmColourDialog);
USEFORM("FormAnimate.cpp", frmAnimate);
USEFORM("FormAbout.cpp", frmAbout);
USEFORM("main.cpp", frmMain);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Carbon");
		Application->CreateForm(__classid(TfrmMain), &frmMain);
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
