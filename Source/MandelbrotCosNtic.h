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

#include <thread>

#include "Fractal.h"
#include "MandelbrotRenderCore.h"


class MandelbrotCosNtic : public Fractal
{
	void OrbitTrap(bool);

public:

	MandelbrotCosNtic();

	~MandelbrotCosNtic();

	bool MultiThreadRender(bool, bool) override;
	void Render(int, int) override;
	void RenderSS(int, int) override;

	void ResetView() override;

	std::wstring GetParameters() override;

    std::wstring Description() override;

    void ToFile(std::ofstream&) override;
};
