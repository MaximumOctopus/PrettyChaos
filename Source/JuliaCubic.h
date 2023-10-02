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


class JuliaCubic : public Fractal
{
	static const int __RMEscapeTime = 0;
	static const int __RMContinuous = 1;
	static const int __RMDistance = 2;
	static const int __RMDistanceOrigin = 3;
	static const int __RMTwoTone = 4;
	static const int __RMThreeTone = 5;
	static const int __RMFourTone = 6;
	static const int __RMFiveTone = 7;

	void ColourNTone(int);
	void ColourDistanceII(double);

public:

	JuliaCubic();

	~JuliaCubic();

	void Render() override;

	void ResetView() override;

    void ToFile(std::ofstream&) override;
};
