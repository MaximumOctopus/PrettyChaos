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


class Dragon : public Fractal
{
	static const int __RMAverage = 0;
	static const int __RMTime = 1;
	static const int __RMDistance = 2;

	static const int __North = 0;
	static const int __East = 1;
	static const int __South = 2;
	static const int __West = 3;

	static constexpr int __Move[] = { 0, 0, 1, -1, 1, -1, 1, 0 };

	void Generate(int);

    void DrawLine(int, int, int, int, int);

    std::wstring generator;

public:

	Dragon();

	~Dragon();

	void Render(int, int) override;

	void ResetView() override;

    void ToFile(std::ofstream&) override;
};
