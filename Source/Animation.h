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


#include "Utility.h"


struct Animation
{
    bool Configured = false;

	int Steps = 10;

	double DeltaA = 0;
	double DeltaB = 0;
	double DeltaC = 0;
    double DeltaD = 0;

	bool IncludeA = false;
	bool IncludeB = false;
	bool IncludeC = false;
	bool IncludeD = false;

	bool Parameters = false;
    bool Zoom = false;

	std::wstring Prefix = L"$yyyy$mm$dd_$Th$Tm$Ts_";

	std::wstring ParametersForFile(double a, double b, double c, double d)
	{
		std::wstring output = L"";

		if (IncludeA)
		{
			output += L"__" + std::to_wstring(a);
		}

		if (IncludeB)
		{
			output += L"__" + std::to_wstring(b);
		}

		if (IncludeC)
		{
			output += L"__" + std::to_wstring(c);
		}

		if (IncludeD)
		{
			output += L"__" + std::to_wstring(d);
		}

		return Utility::ReplaceString(output, L".", L"_");
	}
};
