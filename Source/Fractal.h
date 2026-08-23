//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2026
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
#include "ColourUtility.h"
#include "Fast.h"
#include "Formatting.h"
#include "Palette.h"
#include "ProjectHistory.h"


enum class QuickParameterMode { kNone = 0, kABPlusFine = 1, kABC };


struct RenderModeParameters
{
	std::wstring Name = L"";

	bool AcceptsParameters = false;

	bool AcceptsVarA = false;
	bool AcceptsVarB = false;
	bool AcceptsVarC = false;
	bool AcceptsVarD = false;
	bool AcceptsVarE = false;

	std::wstring VarAName = L"";
	std::wstring VarBName = L"";
	std::wstring VarCName = L"";
	std::wstring VarDName = L"";
	std::wstring VarEName = L"";

	RenderModeParameters(const std::wstring n,
			             const std::wstring n_a, const std::wstring n_b, const std::wstring n_c, const std::wstring n_d, const std::wstring n_e)
	{
		Name = n;

		AcceptsVarA = !n_a.empty();
		AcceptsVarB = !n_b.empty();
		AcceptsVarC = !n_c.empty();
		AcceptsVarD = !n_d.empty();
		AcceptsVarE = !n_e.empty();

		VarAName = n_a;
		VarBName = n_b;
		VarCName = n_c;
		VarDName = n_d;
		VarEName = n_e;

		AcceptsParameters = (AcceptsVarA || AcceptsVarB || AcceptsVarC || AcceptsVarD || AcceptsVarE);
	}
};


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
	static const int __RMJuliaXOR = 7;
	static const int __RMJuliaContinuous = 8;

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
	static const int __RMMandelbrotXOR = 10;
	static const int __RMMandelbrotXOR2 = 11;
	static const int __RMMandelbrotXOR3 = 12;
    static const int __RMMandelbrotTest = 13;

	static const int __RMMartinAverage = 0;
	static const int __RMMartinTime = 1;
	static const int __RMMartinDistance = 2;

	int* NumIterationsPerPixel = nullptr;

	std::chrono::system_clock::time_point StartTime;

	int HasChanged = true;

	void SwapDimensions();
	void CreateRenderCanvases();

	void CalculateRenderTime();

	void ClearFractalDataA(int);

	double Sign(long double);

	void ResetConfig();

	void ColourDistanceI(TBitmap* canvas, long double);
	void ColourDistanceII(TBitmap* canvas, long double);
	void ColourNTone(TBitmap* canvas, int);
	void OrbitTrap(TBitmap* canvas, bool);

	void ColourNToneThread(TBitmap*, int, int, int);

	void JuliaThreadEscapeTime(TBitmap *, int, int, int, int);

	void MandelbrotThreadEscapeTime(TBitmap *, int, int, int);
	void MandelbrotThreadFastEscape(TBitmap *, int, int);
	void MandelbrotThreadContinuous(TBitmap *, int, int);
	void MandelbrotThreadXOR(TBitmap *);

	void OrbitTrapThreadNonFilled(TBitmap *, int, int, double);
	void OrbitTrapThreadFilled(TBitmap *, int, int, double);

public:

	#ifdef _DEBUG
	std::wstring debug = L"";
	#endif

	std::vector<std::wstring> Tests;
	bool HasTests = false;
	int CurrentTest = 0;

	std::vector<RenderModeParameters> Parameters;
	std::wstring Name = L"";

	std::wstring MorphNameA = L"";
	std::wstring MorphNameB = L"";

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

	bool AcceptsMorph = false;
	bool AcceptsZoom = true;

	bool MultiThread = false;

    int MorphType = 0;          // linear, radial (screen), radial (fractal)
	bool MorphA = false;
	bool MorphB = false;

	QuickParameterMode QPM = QuickParameterMode::kNone;

	int RenderMode = 0;

	std::wstring RenderTime = L"0";

	Colour* FractalData = nullptr;
	long double* Data = nullptr;

	TBitmap *RenderCanvas = nullptr;
	TBitmap *rc1 = nullptr;
	TBitmap *rc2 = nullptr;
	TBitmap *rc3 = nullptr;
	TBitmap *rc4 = nullptr;
	TBitmap *rc5 = nullptr;
    TBitmap *PreviewCanvas = nullptr;
	TBitmap *CopyCanvas = nullptr;

    Colour* colours;

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


#pragma region Inline_Test_Functions
inline bool JuliaTest(long double p, long double q)
{
	switch (CurrentTest)
	{
	case 0:
		return p * p + q * q < bailout_radius;
	case 1:
		return abs(abs(p) - abs(q)) < bailout_radius;
	case 2:
		return abs(abs(p * p) - abs(q * q)) < bailout_radius;
	case 3:
		return p * p * q * q < bailout_radius;
	case 4:
		return abs(abs(p) + abs(q)) < bailout_radius;
	}

	return true;
}


inline bool MandelbrotTest(long double x1, long double y1, long double x2, long double y2)
{
	switch (CurrentTest)
	{
	case 0:
		return x2 + y2 < bailout_radius;
	case 1:
		return abs(abs(x1) - abs(y1)) < bailout_radius;
	case 2:
		return abs(x2 - y2) < bailout_radius;
	case 3:
		return x2 * y2 < bailout_radius;
	case 4:
		return abs(abs(x1) + abs(y1)) < bailout_radius;
	}

	return true;
}
#pragma end_region


#pragma region Inline_Colouring_Functions
inline void MandelbrotColourise(int it, int ydotwidthplusx,
	long double x1, long double y1,
	long double x2, long double y2,
	long double p, long double q)
{
	switch (RenderMode)
	{
	case __RMMandelbrotEscapeTime:
	case __RMMandelbrotOrbitTrap:
	case __RMMandelbrotOrbitTrapFilled:
	case __RMMandelbrotTwoTone:
	case __RMMandelbrotThreeTone:
	case __RMMandelbrotFourTone:
	case __RMMandelbrotFiveTone:
	case __RMMandelbrotTest:
		FractalData[ydotwidthplusx].a = it;
		break;
	case __RMMandelbrotContinuous:
	{
		if (it < max_iterations)
		{
			long double log_zn = std::log(x2 + y2) / 0.60205999132796239042747778944899;    // 2 * log(2)
			long double nu = 1 - std::log2(log_zn);

			long double itnew = it + nu;

			it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
			long double it_d = (long double)it + nu;

			FractalData[ydotwidthplusx] = ColourUtility::LinearInterpolate(pp->Colours[it],
																		   pp->Colours[it + 1],
																		   it_d - (std::floorl(it_d)));
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}

		break;
	}
	case __RMMandelbrotDistance:
	{
		if (it < max_iterations)
		{
			Data[ydotwidthplusx] = std::sqrt((x1 + y1) * (x1 + y1));
		}

		FractalData[ydotwidthplusx].a = it;
		break;
	}
	case __RMMandelbrotDistanceII:
	{
		if (it < max_iterations)
		{
			Data[ydotwidthplusx] = std::sqrt(x2 + y2 * x2 + y2);
		}

		FractalData[ydotwidthplusx].a = it;
		break;
	}
	case __RMMandelbrotXOR:
		if (it < max_iterations)
		{
			long double ldi = Var.d * abs(q - y1);
			long double ldc = Var.d * abs(p - x1);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a = ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	case __RMMandelbrotXOR2:
		if (it < max_iterations)
		{
			long double ldi = Var.d * abs(x2);
			long double ldc = Var.d * abs(y2);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a = ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	case __RMMandelbrotXOR3:
		if (it < max_iterations)
		{
			long double w = (x1 + y1) * (x1 + y1);

			long double ldi = Var.d * abs(w - x2);
			long double ldc = Var.d * abs(w - y2);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a = ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	}
}


inline void MandelbrotColouriseSS(int it, int ydotwidthplusx,
	long double x1, long double y1,
	long double x2, long double y2,
	long double p, long double q)
{
	switch (RenderMode)
	{
	case __RMMandelbrotEscapeTime:
	case __RMMandelbrotOrbitTrap:
	case __RMMandelbrotOrbitTrapFilled:
	case __RMMandelbrotTwoTone:
	case __RMMandelbrotThreeTone:
	case __RMMandelbrotFourTone:
	case __RMMandelbrotFiveTone:
	case __RMMandelbrotTest:
	{
		FractalData[ydotwidthplusx].a += it;
		break;
	}
	case __RMMandelbrotContinuous:
	{
		if (it < max_iterations)
		{
			long double log_zn = std::log(x2 + y2) / 0.60205999132796239042747778944899;    // 2 * log(2)
			long double nu = 1 - std::log2(log_zn);

			long double itnew = it + nu;

			it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
			long double it_d = (long double)it + nu;

			FractalData[ydotwidthplusx] += ColourUtility::LinearInterpolate(pp->Colours[it],
																		   pp->Colours[it + 1],
																		   it_d - (std::floorl(it_d)));
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}

		break;
	}
	case __RMMandelbrotDistance:
	{
		if (it < max_iterations)
		{
			Data[ydotwidthplusx] = std::sqrt((x1 + y1) * (x1 + y1));
		}

		FractalData[ydotwidthplusx].a += it;
		break;
	}
	case __RMMandelbrotDistanceII:
	{
		if (it < max_iterations)
		{
			Data[ydotwidthplusx] = std::sqrt(x2 + y2 * x2 + y2);
		}

		FractalData[ydotwidthplusx].a += it;
		break;
	}
case __RMMandelbrotXOR:
		if (it < max_iterations)
		{
			long double ldi = Var.d * abs(q - y1);
			long double ldc = Var.d * abs(p - x1);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a += ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	case __RMMandelbrotXOR2:
		if (it < max_iterations)
		{
			long double ldi = Var.d * abs(x2);
			long double ldc = Var.d * abs(y2);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a += ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	case __RMMandelbrotXOR3:
		if (it < max_iterations)
		{
			long double w = (x1 + y1) * (x1 + y1);

			long double ldi = Var.d * abs(w - x2);
			long double ldc = Var.d * abs(w - y2);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a += ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	}
}


inline void JuliaColourise(int it, int ydotwidthplusx,
		int x, int y,
		long double p, long double q)
{
	switch (RenderMode)
	{
	case __RMJuliaEscapeTime:
	case __RMJuliaTwoTone:
	case __RMJuliaThreeTone:
	case __RMJuliaFourTone:
	case __RMJuliaFiveTone:
	{
		FractalData[ydotwidthplusx].a = it;
		break;
	}
	case __RMJuliaDistance:
	{
		Data[ydotwidthplusx] = std::sqrt((p + q) * (p + q));

		FractalData[ydotwidthplusx].a = it;

		break;
	}
	case __RMJuliaDistanceOrigin:
	{
		int nx = Fast::Floor(x - (Width / 2));
		int ny = Fast::Floor(y - (Height / 2));

		int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

		FractalData[ydotwidthplusx] = pp->Colours[index];
		break;
	}
	case __RMJuliaXOR:
		if (it < max_iterations)
		{
			long double ldi = Var.d * abs(q - Var.b);
			long double ldc = Var.d * abs(p - Var.a);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a = ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	case __RMJuliaContinuous:
		if (it < max_iterations)
		{
			long double log_zn = std::log(p * p + q * q) / 0.60205999132796239042747778944899;    // 2 * log(2)
			long double nu = 1 - std::log2(log_zn);

			long double itnew = it + nu;

			it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
			long double it_d = (long double)it + nu;

			FractalData[ydotwidthplusx] = ColourUtility::LinearInterpolate(pp->Colours[it],
																		   pp->Colours[it + 1],
																		   it_d - (std::floorl(it_d)));
		}
		else
		{
			FractalData[ydotwidthplusx] = pp2->PatternLive.SingleColour;
		}

		break;
	}
}


inline void JuliaColouriseSS(int it, int ydotwidthplusx,
		int x, int y,
		long double p, long double q)
{
	switch (RenderMode)
	{
	case __RMJuliaEscapeTime:
	case __RMJuliaTwoTone:
	case __RMJuliaThreeTone:
	case __RMJuliaFourTone:
	case __RMJuliaFiveTone:
	{
		FractalData[ydotwidthplusx].a += it;
		break;
	}
	case __RMJuliaDistance:
	{
		Data[ydotwidthplusx] = std::sqrt((p + q) * (p + q));

		FractalData[ydotwidthplusx].a += it;
		break;
	}
	case __RMJuliaDistanceOrigin:
	{
		int nx = Fast::Floor(x - (Width / 2));
		int ny = Fast::Floor(y - (Height / 2));

		int index = Fast::Floor( ((std::sqrt(nx * nx + ny * ny) / maxdim) * std::pow((long double)it / max_iterations, n_coeff)) * pp->ColourCount);

		FractalData[ydotwidthplusx] += pp->Colours[index];
		break;
	}
	case __RMJuliaXOR:
		if (it < max_iterations)
		{
			long double ldi = Var.d * abs(q - Var.b);
			long double ldc = Var.d * abs(p - Var.a);

			int ldx = (int)ldi ^ (int)ldc;

			FractalData[ydotwidthplusx].a += ldx;
		}
		else
		{
			FractalData[ydotwidthplusx].a = -1;
		}
		break;
	case __RMJuliaContinuous:
	{
		if (it < max_iterations)
		{
			long double log_zn = std::log(p * p + q * q) / 0.60205999132796239042747778944899;    // 2 * log(2)
			long double nu = 1 - std::log2(log_zn);

			long double itnew = it + nu;

			it = std::pow((Fast::Floor(itnew) / max_iterations), n_coeff) * pp->ColourCount;
			long double it_d = (long double)it + nu;

			FractalData[ydotwidthplusx] += ColourUtility::LinearInterpolate(pp->Colours[it],
																			pp->Colours[it + 1],
																		    it_d - (std::floorl(it_d)));
		}
		else
		{
			FractalData[ydotwidthplusx] += pp2->PatternLive.SingleColour;
		}

		break;
	}
	}
}
#pragma end_region
};
