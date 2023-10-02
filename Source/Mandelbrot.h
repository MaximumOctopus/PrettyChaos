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


#include "Fractal.h"


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

	void ColourNTone(int);
	void ColourTwoTone();
	void ColourThreeTone();
	void ColourDistanceI(double);
	void ColourDistanceII(double);
	void OrbitTrap(bool);

public:

	Mandelbrot();

	~Mandelbrot();

	void Render() override;
    void Preview() override;

	void ResetView() override;

    void ToFile(std::ofstream&) override;
};