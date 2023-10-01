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