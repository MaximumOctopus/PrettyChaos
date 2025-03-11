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

#include "Fractal.h"


class FractalHandler
{

public:

	std::vector<Fractal*> Fractals;

	std::vector<std::wstring> Names;

	FractalHandler();
    ~FractalHandler();
};
