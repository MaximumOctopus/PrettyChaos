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


class Martin : public Fractal
{

public:

	Martin();

	~Martin();

	void Render() override;

	void ResetView() override;

    void ToFile(std::ofstream&) override;
};
