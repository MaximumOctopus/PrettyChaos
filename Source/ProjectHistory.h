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


struct ProjectHistory
{
	int fractal = 0;
    std::wstring Description = L"";

	double xmin = 0;
	double xmax = 0;
	double ymin = 0;
	double ymax = 0;

	double VarA = 0;
	double VarB = 0;
	double VarC = 0;
	double VarD = 0;

	double Coeff = 0;
	double MaxIterations = 0;
	double Bailout  = 0;

	ProjectHistory(int _fractal, std::wstring _Description, double _xmin, double _xmax, double _ymin, double _ymax,
				   double _VarA, double _VarB, double _VarC, double _VarD,
				   double _Coeff, double _MaxIterations, double _Bailout)
	{
		fractal = _fractal;

        Description = _Description;

		xmin = _xmin;
		xmax = _xmax;
		ymin = _ymin;
		ymax = _ymax;

		VarA = _VarA;
		VarB = _VarB;
		VarC = _VarC;
		VarD = _VarD;

		Coeff = _Coeff;
		MaxIterations = _MaxIterations;
		Bailout  = _Bailout;
	}
};
