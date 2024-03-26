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

#include <Vcl.Graphics.hpp>

#include <chrono>
#include <fstream>
#include <vector>


#include "Formatting.h"


struct Variables
{
	double a = 0;
	double b = 0;
	double c = 0;
    double d = 0;
};


class Fractal
{

protected:

	int PaletteInfintyR = 0;
	int PaletteInfintyG = 0;
	int PaletteInfintyB = 0;

	int* NumIterationsPerPixel = nullptr;

	std::chrono::system_clock::time_point StartTime;

	int HasChanged = true;

	void CalculateRenderTime();

	double Sign(double);

    void ColourDistanceI(double);
	void ColourDistanceII(double);
	void ColourNTone(int);

public:

	#ifdef _DEBUG
	std::wstring debug = L"";
	#endif

	std::vector<std::wstring> RenderModes;
	std::wstring Name;

	double n_coeff = 1;  // used to map the linear range of palette colours to an exponential range (very cool)
	double max_iterations = 1000;
	double bailout_radius = 256;

	Variables Var;

	int Palette[501];

	int AcceptsABCSpectificRenderModeBegin = -1;
	int AcceptsABCSpectificRenderModeEnd = -1;
	bool AcceptsABC = false;
	bool AcceptsVarA = false;
	bool AcceptsVarB = false;
	bool AcceptsVarC = false;
	bool AcceptsVarD = false;

	bool AcceptsZoom = true;

	bool MultiThread = false;
    int ThreadCount = 4;

	std::wstring NameA = L"";
	std::wstring NameB = L"";
	std::wstring NameC = L"";
	std::wstring NameD = L"";

	int RenderMode = 0;

	std::wstring RenderTime = L"0";

	int* Iteration = nullptr;
	double* Data = nullptr;

	TBitmap *RenderCanvas = nullptr;

	double ymin = 0;    // fractal objects must set these in their constructor
	double ymax = 0;    //
	double xmin = 0;    //
	double xmax = 0;    //
	double x_resolution = 0;
	double y_resolution = 0;

	int Width = 1280;
	int Height = 1024;

	Fractal();

	~Fractal();

	virtual void MultiThreadRender();
	virtual void Render(int, int);
    virtual void Preview();

	virtual void ResetView();

	void SetView(double, double, double, double);
	void FitToView(double, double, double, double);
    void ZoomAtPoint(double, double);

	void SetDimensions(int, int);
	void SetParameters(double, int, int);
	void SetRenderMode(int);

	void SetABC(double, double, double, double);
	bool ShowABC(int);

	void SetPaletteInfinity(int);

	virtual void ToFile(std::ofstream&);
};
