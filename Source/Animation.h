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

struct Animation
{
    bool Configured = false;

	int Steps = 10;

	double DeltaA = 0;
	double DeltaB = 0;
	double DeltaC = 0;
    double DeltaD = 0;

	bool Parameters = false;
    bool Zoom = false;

    std::wstring Prefix = L"$yyyy$mm$dd_$Th$Tm$Ts_";
};
