//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once


#include <chrono>
#include <vector>


struct Variables
{
	double a = 0;
	double b = 0;
	double c = 0;
};


class Fractal
{

protected:

	int* NumIterationsPerPixel = nullptr;

	std::chrono::system_clock::time_point StartTime;

	int HasChanged = true;

	void CalculateRenderTime();

	int LinearInterpolate(int, int, double);

	double Sign(double);

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

	bool AcceptsABC = false;
	bool AcceptsVarA = false;
	bool AcceptsVarB = false;
	bool AcceptsVarC = false;

	int Palette[500];
	int PaletteInfinity = 0x000000;

	int RenderMode = 0;

	std::wstring RenderTime = L"0";

	int* Canvas = nullptr;
	int* Iteration = nullptr;
	double* Distances = nullptr;

	double ymin = 0;    // fractal objects must set these in their constructor
	double ymax = 0;    //
	double xmin = 0;    //
	double xmax = 0;    //

	int Width = 0;
    int Height = 0;

	Fractal();

	~Fractal();

	virtual void Render();
    virtual void Preview();

	virtual void ResetView();

	void SetView(double, double, double, double);
	void FitToView(double, double, double, double);
    void ZoomAtPoint(double, double);

	void SetDimensions(int, int);
	void SetParameters(double, int, int);
	void SetRenderMode(int);

	void SetABC(double, double, double);
};
