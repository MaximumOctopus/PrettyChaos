//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include "HistoryHandler.h"


HistoryHandler::HistoryHandler()
{

}


void HistoryHandler::Add(double _xmin, double _xmax, double _ymin, double _ymax)
{
	ZoomHistory zh(_xmin, _xmax, _ymin, _ymax);

    History.push_back(zh);
}
