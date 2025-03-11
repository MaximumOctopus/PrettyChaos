//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include "HistoryHandler.h"


HistoryHandler::HistoryHandler()
{

}


void HistoryHandler::AddZoom(double _xmin, double _xmax, double _ymin, double _ymax)
{
	ZoomHistory zh(_xmin, _xmax, _ymin, _ymax);

	Zoom.push_back(zh);
}


void HistoryHandler::AddProject(int _fractal, double _xmin, double _xmax, double _ymin, double _ymax,
								double _VarA, double _VarB, double _VarC, double _VarD,
								double _Coeff, double _MaxIterations, double _Bailout)
{
	ProjectHistory zp(_fractal, _xmin, _xmax, _ymin, _ymax,
					  _VarA, _VarB, _VarC, _VarD,
				      _Coeff, _MaxIterations, _Bailout);

    Project.push_back(zp);
}
