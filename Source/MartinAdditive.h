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


class MartinAdditive : public Fractal
{
	static const int __RMAverage = 0;
	static const int __RMTime = 1;
	static const int __RMDistance = 2;

public:

	MartinAdditive();

	~MartinAdditive();

	void Render() override;

	void ResetView() override;

    void ToFile(std::ofstream&) override;
};
