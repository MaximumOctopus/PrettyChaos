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

#include <string>

#ifdef _DEBUG
static const std::wstring __PrettyChaosVersion = L"0.2 (debug) :: September 23rd 2023";
#else
static const std::wstring __PrettyChaosVersion = L"0.2 :: September 23rd 2023";
#endif


static const int DimensionsDesktop[16][2] = {
	{ 1024, 768 },
	{ 1280, 720 },
	{ 1280, 800 },
	{ 1280, 1024 },
	{ 1360, 768 },
	{ 1366, 768 },
	{ 1440, 900 },
	{ 1600, 900 },
	{ 1680, 1050 },
	{ 1920, 1200 },
	{ 1920, 1080 },
	{ 2560, 1440 },
	{ 2560, 1080 },
	{ 2560, 1600 },
	{ 2880, 1800 },
	{ 3440, 1440 }};

static const int DimensionsPhone[12][2] = {
	{ 828, 1792 },
	{ 1125, 2436 },
	{ 1242, 2688 },
	{ 750,  1334 },
	{ 1170, 2532 },
	{ 1125, 2436 },
	{ 1170, 2532 },
	{ 1284, 2778 },
	{ 1170, 2532 },
	{ 1080, 2340 },
	{ 1170, 2532 },
	{ 1284, 2778 } };
