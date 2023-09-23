//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <string>


struct PCProject
{
	int Width = 0;
	int Height = 0;

	int RenderMode = 0;
	int nCoeff = 1;

	double MaxIterations = 1000;
	double BailoutRadius = 256;

	double xmin = 0;
	double xmax = 0;
	double ymin = 0;
	double ymax = 0;
};


class ProjectIO
{
	enum class FileProperty {
		None = 0, Width = 1, Height = 2, RenderMode = 3, nCoeff = 4,
		MaxIterations = 5, BailoutRadius = 6,
		xmin = 7, xmax = 8, ymin = 9, ymax = 10
	};

	static const int kPropertyListCount = 10;

	const std::wstring FilePropertyList[kPropertyListCount] = {
		L"Width", L"Height", L"RenderMode", L"nCoeff",
		L"MaxIterations", L"BailoutRadius",
		L"xmin", L"xmax", L"ymin", L"ymax"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::Width, FileProperty::Height, FileProperty::RenderMode, FileProperty::nCoeff,
		FileProperty::MaxIterations, FileProperty::BailoutRadius,
		FileProperty::xmin, FileProperty::xmax, FileProperty::ymin, FileProperty::ymax
	};

	FileProperty GetInputProperty(std::wstring);

public:

	ProjectIO();

	bool Load(std::wstring, PCProject&);

	bool Save(std::wstring, PCProject&);
};
