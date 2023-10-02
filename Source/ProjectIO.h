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
	std::wstring Name = L"";        // name of the fractal being generated

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

	double var_a = 0;
	double var_b = 0;
	double var_c = 0;
};


class ProjectIO
{
	enum class FileProperty {
		None = 0, Name = 1, Width = 2, Height = 3, RenderMode = 4, nCoeff = 5,
		MaxIterations = 6, BailoutRadius = 7,
		xmin = 8, xmax = 9, ymin = 10, ymax = 11,
		var_a = 12, var_b = 13, var_c = 14
	};

	static const int kPropertyListCount = 14;

	const std::wstring FilePropertyList[kPropertyListCount] = {
    	L"Name", L"Width", L"Height", L"RenderMode", L"nCoeff",
		L"MaxIterations", L"BailoutRadius",
		L"xmin", L"xmax", L"ymin", L"ymax",
		L"var_a", L"var_b", L"var_c"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::Name, FileProperty::Width, FileProperty::Height, FileProperty::RenderMode, FileProperty::nCoeff,
		FileProperty::MaxIterations, FileProperty::BailoutRadius,
		FileProperty::xmin, FileProperty::xmax, FileProperty::ymin, FileProperty::ymax,
        FileProperty::var_a, FileProperty::var_b, FileProperty::var_c
	};

	FileProperty GetInputProperty(std::wstring);

public:

	ProjectIO();

	bool Load(std::wstring, PCProject&);

	bool Save(std::wstring, PCProject&);
};
