//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once


#include "Fractal.h"


class JuliaNtic : public Fractal
{

	long double max_d = 0;

public:

	JuliaNtic();

	~JuliaNtic();

	bool MultiThreadRender(bool, bool) override;
	void Render(int, int) override;
	void RenderSS(int, int) override;

    void ResetAll() override;
	void ResetView() override;

    std::wstring GetParameters() override;

    std::wstring Description() override;

    void ToFile(std::ofstream&) override;
};
