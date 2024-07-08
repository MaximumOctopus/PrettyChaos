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

#include "Colour.h"
#include "Formatting.h"


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

	int* NumIterationsPerPixel = nullptr;

	std::chrono::system_clock::time_point StartTime;

	int HasChanged = true;

	void SwapDimensions();

	void CalculateRenderTime();

	double Sign(long double);

	void ColourDistanceI(long double);
	void ColourDistanceII(long double);
	void ColourNTone(int);

public:

	#ifdef _DEBUG
	std::wstring debug = L"";
	#endif

	std::vector<std::wstring> RenderModes;
	std::wstring Name;

	long double n_coeff = 1;  		// used to map the linear range of palette colours to an exponential range (very cool)
	long double max_iterations = 1000;
	long double bailout_radius = 256;

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
	int ThreadCount = 0;

	int QuickParamterMode = 0;  	// 0 = none, 1 = A+B + fine control, 2 = A+B+C

	std::wstring NameA = L"";
	std::wstring NameB = L"";
	std::wstring NameC = L"";
	std::wstring NameD = L"";

	int RenderMode = 0;

	std::wstring RenderTime = L"0";

	Colour* FractalData = nullptr;
	long double* Data = nullptr;

	TBitmap *RenderCanvas = nullptr;
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
    virtual void Preview();

	virtual void ResetAll();
	virtual void ResetView();

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

	void FinaliseRenderJulia(double);

    virtual std::wstring Description();

	virtual void ToFile(std::ofstream&);
};
