//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

// https://en.wikipedia.org/wiki/Julia_set

#pragma once


#include "Fractal.h"


class JuliaCos : public Fractal
{

public:

	JuliaCos();

	~JuliaCos();

	bool MultiThreadRender(bool, bool) override;
	void Render(int, int) override;
	void RenderSS(int, int) override;

	void ResetView() override;

	std::wstring GetParameters() override;

	std::wstring Description() override;
	std::wstring HistoryEntry() override;

   	void ToFile(std::ofstream&) override;
};
