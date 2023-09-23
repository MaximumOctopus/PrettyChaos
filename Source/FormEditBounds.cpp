

#include <vcl.h>
#pragma hdrstop

#include "FormEditBounds.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmEditBounds *frmEditBounds;


__fastcall TfrmEditBounds::TfrmEditBounds(TComponent* Owner)
	: TForm(Owner)
{

}


void __fastcall TfrmEditBounds::FormShow(TObject *Sender)
{
	eXMin->Text = xmin;
	eXMax->Text = xmax;
	eYMin->Text = ymin;
	eYMax->Text = ymax;
}


void TfrmEditBounds::SetBoundsValues(int _width, int _height, double _xmin, double _xmax, double _ymin, double _ymax)
{
	fwidth = _width;
    fheight = _height;

	xmin = _xmin;
	xmax = _xmax;
	ymin = _ymin;
	ymax = _ymax;
}


void __fastcall TfrmEditBounds::bOKClick(TObject *Sender)
{
	xmin = eXMin->Text.ToDouble();
	ymax = eXMax->Text.ToDouble();
	xmin = eYMin->Text.ToDouble();
	ymax = eYMax->Text.ToDouble();

	if (rbAutoFitting->Checked)
	{
		if (fwidth > fheight || fwidth == fheight)
		{
			double c_yaxis = ymin + ((ymax - ymin) / 2); // centre point of y-axis

			double x_coeff = (xmax - xmin) / (double)fwidth;

			double y_range = x_coeff / (1 / (double)fheight);      // gets new y range

			ymin = c_yaxis - (y_range / 2);
			ymax = c_yaxis + (y_range / 2);
		}
		else
		{
			double c_xaxis = xmin + ((xmax - xmin) / 2); // centre point of x-axis

			double y_coeff = (ymax - ymin) / (double)fheight;

			double x_range = y_coeff / (1 / (double)fwidth);      // gets new y range

			xmin = c_xaxis - (x_range / 2);
			xmax = c_xaxis + (x_range / 2);
		}
	}
}
