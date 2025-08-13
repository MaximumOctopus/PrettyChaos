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

#include "Animation.h"


struct PCProject
{
	std::wstring Name = L"";        // name of the fractal being generated

	int Width = 0;
	int Height = 0;

	int RenderMode = 0;
	bool SuperSampling = false;
    int SuperSamplingLevel = 8;
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
	long double var_e = 0;

    std::wstring ProjectFileName = L"";
	std::wstring PaletteFileName = L"";
	std::wstring Palette2FileName = L"";
};


class ProjectIO
{
	enum class FileProperty {
		None = 0, Name = 1, Width = 2, Height = 3, RenderMode = 4, nCoeff = 5,
		MaxIterations = 6, BailoutRadius = 7,
		xmin = 8, xmax = 9, ymin = 10, ymax = 11,
		var_a = 12, var_b = 13, var_c = 14, var_d = 15, var_e = 16,
		Steps = 17,
		DeltaA = 18, DeltaB = 19, DeltaC = 20, DeltaD = 21, DeltaE = 22,
		Parameters = 23, Zoom = 24, Prefix = 25,
		PaletteFileName = 26, BackgroundPaletteFileName = 27, GradientDirection = 28, IsGradient = 29,
		SuperSampling = 30, SuperSamplingLevel = 31
	};

	static const int kPropertyListCount = 31;

	const std::wstring FilePropertyList[kPropertyListCount] = {
		L"Name", L"Width", L"Height", L"RenderMode", L"nCoeff",
		L"MaxIterations", L"BailoutRadius",
		L"xmin", L"xmax", L"ymin", L"ymax",
		L"var_a", L"var_b", L"var_c", L"var_d", L"var_e",
		L"Steps",
		L"DeltaA", L"DeltaB", L"DeltaC", L"DeltaD", L"DeltaE",
		L"Parameters", L"Zoom", L"Prefix",
		L"Palette", L"Palette2", L"GradientDirection", L"IsGradient",
		L"SS", L"SSLevel"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::Name, FileProperty::Width, FileProperty::Height, FileProperty::RenderMode, FileProperty::nCoeff,
		FileProperty::MaxIterations, FileProperty::BailoutRadius,
		FileProperty::xmin, FileProperty::xmax, FileProperty::ymin, FileProperty::ymax,
		FileProperty::var_a, FileProperty::var_b, FileProperty::var_c, FileProperty::var_d, FileProperty::var_e,
		FileProperty::Steps,
		FileProperty::DeltaA, FileProperty::DeltaB, FileProperty::DeltaC, FileProperty::DeltaD, FileProperty::DeltaE,
		FileProperty::Parameters, FileProperty::Zoom, FileProperty::Prefix,
		FileProperty::PaletteFileName, FileProperty::BackgroundPaletteFileName, FileProperty::GradientDirection, FileProperty::IsGradient,
		FileProperty::SuperSampling, FileProperty::SuperSamplingLevel
	};

	FileProperty GetInputProperty(const std::wstring);

public:

	ProjectIO();

	bool Load(const std::wstring, PCProject&, Animation&);

	bool Save(const std::wstring, PCProject&, Animation&);
};
