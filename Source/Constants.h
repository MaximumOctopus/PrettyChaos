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

#include <string>

#ifdef _DEBUG
static const std::wstring __PrettyChaosVersion = L"0.22 (debug) :: June 29th 2025";
#else
static const std::wstring __PrettyChaosVersion = L"0.22 :: June 29th 2025";
#endif

static const std::wstring __AutoSaveTemplate = L"Images\\$yyyy$mm$dd_$Th$Tm$Ts.png";

static const int DimensionsDesktop[17][2] = {
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
	{ 3440, 1440 },
	{ 3840, 2160 }};

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

static const int DimensionsTexture[6] =	{ 128, 256, 512, 1024, 2048, 4096 };

static const double JuliaSetExamples[28][2] = {
	{ -0.79, 0.15 },
	{ -0.162, 1.04 },
	{ 0.3, -0.01 },
	{ -1.476, 0 },
	{ -0.12, -0.77 },
	{ 0.28, 0.008 },
	{ 0, 0.8 },
	{ 0.37, 0.1 },
	{ 0.355, 0.355 },
	{ -0.54, 0.54 },
	{ -0.4, -0.59 },
	{ 0.34, -0.05 },
	{ 0.355534, 0.337292 },
	{ -0.162, 1.04 },
	{ -0.79, 0.15 },
	{ 0.33, 0.008 },
	{ -0.74543, 0.11301 },
	{ -0.8, 0.156 },
	{ 0.26, 0.54 },
	{ -1.04, 0.04 },
	{ -1.135, 0.2475 },
	{ -1.1825, 0.3175 },
	{ -0.72, -0.3275 },
	{ -1.17675, 0.645 },
	{ -1, 0 },
	{ 0.3, 0.6 },
	{ 0.8, 0.156 },
	{ 0.2793, -0.01 } };

static const double JuliaCubicExamples[10][2] = {
	{ -1.5855, 0.6877 },
	{ 0.859, 0.7157 },
	{ -0.748, -1.309 },
	{ -0.349, 1.291 },
	{ -1.249, 1.092 },
	{ -1.659, 0.6807 },
	{ -1.659, 0.5807 },
	{ -0.789, -1.3163 },
	{ -0.394, -1.2243 },
	{ -1.6, 0.7061 } };


static const double MartinExamples[8][3] = {
	{ 68, 75, 83 },
	{ 90, 30, 10 },
	{ 10, -10, 100 },
	{ -200, -4, -80 },
	{ -137, 17, -4 },
	{ 10, 100, -10 },
	{ -137, 17, 4 },
	{ 12, 18, 256 } };
