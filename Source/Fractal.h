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
#include "Palette.h"
#include "ProjectHistory.h"


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
	long double e = 0;

	void Set(long double _n_coeff, long double _max_iterations, long double _bailout_radius,
			 long double _a, long double _b, long double _c, long double _d, long double _e)
	{
		n_coeff = _n_coeff;
		max_iterations = _max_iterations;
		bailout_radius = _bailout_radius;

		a = _a;
		b = _b;
		c = _c;
		d = _d;
        e = _e;
	}
};


struct Variables
{
	long double a = 0;
	long double b = 0;
	long double c = 0;
	long double d = 0;
	long double e = 0;

	long double morph_a = 0.0001;
	long double morph_b = 0.0001;
};


class Fractal
{
	static const int __PreviewWidth = 200;
	static const int __PreviewHeight = 200;

protected:

	static const int __RMJuliaEscapeTime = 0;
	static const int __RMJuliaDistance = 1;
	static const int __RMJuliaDistanceOrigin = 2;
	static const int __RMJuliaTwoTone = 3;
	static const int __RMJuliaThreeTone = 4;
	static const int __RMJuliaFourTone = 5;
	static const int __RMJuliaFiveTone = 6;
	static const int __RMJuliaContinuous = 7;

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

	std::chrono::system_clock::time_point StartTime;

	int HasChanged = true;

	void SwapDimensions();

	void CalculateRenderTime();

	void ClearFractalDataA(int);

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

    int maxdim = 0;

	Variables Var;

	Palette *pp;    // main colour palette
	Palette *pp2;   // secondary palette for background (etc.)

	int AcceptsABCSpectificRenderModeBegin = -1;
	int AcceptsABCSpectificRenderModeEnd = -1;
	bool AcceptsABC = false;
	bool AcceptsMorph = false;
	bool AcceptsVarA = false;
	bool AcceptsVarB = false;
	bool AcceptsVarC = false;
	bool AcceptsVarD = false;
	bool AcceptsVarE = false;

	bool AcceptsZoom = true;

	bool MultiThread = false;

    int MorphType = 0;          // linear, radial (screen), radial (fractal)
	bool MorphA = false;
	bool MorphB = false;

	QuickParameterMode QPM = QuickParameterMode::kNone;

	std::wstring NameA = L"";
	std::wstring NameB = L"";
	std::wstring NameC = L"";
	std::wstring NameD = L"";
	std::wstring NameE = L"";

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

	virtual bool MultiThreadRender(bool, bool, bool);
	virtual void PreRender(bool);
	virtual void Render(int, int);
	virtual void RenderMorph(int, int);
	virtual void RenderSS(int, int);
	virtual void RenderSSMorph(int, int);

	void MT();
	void MTMorph();
	void MTSS();
	void MTSSMorph();

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

	void SetABC(long double, long double, long double, long double, long double);
    void SetMorph(int, bool, bool, long double, long double);
	bool ShowABC(int);

	void SetPaletteInfinity(Colour);

	virtual std::wstring GetParameters();

	void CopyImage();
	void MergeImage();

	bool AttemptRecolour();

	void FinaliseRenderDragon(TBitmap*);
	void FinaliseRenderJulia(TBitmap*);
	void FinaliseRenderMandelbrot(TBitmap*);
	void FinaliseRenderMartin(TBitmap*);

    void SetFromProjectHistory(ProjectHistory);
	ProjectHistory GetAsProject(int);

	virtual std::wstring Description();
    virtual std::wstring HistoryEntry();

	virtual void ToFile(std::ofstream&);
};
