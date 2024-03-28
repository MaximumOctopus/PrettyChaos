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

#include <thread>

#include "Fractal.h"
#include "MandelbrotRenderCore.h"


class Mandelbrot : public Fractal
{
	static const int __RMEscapeTime = 0;
	static const int __RMContinuous = 1;
	static const int __RMDistance = 2;
	static const int __RMDistanceII = 3;
	static const int __RMOrbitTrap = 4;
	static const int __RMOrbitTrapFilled = 5;
	static const int __RMTwoTone = 6;
	static const int __RMThreeTone = 7;
	static const int __RMFourTone = 8;
	static const int __RMFiveTone = 9;

	void OrbitTrap(bool);

	double max_d = 0;

    void FinaliseRender();

public:

	Mandelbrot();

	~Mandelbrot();

	bool MultiThreadRender() override;
	void Render(int, int) override;
    void Preview() override;

    void ResetAll() override;
	void ResetView() override;

    std::wstring GetParameters() override;

    void ToFile(std::ofstream&) override;
};