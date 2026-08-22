//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2026
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
    int BoundaryTest = 0;
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

	bool MorphEnabled = false;

    int MorphType = 0;
	bool MorphA = false;
	bool MorphB = false;

	long double morph_var_a = 0;
    long double morph_var_b = 0;

    std::wstring ProjectFileName = L"";
	std::wstring PaletteFileName = L"";
	std::wstring Palette2FileName = L"";
};


class ProjectIO
{
	enum class FileProperty {
		None = 0, Name, Width, Height, RenderMode, BoundaryTest, nCoeff,
		MaxIterations, BailoutRadius,
		xmin, xmax, ymin, ymax,
		var_a, var_b, var_c, var_d, var_e,
		Steps,
		DeltaA, DeltaB, DeltaC, DeltaD, DeltaE,
		Parameters, Zoom, Prefix,
		PaletteFileName, BackgroundPaletteFileName, GradientDirection, IsGradient,
		SuperSampling, SuperSamplingLevel,
		MorphEnabled, MorphA, MorphB,
		MorphVarA, MorphVarB, MorphType,
		DrawMode, GridWidth, GridColour1, GridColour2
	};

	static const int kPropertyListCount = 42;

	const std::wstring FilePropertyList[kPropertyListCount] = {
		L"Name", L"Width", L"Height", L"RenderMode", L"BoundaryTest", L"nCoeff",
		L"MaxIterations", L"BailoutRadius",
		L"xmin", L"xmax", L"ymin", L"ymax",
		L"var_a", L"var_b", L"var_c", L"var_d", L"var_e",
		L"Steps",
		L"DeltaA", L"DeltaB", L"DeltaC", L"DeltaD", L"DeltaE",
		L"Parameters", L"Zoom", L"Prefix",
		L"Palette", L"Palette2", L"GradientDirection", L"IsGradient",
		L"SS", L"SSLevel",
		L"Morph", L"MorphA", L"MorphB",
		L"var_morph_a", L"var_morph_b", L"MorphType",
		L"DrawMode", L"GridWidth", L"GridColour1", L"GridColour2"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::Name, FileProperty::Width, FileProperty::Height, FileProperty::RenderMode, FileProperty::BoundaryTest, FileProperty::nCoeff,
		FileProperty::MaxIterations, FileProperty::BailoutRadius,
		FileProperty::xmin, FileProperty::xmax, FileProperty::ymin, FileProperty::ymax,
		FileProperty::var_a, FileProperty::var_b, FileProperty::var_c, FileProperty::var_d, FileProperty::var_e,
		FileProperty::Steps,
		FileProperty::DeltaA, FileProperty::DeltaB, FileProperty::DeltaC, FileProperty::DeltaD, FileProperty::DeltaE,
		FileProperty::Parameters, FileProperty::Zoom, FileProperty::Prefix,
		FileProperty::PaletteFileName, FileProperty::BackgroundPaletteFileName, FileProperty::GradientDirection, FileProperty::IsGradient,
		FileProperty::SuperSampling, FileProperty::SuperSamplingLevel,
		FileProperty::MorphEnabled, FileProperty::MorphA, FileProperty::MorphB,
		FileProperty::MorphVarA, FileProperty::MorphVarB, FileProperty::MorphType,
		FileProperty::DrawMode, FileProperty::GridWidth, FileProperty::GridColour1, FileProperty::GridColour2
	};

	FileProperty GetInputProperty(const std::wstring);

public:

	ProjectIO();

	bool Load(const std::wstring, PCProject&, Animation&);

	bool Save(const std::wstring, PCProject&, Animation&);
};
