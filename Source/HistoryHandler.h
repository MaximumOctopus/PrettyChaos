//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include <vector>


struct ZoomHistory
{
	double xmin, xmax, ymin, ymax;

	ZoomHistory(double a, double b, double c, double d)
	{
		xmin = a;
		xmax = b;
		ymin = c;
		ymax = d;
    }
};


class HistoryHandler
{
public:

    std::vector<ZoomHistory> History;

	HistoryHandler();

	void Add(double, double, double, double);
};
