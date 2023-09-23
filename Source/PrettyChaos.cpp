

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

USEFORM("PaletteEditor.cpp", frmPaletteEditor);
USEFORM("main.cpp", frmMain);
USEFORM("FormEditBounds.cpp", frmEditBounds);
USEFORM("FormColourDialog.cpp", frmColourDialog);
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
