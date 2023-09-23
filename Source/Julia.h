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


class Julia : public Fractal
{

public:

	Julia();

	~Julia();

	void Render() override;

    void ResetView() override;
};
