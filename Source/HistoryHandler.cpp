//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <fstream>
#include <iomanip>

#include "Formatting.h"
#include "HistoryHandler.h"
#include "ProjectHistory.h"


HistoryHandler::HistoryHandler()
{

}


void HistoryHandler::AddZoom(double _xmin, double _xmax, double _ymin, double _ymax)
{
	ZoomHistory zh(_xmin, _xmax, _ymin, _ymax);

	Zoom.push_back(zh);
}


void HistoryHandler::AddProject(int _fractal, double _xmin, double _xmax, double _ymin, double _ymax,
								double _VarA, double _VarB, double _VarC, double _VarD, double _VarE,
								double _Coeff, double _MaxIterations, double _Bailout)
{
	ProjectHistory zp(_fractal, L"",
					  _xmin, _xmax, _ymin, _ymax,
					  _VarA, _VarB, _VarC, _VarD, _VarE,
				      _Coeff, _MaxIterations, _Bailout);

	Projects.push_back(zp);
}


void HistoryHandler::AddProject(ProjectHistory ph)
{
    Projects.push_back(ph);
}


bool HistoryHandler::Load(const std::wstring file_name)
{
	std::wifstream file(file_name);

	if (file)
	{
		std::wstring s(L"");

		int fractal = 0;
		std::wstring Description = L"";

		double xmin = 0;
		double xmax = 0;
		double ymin = 0;
		double ymax = 0;

		double var_a = 0;
		double var_b = 0;
		double var_c = 0;
		double var_d = 0;
		double var_e = 0;

		double Coeff = 0;
		double MaxIterations = 0;
		double BailoutRadius = 0;

		while (std::getline(file, s))
		{
			if (s != L"")
			{
				if (s[0] == L'/' || s[0] == L'#')
				{
					// comment, do nothing
				}
				else
				{
					auto equals = s.find(L'=');
					FileProperty PropertyName = FileProperty::None;

					std::wstring key = s.substr(0, equals);
					std::wstring value = s.substr(equals + 1);

					if (equals == std::wstring::npos)
					{
						key = s;
					}

					PropertyName = GetInputProperty(key);

					switch (PropertyName)
					{
					case FileProperty::None:
						//ShowMessage(key.c_str());
						break;
					case FileProperty::ObjectOpen:
						break;
					case FileProperty::ObjectClose:
					{
						ProjectHistory ph(fractal, Description, xmin, xmax, ymin, ymax,
										  var_a, var_b, var_c, var_d, var_e,
										  Coeff, MaxIterations, BailoutRadius);

						Projects.push_back(ph);
						break;
					}
                    case FileProperty::Index:
						fractal = stoi(value);
						break;
					case FileProperty::Description:
						Description = value;
						break;
					case FileProperty::nCoeff:
						Coeff = stod(value);
						break;
					case FileProperty::MaxIterations:
						MaxIterations = stoi(value);
						break;
					case FileProperty::BailoutRadius:
						BailoutRadius = stoi(value);
						break;
					case FileProperty::xmin:
						xmin = stod(value);
						break;
					case FileProperty::xmax:
						xmax = stod(value);
						break;
					case FileProperty::ymin:
						ymin = stod(value);
						break;
					case FileProperty::ymax:
						ymax = stod(value);
						break;
					case FileProperty::VarA:
						var_a = stod(value);
						break;
					case FileProperty::VarB:
						var_b = stod(value);
						break;
					case FileProperty::VarC:
						var_c = stod(value);
						break;
					case FileProperty::VarD:
						var_d = stod(value);
						break;
					case FileProperty::VarE:
						var_e = stod(value);
						break;
					}
				}
			}
		}

        file.close();

        return true;
	}

	return false;
}


bool HistoryHandler::Save(const std::wstring file_name)
{
	std::ofstream file(file_name);

	if (file)
	{
		for (int t = 0; t < Projects.size(); t++)
		{
			file << Formatting::to_utf8(L"[0\n");

			file << Formatting::to_utf8(L"index=" + std::to_wstring(Projects[t].fractal) + L"\n");
			file << Formatting::to_utf8(L"description=" + Projects[t].Description + L"\n");

			file << Formatting::to_utf8(L"nCoeff=" + std::to_wstring(Projects[t].Coeff) + L"\n");
			file << Formatting::to_utf8(L"MaxIterations=" + std::to_wstring(Projects[t].MaxIterations) + L"\n");
			file << Formatting::to_utf8(L"BailoutRadius=" + std::to_wstring(Projects[t].Bailout) + L"\n");

			file << Formatting::to_utf8(L"xmin=" + Formatting::LDToStr(Projects[t].xmin) + L"\n");
			file << Formatting::to_utf8(L"xmax=" + Formatting::LDToStr(Projects[t].xmax) + L"\n");
			file << Formatting::to_utf8(L"ymin=" + Formatting::LDToStr(Projects[t].ymin) + L"\n");
			file << Formatting::to_utf8(L"ymax=" + Formatting::LDToStr(Projects[t].ymax) + L"\n");

			file << Formatting::to_utf8(L"var_a=" + Formatting::LDToStr(Projects[t].VarA) + L"\n");
			file << Formatting::to_utf8(L"var_b=" + Formatting::LDToStr(Projects[t].VarB) + L"\n");
			file << Formatting::to_utf8(L"var_c=" + Formatting::LDToStr(Projects[t].VarC) + L"\n");
			file << Formatting::to_utf8(L"var_d=" + Formatting::LDToStr(Projects[t].VarD) + L"\n");

			file << Formatting::to_utf8(L"]\n");
		}

		file.close();

        return true;
	}


	return false;
}


HistoryHandler::FileProperty HistoryHandler::GetInputProperty(const std::wstring input)
{
	for (int t = 0; t < kPropertyListCount; t++)
	{
		if (input == FilePropertyList[t])
		{
			return FilePropertyReference[t];
		}
	}

	return FileProperty::None;
}
