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

#include <string>

#include "Animation.h"


struct PCProject
{
	std::wstring Name = L"";        // name of the fractal being generated

	int Width = 0;
	int Height = 0;

	int RenderMode = 0;
	bool SuperSampling = false;
    bool SuperSamplingLevel = 8;
	double nCoeff = 1;

	long double MaxIterations = 1000;
	long double BailoutRadius = 256;

	long double xmin = 0;
	long double xmax = 0;
	long double ymin = 0;
	long double ymax = 0;

	long double var_a = 0;
	long double var_b = 0;
	long double var_c = 0;
	long double var_d = 0;

	std::wstring PaletteFileName = L"";
};


class ProjectIO
{
	enum class FileProperty {
		None = 0, Name = 1, Width = 2, Height = 3, RenderMode = 4, nCoeff = 5,
		MaxIterations = 6, BailoutRadius = 7,
		xmin = 8, xmax = 9, ymin = 10, ymax = 11,
		var_a = 12, var_b = 13, var_c = 14, var_d = 15,
		Steps = 20, DeltaA = 21, DeltaB = 22, DeltaC = 23, DeltaD = 24,
		Parameters = 25, Zoom = 26, Prefix = 27,
		PaletteFileName = 28,
		SuperSampling = 29, SuperSamplingLevel = 30
	};

	static const int kPropertyListCount = 26;

	const std::wstring FilePropertyList[kPropertyListCount] = {
		L"Name", L"Width", L"Height", L"RenderMode", L"nCoeff",
		L"MaxIterations", L"BailoutRadius",
		L"xmin", L"xmax", L"ymin", L"ymax",
		L"var_a", L"var_b", L"var_c", L"var_d",
		L"Steps", L"DeltaA", L"DeltaB", L"DeltaC", L"DeltaD",
		L"Parameters", L"Zoom", L"Prefix",
		L"Palette",
		L"SS", L"SSLevel"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::Name, FileProperty::Width, FileProperty::Height, FileProperty::RenderMode, FileProperty::nCoeff,
		FileProperty::MaxIterations, FileProperty::BailoutRadius,
		FileProperty::xmin, FileProperty::xmax, FileProperty::ymin, FileProperty::ymax,
		FileProperty::var_a, FileProperty::var_b, FileProperty::var_c, FileProperty::var_d,
		FileProperty::Steps, FileProperty::DeltaA, FileProperty::DeltaB, FileProperty::DeltaC, FileProperty::DeltaD,
		FileProperty::Parameters, FileProperty::Zoom, FileProperty::Prefix,
		FileProperty::PaletteFileName,
		FileProperty::SuperSampling, FileProperty::SuperSamplingLevel
	};

	FileProperty GetInputProperty(const std::wstring);

public:

	ProjectIO();

	bool Load(const std::wstring, PCProject&, Animation&);

	bool Save(const std::wstring, PCProject&, Animation&);
};
