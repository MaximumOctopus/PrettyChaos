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


class Fractal
{

protected:

	std::chrono::system_clock::time_point StartTime;

	int HasChanged = true;

	void CalculateRenderTime();

	int LinearInterpolate(int, int, double);

public:

	#ifdef _DEBUG
	std::wstring debug = L"";
	#endif

    double n_coeff = 1;  // used to map the linear range of palette colours to an exponential range (very cool)
	double max_iterations = 1000;
    double bailout_radius = 256;

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

};
