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

#include <vector>

#include "ProjectHistory.h"

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
	enum class FileProperty {
		None = 0, ObjectOpen = 1, ObjectClose = 2,
		Index = 3, Description = 4,
		nCoeff = 5,	MaxIterations = 6, BailoutRadius = 7,
		xmin = 8, xmax = 9, ymin = 10, ymax = 11,
		VarA = 12, VarB = 13, VarC = 14, VarD = 15, VarE = 16
	};

	static const int kPropertyListCount = 16;

	const std::wstring FilePropertyList[kPropertyListCount] = {
		L"[", L"]", L"index", L"description",
		L"nCoeff",	L"MaxIterations", L"BailoutRadius",
		L"xmin", L"xmax", L"ymin", L"ymax",
		L"var_a", L"var_b", L"var_c", L"var_d", L"var_e"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::ObjectOpen, FileProperty::ObjectClose, FileProperty::Index, FileProperty::Description,
		FileProperty::nCoeff, FileProperty::MaxIterations, FileProperty::BailoutRadius,
		FileProperty::xmin, FileProperty::xmax, FileProperty::ymin, FileProperty::ymax,
		FileProperty::VarA, FileProperty::VarB, FileProperty::VarC, FileProperty::VarD, FileProperty::VarE
	};

	FileProperty GetInputProperty(const std::wstring);

public:

	std::vector<ZoomHistory> Zoom;

	std::vector<ProjectHistory> Projects;

	HistoryHandler();

	void AddZoom(double, double, double, double);

	void AddProject(ProjectHistory);
	void AddProject(int _fractal, double _xmin, double _xmax, double _ymin, double _ymax,
					double _VarA, double _VarB, double _VarC, double _VarD, double _VarE,
					double _Coeff, double _MaxIterations, double _Bailout);

	bool Load(const std::wstring);
	bool Save(const std::wstring);
};
