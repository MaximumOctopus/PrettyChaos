//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Julia_set

#pragma once


#include "Fractal.h"


class Julia : public Fractal
{
	static const int __RMEscapeTime = 0;
	static const int __RMContinuous = 1;
	static const int __RMDistance = 2;
	static const int __RMDistanceOrigin = 3;
	static const int __RMTwoTone = 4;
	static const int __RMThreeTone = 5;
	static const int __RMFourTone = 6;
	static const int __RMFiveTone = 7;

	double max_d = 0;

    void FinaliseRender();

public:

	Julia();

	~Julia();

	bool MultiThreadRender() override;
	void Render(int, int) override;

    void ResetAll() override;
	void ResetView() override;

   	void ToFile(std::ofstream&) override;
};
