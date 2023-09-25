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
	void ColourTwoTone();
	void ColourThreeTone();
	void ColourDistanceII(double);

public:

	JuliaCubic();

	~JuliaCubic();

	void Render() override;

    void ResetView() override;
};
