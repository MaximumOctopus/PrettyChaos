

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

USEFORM("main.cpp", frmMain);
USEFORM("PaletteEditor.cpp", frmPaletteEditor);
USEFORM("FormColourDialog.cpp", frmColourDialog);
USEFORM("FormEditBounds.cpp", frmEditBounds);
USEFORM("FormAbout.cpp", frmAbout);
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
