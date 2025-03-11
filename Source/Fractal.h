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

#include <Vcl.Graphics.hpp>

#include <chrono>
#include <fstream>
#include <vector>

#include "Colour.h"
#include "Formatting.h"


enum class QuickParameterMode { kNone = 0, kABPlusFine = 1, kABC };

struct DefaultConfig
{
	long double n_coeff = 1;  		// used to map the linear range of palette colours to an exponential range (very cool)
	long double max_iterations = 1000;
	long double bailout_radius = 4;

	long double a = 0;
	long double b = 0;
	long double c = 0;
	long double d = 0;

	void Set(long double _n_coeff, long double _max_iterations, long double _bailout_radius,
			 long double _a, long double _b, long double _c, long double _d)
	{
		n_coeff = _n_coeff;
		max_iterations = _max_iterations;
		bailout_radius = _bailout_radius;

		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}
};


struct Variables
{
	long double a = 0;
	long double b = 0;
	long double c = 0;
	long double d = 0;
};


class Fractal
{
	static const int __PreviewWidth = 200;
	static const int __PreviewHeight = 200;

protected:

	static const int __RMJuliaEscapeTime = 0;
	static const int __RMJuliaContinuous = 1;
	static const int __RMJuliaDistance = 2;
	static const int __RMJuliaDistanceOrigin = 3;
	static const int __RMJuliaTwoTone = 4;
	static const int __RMJuliaThreeTone = 5;
	static const int __RMJuliaFourTone = 6;
	static const int __RMJuliaFiveTone = 7;

	static const int __RMMandelbrotEscapeTime = 0;
	static const int __RMMandelbrotContinuous = 1;
	static const int __RMMandelbrotDistance = 2;
	static const int __RMMandelbrotDistanceII = 3;
	static const int __RMMandelbrotOrbitTrap = 4;
	static const int __RMMandelbrotOrbitTrapFilled = 5;
	static const int __RMMandelbrotTwoTone = 6;
	static const int __RMMandelbrotThreeTone = 7;
	static const int __RMMandelbrotFourTone = 8;
	static const int __RMMandelbrotFiveTone = 9;

	static const int __RMMartinAverage = 0;
	static const int __RMMartinTime = 1;
	static const int __RMMartinDistance = 2;

	int* NumIterationsPerPixel = nullptr;

	long double max_d = 0;

	std::chrono::system_clock::time_point StartTime;

	int HasChanged = true;

	void SwapDimensions();

	void CalculateRenderTime();

	void ClearFractalDataA();

	double Sign(long double);

	void ResetConfig();

	void ColourDistanceI(TBitmap* canvas, long double);
	void ColourDistanceII(TBitmap* canvas, long double);
	void ColourNTone(TBitmap* canvas, int);
	void OrbitTrap(TBitmap* canvas, bool);

public:

	#ifdef _DEBUG
	std::wstring debug = L"";
	#endif

	std::vector<std::wstring> RenderModes;
	std::wstring Name;

	DefaultConfig Defaults;

	long double n_coeff = 1;  		// used to map the linear range of palette colours to an exponential range (very cool)
	long double max_iterations = 1000;
	long double bailout_radius = 256;

	int supersamples = 8;
	int supersamplenormalistioncoefficient = 3; // log2(supersamples)

	Variables Var;

	Colour Palette[501];

	int AcceptsABCSpectificRenderModeBegin = -1;
	int AcceptsABCSpectificRenderModeEnd = -1;
	bool AcceptsABC = false;
	bool AcceptsVarA = false;
	bool AcceptsVarB = false;
	bool AcceptsVarC = false;
	bool AcceptsVarD = false;

	bool AcceptsZoom = true;

	bool MultiThread = false;

	QuickParameterMode QPM = QuickParameterMode::kNone;

	std::wstring NameA = L"";
	std::wstring NameB = L"";
	std::wstring NameC = L"";
	std::wstring NameD = L"";

	int RenderMode = 0;

	std::wstring RenderTime = L"0";

	Colour* FractalData = nullptr;
	long double* Data = nullptr;

	TBitmap *RenderCanvas = nullptr;
    TBitmap *PreviewCanvas = nullptr;
    TBitmap *CopyCanvas = nullptr;

	long double ymin = 0;    		// fractal objects must set these in their constructor
	long double ymax = 0;    		//
	long double xmin = 0;    		//
	long double xmax = 0;    		//
	long double x_resolution = 0;
	long double y_resolution = 0;

	int Width = 1280;
	int Height = 1024;

	int PreviewWidth = __PreviewWidth;
	int PreviewHeight = 160;

	Fractal();

	~Fractal();

	virtual bool MultiThreadRender(bool, bool);
	virtual void PreRender(bool);
	virtual void Render(int, int);
	virtual void RenderSS(int, int);

	virtual void ResetView();

    void ResetAll();

	bool PointGoesToInfinity(long double, long double);

	void SetView(long double, long double, long double, long double);
	void FitToView(long double, long double, long double, long double);
	void ZoomAtPoint(long double, long double);
	void ZoomOut();
	void CentreOnPoint(long double, long double);

	void SetDimensions(bool, int, int);
    void SetPreviewDimensions();
	void SetParameters(long double, int, int);
	void SetRenderMode(int);

	void SetABC(long double, long double, long double, long double);
	bool ShowABC(int);

	void SetPaletteInfinity(Colour);

	virtual std::wstring GetParameters();

	void CopyImage();
	void MergeImage();

	bool AttemptRecolour();

	void FinaliseRenderDragon(TBitmap*);
	void FinaliseRenderJulia(TBitmap*, double);
	void FinaliseRenderMandelbrot(TBitmap*, double);
	void FinaliseRenderMartin(TBitmap*);

    virtual std::wstring Description();

	virtual void ToFile(std::ofstream&);
};
